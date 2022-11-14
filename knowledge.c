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
// #define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "chat1002.h"
#include <stdbool.h>

extern NODE* head = NULL;


/* Check if a intent is matched to where who what

If matched return 1  */

int isKeyword(char* buffer) {
	char* keywords[] = { "where","who","what" };
	int i, flag = 0;
	for (i = 0; i < 3; ++i) {
		if (strcmp(keywords[i], buffer) == 0) {
			flag = 1;
			break;
		}
	}
	return flag;
}

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
int knowledge_get(const char* intent, const char* entity, char* response, int n) {
	// if intent not equal to what who where
	if (isKeyword(intent) == 0) {
		return KB_INVALID;
	}
	NODE* current = head;
	while (current != NULL)
	{
		// Copy response to buffer if intent and entity match.
		if (compare_token(current->intent, intent) == 0 && compare_token(current->entity, entity) == 0) {
			snprintf(response, n, "%s", current->response);
			return KB_OK;
		}
		current = current->next;
	}
	return KB_NOTFOUND;
}

int check_exists(char* entity, char* intent, char* response)
{
	NODE* temp = head;
	// check if entity, intent and response exists in the linked list
	while (temp != NULL)
	{
		// Check if entity and intent matches 
		if (compare_token(temp->entity, entity) == 0 && compare_token(temp->intent, intent) == 0)
		{
			if ((compare_token(temp->response, response) == 0))
			{
				// if the response is the same it will return 0
				return 1;
			}
			else
			{
				// if the response is different it will be replaced with new response
				snprintf(temp->response, MAX_RESPONSE, response);
				return 1;
			}
		}
		temp = temp->next;
	}
	return 0;
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
int knowledge_put(const char* intent, const char* entity, const char* response) {

	// allocate memory for new_node
	NODE* new_node = (NODE*)malloc(sizeof(NODE));
	// if failed to create node means no memory.
	if (new_node == NULL)
	{
		return KB_NOMEM;
	}

	// copy the intent, entity and response to the new node
	snprintf(new_node->entity, MAX_ENTITY, entity);
	snprintf(new_node->intent, MAX_INTENT, intent);
	snprintf(new_node->response, MAX_RESPONSE, response);

	if (head != NULL)
	{
		bool judge = true;
		NODE* current_ptr = head->next;
		NODE* pre_ptr = head;

		while (strlen(current_ptr->intent) < strlen(intent))
		{
			if (current_ptr->next == NULL)
			{
				current_ptr->next = new_node;
				new_node->next = NULL;
				judge = false;
			}
			pre_ptr = current_ptr;
			current_ptr = current_ptr->next;
		}
		if (judge)
		{
			pre_ptr->next = new_node;
			new_node->next = current_ptr;
		}
	}
	else
	{
		NODE* head_node = (NODE*)malloc(sizeof(NODE));
		head = head_node;
		head_node->next = new_node;
		new_node->next = NULL;
	}

	return KB_OK;


}

/*
 * Read a knowledge base from a file.
 *
 * Input:
 *   f - the file
 *
 * Returns: the number of entity/response pairs successful read from the file
 */
int knowledge_read(FILE* f) {
	int count = 0;
	int status = 0;
	char intent[MAX_INTENT];
	char buffer[MAX_RESPONSE + MAX_ENTITY + 1];
	char* tempintent;
	while (fgets(buffer, 255, f))
	{
		buffer[strcspn(buffer, "\n")] = 0;
		if (strlen(buffer) == 0)
		{
			continue;
		}
		// check is this line contains intent keyword with [intent]
		if (buffer[0] == '[')
		{
			snprintf(intent, MAX_INTENT, buffer);
			// Strip [ from intent and store to tempintent the rest.
			tempintent = strtok(intent, "[");
			// Strip ] from tempintent and store back to it.
			tempintent = strtok(tempintent, "]");
			// Check if it contains who/what/where
			if (isKeyword(tempintent))
			{
				snprintf(intent, MAX_INTENT, tempintent);
				status = 1; // means we have the correct intent this section is correct
			}
			else
			{
				status = 0; // No, this intent is not correct, skip the section
			}

		}
		else if(status)
		{
			// check if the line contains "="
			if (strchr(buffer, '=') != NULL)
			{
				// split the string by "="
				char* token = strtok(buffer, "=");
				char* entity = token;
				token = strtok(NULL, "=");
				char* response = token;
				//printf("intent = %s entity = %s response = %s\n", intent, entity, response);
				if (knowledge_put(intent, entity, response) == 0)
				{
					count++;
				}
			}

		}
	}
	return count;
}


/*
 * Reset the knowledge base, removing all know entitities from all intents.
 */
void knowledge_reset() {
	NODE *ptr = head;
	while(ptr!=NULL){
		ptr=ptr->next;
		free(head);
		head=ptr;
	}
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
	char buffer2[255];
	NODE* p = head->next;

	while (p != NULL)
	{

		if (!compare_token(empty, p->intent) == 0)
		{
			if (header == 1)
			{
				// so after every rows of entity and response, we would have a new line 
				fputs("\n", f);
			}
			snprintf(empty, MAX_INPUT, p->intent);
			snprintf(buffer2, 255, "[%s]", p->intent);
			fputs(buffer2, f);
			fputs("\n", f);
			header = 1;
		}
		// format string to concatenate 2 variable together in 1 line
		j = snprintf(buffer, 255, "%s = %s\n", p->entity, p->response);
		fputs(buffer, f);
		p = p->next;
	}
}
