/*
 * INF1002 (C Language) Group Project.
 *
 * This file implements the chatbot's knowledge base.
 *
 * knowledge_get() retrieves the response to a question.
 * knowledge_put() inserts a new response to a question.
 * knowledge_read() reads the knowledge base from a file.
 * knowledge_reset() erases all of the knowledge.
 * knowledge_write() saves the knowledge base in a file.
 *
 * You may add helper functions as necessary.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "chat1002.h"

#include <Windows.h>


extern NODE* head = NULL;
/*
 * Get the response to a question.
 *
 * Input:
 *   intent   - the question word
 *   entity   - the entity
 *   response - a buffer to receive the response
 *   n        - the maximum number of characters to write to the response buffer
 *
 * Returns:
 *   KB_OK, if a response was found for the intent and entity (the response is copied to the response buffer)
 *   KB_NOTFOUND, if no response could be found
 *   KB_INVALID, if 'intent' is not a recognised question word
 */
int knowledge_get(const char *intent, const char *entity, char *response, int n, FILE *f) {

	/*No Error Handling for keys not found in .ini*/

	int i = 0;
	char buffer[256];

	printf("knowledge_get() | Intent: %s | Entity: %s\n", intent, entity);

	while (fgets(buffer, sizeof(buffer), f)) {

		char* token = strtok(buffer, "=");

		/*[what] response*/
		if (strstr(token, "[what]") != NULL && strstr(intent, "what") != NULL) {
			printf("knowledge_get() | [what] Token found\n");
			while (strstr(token, "[where]") == NULL && fgets(buffer, sizeof(buffer), f)) {
				token = strtok(buffer, "=");
				printf("knowledge_get() | [what]Key: %s\n", token);

				/*Check if key is found*/
				if (strstr(token, entity) != NULL) {
					response = strtok(NULL, "=");
					printf("knowledge_get() | [what]Response for key '%s' found: %s\n", token, response);
					break;
				}
			}
			if (strstr(token, entity) == NULL) {
				response = '\0';
				knowledge_put(intent, entity, response, f);
			}
		}
		/*[where] response*/
		else if (strstr(token, "[where]") != NULL && strstr(intent, "where") != NULL) {
			printf("knowledge_get() | [where] Token found\n");
			while (strstr(token, "[who]") == NULL && fgets(buffer, sizeof(buffer), f)) {
				token = strtok(buffer, "=");
				printf("knowledge_get() | [where]Key: %s\n", token);

				/*Check if key is found*/
				if (strstr(token, entity) != NULL) {
					response = strtok(NULL, "=");
					printf("knowledge_get() | [where]Response for key '%s' found: %s\n", token, response);
					break;
				}
			}

			if (strstr(token, entity) == NULL) {
				response = '\0';
				knowledge_put(intent, entity, response, f);
			}
		}
		/*[who] response*/
		else if (strstr(token, "[who]") != NULL && strstr(intent, "who") != NULL) {
			printf("knowledge_get() | [who] Token found\n");
			while (fgets(buffer, sizeof(buffer), f)) {
				token = strtok(buffer, "=");
				printf("knowledge_get() | [who]Key: %s\n", token);

				/*Check if key is found*/
				if (strstr(token, entity) != NULL) {
					response = strtok(NULL, "=");
					printf("knowledge_get() | [who]Response for key '%s' found: %s\n", token, response);
					break;
				}
			}

			if (strstr(token, entity) == NULL) {
				response = '\0';
				knowledge_put(intent, entity, response, f);
			}
		}

	}
	return 0;
	
	/* to be implemented 
	char *f, content;
	knowledge_read(fopen("INF1002_Group Project Assignment_Sample.ini", "r"));
	printf("knowledge_get() | Intent: %s | Entity: %s", intent, entity);

	/*
	if(strstr(intent, entity) != NULL){
		LPCSTR ini = "C:\\config.ini";
	}
	
	return KB_NOTFOUND;*/

}


/*
 * Insert a new response to a question. If a response already exists for the
 * given intent and entity, it will be overwritten. Otherwise, it will be added
 * to the knowledge base.
 *
 * Input:
 *   intent    - the question word
 *   entity    - the entity
 *   response  - the response for this question and entity
 *
 * Returns:
 *   KB_FOUND, if successful
 *   KB_NOMEM, if there was a memory allocation failure
 *   KB_INVALID, if the intent is not a valid question word
 */
int knowledge_put(const char *intent, const char *entity, const char *response, FILE *f) {

	/* to be implemented */
	printf("--------------------\n");
	printf("knowledge_put() | We got here!\n");
	printf("Intent: %s\n", intent);
	printf("Entity: %s\n", entity);
	printf("Response: %s\n", response);
	
	char putBuffer[MAX_RESPONSE];
	//char* putBuffer[MAX_RESPONSE];
	//char* token = strtok(putBuffer, "="); 
	
	// For unkown entity, under [WHAT].
	if (compare_token(intent, "what") == 0) {
		if (compare_token(entity, ""))
		printf("%s: I don't know. What is %s?\n", chatbot_botname(), entity);

		//prompt_user( - buffer - , - 256 - , - a string. not sure how to put. -);
	}

	// For unkown entity, under [WHERE].
	else if (compare_token(intent, "where") == 0) {
		printf("%s: I don't know. Where is %s?\n", chatbot_botname(), entity);
	}
	// For unkown entity, under [WHO].
	else if (compare_token(intent, "who") == 0) {
		printf("%s: I don't know. Who is %s?\n", chatbot_botname(), entity);
	}
	else {
		return KB_INVALID;
	}

	

}


