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
int knowledge_put(const char *intent, const char *entity, const char *response) {

	/* to be implemented */

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

	char c;
	/* to be implemented */
	if (f == NULL)
    {
        printf("knowledge_read() | Cannot open file \n");
    }
	else 
	{
		printf("knowledge_read() | File Output: \n");
		do{
			c = fgetc(f);
			printf("%c", c);
		}
		while(c != EOF);
	};

	return 0;
}


/*
 * Reset the knowledge base, removing all know entitities from all intents.
 */
void knowledge_reset() {

	/* to be implemented */

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
