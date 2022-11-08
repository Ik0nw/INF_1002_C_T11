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
int knowledge_get(const char *intent, const char *entity, char *response, int n) {


	
	return KB_NOTFOUND;
	
	
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
int knowledge_put(const char *intent, const char *entity, const char *response) {

	return KB_INVALID;

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
	if (f == NULL){
        printf("knowledge_read() | Cannot open file \n");
    }
	else {
		printf("knowledge_read() | File Output: \n");
		
		if (head == NULL) {
			head = (NODE *)malloc(sizeof(NODE));
			strncpy(head->entity, "SIT", MAX_ENTITY);
			strncpy(head->response, "in sg", MAX_RESPONSE);
			strncpy(head->intent, "where", MAX_INTENT);
		}
		while (fgets(line, MAX_INPUT, f) != NULL) {
			// if (head == NULL) {
			// 	head = (NODE*)malloc(sizeof(NODE));
			// 	strncpy(head->entity, "SIT",MAX_ENTITY);
			// 	strncpy(head->intent, "what", MAX_INTENT);
			// 	strncpy(head->response,"TEST RESPONSE", MAX_RESPONSE);
			// }
			line[strcspn(line, "\n")] = 0;
			// if(line[strlen(line)-1]=='\n'){
			// 	line[strlen(line)-1]='\0';
			// 	printf("%s", line);
			// }
			printf("%s", line);
			//printf("%s vs [what]",line);
			//printf("%d\n", strcmp(line, "[what]"));
			
			//printf("%d",compare_token(line,"[what]"));
			//printf("%d:%d\n", strlen(line), strlen("[who]"));
			//printf("%d\n", compare_token(line,"[who]"));
			//printf("%d\n", compare_token(line,"[who]\n"));
			if (compare_token(line, "[what]") == 0) {
				intentcounter = 1;
				printf("Once");
			}
			else if (intentcounter == 1) {
				if (compare_token(line, "\n") == 0) {
					intentcounter = 0;
					continue;
				}
				entity = strtok(line, "=");
				response = strtok(NULL, "=");
				response[strlen(response) - 1] = '\0';
				NODE* ptr = head;
				while (ptr != NULL) {
					printf("Hello");
					if (ptr->intent == "what") {
						printf("yes, its a what\n");
						if (compare_token(entity, ptr->entity) == 0) {
							printf("SAME %s", entity);
						}
					}
					ptr = ptr->next;
				}


			}
			if (compare_token(line, "[where]") == 0) {
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

			}
			if (compare_token(line, "[who]") == 0) {
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

			}
			
			
		}
			
		fclose(f);
		/*NODE* ptr = head;
		while (ptr != NULL) {
			printf("%s\n", ptr->intent);
			ptr = ptr->next;
		}*/
	};

	return 0;
}


/*
 * Reset the knowledge base, removing all know entitities from all intents.
 */
void knowledge_reset() {
	NODE* ptr = head;
	while (ptr != NULL) {
		ptr = ptr->next;
		free(head);
		head = ptr;
	}

	/* for debugging*/
	printf("All knowledge is been cleared\n");
}


/*
 * Write the knowledge base to a file.
 *
 * Input:
 *   f - the file
 */
void knowledge_write(FILE* f)
{
	const char* intent_list[3];
	intent_list[0] = "[what]";
	intent_list[1] = "[where]";
	intent_list[2] = "[who]";
	char buffer[255];
	int j = 0;
	int header = 0;
	// empty string
	char empty[MAX_INPUT] = "";
	NODE* p = head;
	
	while (p != NULL)
	{
		if (!strcmp(empty,p->intent) == 0)
		{
			if (header == 1)
			{
				// so after every rows of entity and response, we would have a new line 
				fputs("\n);
			}
			
			strcpy(empty, p->intent);
			fputs(p->intent, f);
			fputs("\n", f);
		        header = 1;
		}
		// format string to concatenate 2 variable together in 1 line
		j = snprintf(buffer, 255, "%s = %s\n", p->entity, p->response);
		fputs(buffer, f);
		p = p->next;
	}
}