/*
 * Read a knowledge base from a file.
 *
 * Input:
 *   f - the file
 *
 * Returns: the number of entity/response pairs successful read from the file
 */
int knowledge_read(FILE *f) {
	char line[MAX_INPUT];
	char *entity;
	char *response;
	int intentcounter = 0;
	// 1 = what
	// 2 = where
	// 3 = who
	/* to be implemented */
	if (f == NULL)
    {
        printf("knowledge_read() | Cannot open file \n");
    }
	else 
	{
		printf("knowledge_read() | File Output: \n");
		while (fgets(line, MAX_INPUT, f) != NULL) {
			NODE* newNode;
			if (compare_token(line, "[what]\n") == 0) {
				intentcounter = 1;
			}
			else if (intentcounter == 1) {
				if (compare_token(line, "\n") == 0) {
					intentcounter = 0;
					continue;
				}
				entity = strtok(line, "=");
				response = strtok(NULL, "=");
				response[strlen(response) - 1] = '\0';
				if (head == NULL) {
					head = (NODE*)malloc(sizeof(NODE));
					strncpy(head->entity, entity, MAX_ENTITY);
					strncpy(head->response, response, MAX_RESPONSE);
					strncpy(head->intent, "what", MAX_INTENT);
				}
				else {
					newNode = (NODE*)malloc(sizeof(NODE));
					strncpy(newNode->entity, entity, MAX_ENTITY);
					strncpy(newNode->response, response, MAX_RESPONSE);
					strncpy(newNode->intent, "what", MAX_INTENT);
					head->next = newNode;
				}
				
				/*printf("entity : %s", entity);
				printf("response : %s", response);*/

			}
			if (compare_token(line, "[where]\n") == 0) {
				intentcounter = 2;
			}
			else if (intentcounter == 2) {
				if (compare_token(line, "\n") == 0) {
					intentcounter = 0;
					continue;
				}
				entity = strtok(line, "=");
				response = strtok(NULL, "=");
				response[strlen(response) - 1] = '\0';
				if (head == NULL) {
					head = (NODE*)malloc(sizeof(NODE));
					strncpy(head->entity, entity, MAX_ENTITY);
					strncpy(head->response, response, MAX_RESPONSE);
					strncpy(head->intent, "where", MAX_INTENT);
				}
				else {
					newNode = (NODE*)malloc(sizeof(NODE));
					strncpy(newNode->entity, entity, MAX_ENTITY);
					strncpy(newNode->response, response, MAX_RESPONSE);
					strncpy(newNode->intent, "where", MAX_INTENT);
					head->next = newNode;
				}

				/*printf("entity : %s", entity);
				printf("response : %s", response);*/
			}
			if (compare_token(line, "[who]\n") == 0) {
				intentcounter = 3;
			}
			else if (intentcounter == 3) {
				if (compare_token(line, "\n") == 0) {
					intentcounter = 0;
					continue;
				}
				entity = strtok(line, "=");
				response = strtok(NULL, "=");
				response[strlen(response) - 1] = '\0';
				if (head == NULL) {
					head = (NODE*)malloc(sizeof(NODE));
					strncpy(head->entity, entity, MAX_ENTITY);
					strncpy(head->response, response, MAX_RESPONSE);
					strncpy(head->intent, "who", MAX_INTENT);
				}
				else {
					newNode = (NODE*)malloc(sizeof(NODE));
					strncpy(newNode->entity, entity, MAX_ENTITY);
					strncpy(newNode->response, response, MAX_RESPONSE);
					strncpy(newNode->intent, "who", MAX_INTENT);
					head->next = newNode;
				}

				/*printf("entity : %s", entity);
				printf("response : %s", response);*/
			}
		}
		NODE* ptr = head;
		while (ptr != NULL) {
			//printf("%s", ptr->response);
			ptr = ptr->next;
		}
		head = clearmemory(head);
		fclose(f);
	};

	return 0;
}


/*
 * Reset the knowledge base, removing all know entitities from all intents.
 */
void knowledge_reset() {
	
	temp = (NODE*)malloc(sizeof(NODE));
	while (head->next)
	{
		temp = head->next;
		head->next = head->next->next;
		free(temp);
	}
	free(temp);
	/* for debugging*/
	printf("All knowledge is been cleared\n");
}


/*
 * Write the knowledge base to a file.
 *
 * Input:
 *   f - the file
 */
void knowledge_write(FILE *f) {

	/* to be implemented */

}


NODE* clearmemory(NODE* head) {
	NODE* ptr = head;
	while (ptr != NULL) {
		ptr = ptr->next;
		free(head);
		head = ptr;
	}
	return head;
}