/*
 * INF1002 (C Language) Group Project.
 *
 * This file implements the behaviour of the chatbot. The main entry point to
 * this module is the chatbot_main() function, which identifies the intent
 * using the chatbot_is_*() functions then invokes the matching chatbot_do_*()
 * function to carry out the intent.
 *
 * chatbot_main() and chatbot_do_*() have the same method signature, which
 * works as described here.
 *
 * Input parameters:
 *   inc      - the number of words in the question
 *   inv      - an array of pointers to each word in the question
 *   response - a buffer to receive the response
 *   n        - the size of the response buffer
 *
 * The first word indicates the intent. If the intent is not recognised, the
 * chatbot should respond with "I do not understand [intent]." or similar, and
 * ignore the rest of the input.
 *
 * If the second word may be a part of speech that makes sense for the intent.
 *    - for WHAT, WHERE and WHO, it may be "is" or "are".
 *    - for SAVE, it may be "as" or "to".
 *    - for LOAD, it may be "from".
 * The word is otherwise ignored and may be omitted.
 *
 * The remainder of the input (including the second word, if it is not one of the
 * above) is the entity.
 *
 * The chatbot's answer should be stored in the output buffer, and be no longer
 * than n characters long (you can use snprintf() to do this). The contents of
 * this buffer will be printed by the main loop.
 *
 * The behaviour of the other functions is described individually in a comment
 * immediately before the function declaration.
 *
 * You can rename the chatbot and the user by changing chatbot_botname() and
 * chatbot_username(), respectively. The main loop will print the strings
 * returned by these functions at the start of each line.
 */

#include <stdio.h>
#include <string.h>
#include "chat1002.h"

/*
 * Get the name of the chatbot.
 *
 * Returns: the name of the chatbot as a null-terminated string
 */
const char *chatbot_botname() {

	return "Chatbot";

}


/*
 * Get the name of the user.
 *
 * Returns: the name of the user as a null-terminated string
 */
const char *chatbot_username() {

	return "User";

}


/*
 * Get a response to user input.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0, if the chatbot should continue chatting
 *   1, if the chatbot should stop (i.e. it detected the EXIT intent)
 */
int chatbot_main(int inc, char *inv[], char *response, int n) {
	/* check for empty input */
	if (inc < 1) {
		snprintf(response, n, "");
		return 0;
	}

	/* look for an intent and invoke the corresponding do_* function */
	if (chatbot_is_exit(inv[0]))
		return chatbot_do_exit(inc, inv, response, n);
	else if (chatbot_is_load(inv[0]))
		return chatbot_do_load(inc, inv, response, n);
	else if (chatbot_is_question(inv[0]))
		return chatbot_do_question(inc, inv, response, n);
	else if (chatbot_is_reset(inv[0]))
		return chatbot_do_reset(inc, inv, response, n);
	else if (chatbot_is_save(inv[0]))
		return chatbot_do_save(inc, inv, response, n);
	else {
		snprintf(response, n, "I don't understand \"%s\".", inv[0]);
		return 0;
	}

}


/*
 * Determine whether an intent is EXIT.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "exit" or "quit"
 *  0, otherwise
 */
int chatbot_is_exit(const char *intent) {

	return compare_token(intent, "exit") == 0 || compare_token(intent, "quit") == 0;

}


/*
 * Perform the EXIT intent.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after a question)
 */
int chatbot_do_exit(int inc, char *inv[], char *response, int n) {

	snprintf(response, n, "Goodbye!");

	return 1;

}


/*
 * Determine whether an intent is LOAD.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "load"
 *  0, otherwise
 */
int chatbot_is_load(const char *intent) {

	/* to be implemented */
	if (compare_token(intent, "LOAD") == 0) {
		return 1;
	}
	else {
		return 0;
	}
}


/*
 * Load a chatbot's knowledge base from a file.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after loading knowledge)
 */
int chatbot_do_load(int inc, char* inv[], char* response, int n) {
	//int count;
	//if (inc != 2)
	//{
	//	snprintf(response, n, "[!] Invalid format. LOAD <FILENAME.INI>");
	//}
	//else
	//	// assume we have the right file format
	//{
	//	FILE* f;
	//	f = fopen(inv[1], "r");
	//	count = knowledge_read(f);
	//	snprintf(response, n, "%d pair read from knowledge base", count);
	//	fclose(f);
	//}

	//return 0;

	int count = 0;
	int skip = 0;
	if (inc > 3 || inc == 1) {
		snprintf(response, n, "Please enter a valid input.");
		return 0;
	}
	if ((strcmp(inv[1], "from") == 0)) {
		skip = 1;
	}
	if (skip == 1) {
		if (inc == 2) {
			snprintf(response, n, "Please enter a valid input.");
			return 0;
		}
		snprintf(inv[1], n, inv[2]);
	}
	char* dot = strrchr(inv[1], '.');
	if (!(dot && !strcmp(dot, ".ini"))) {
		snprintf(response, n, "Invalid filename. Please ensure file ends with .ini");
		return 0;
	}
	FILE* f;
	f = fopen(inv[1], "r");
	if (f == NULL) {
		snprintf(response, n, "File doesn't exist. Please try again");
		return 0;
	}
	count = knowledge_read(f);
	snprintf(response, n, "%d pair read from knowledge base", count);
	fclose(f);



	// for SAVE, it may be "as" or "to".
	/* to be implemented */
	return 0;

}
/*
 * Determine whether an intent is a question.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "what", "where", or "who"
 *  0, otherwise
 */
int chatbot_is_question(const char *intent){
	char tempintent[MAX_INTENT] = "";
	strcpy(tempintent, intent);
	for (int i = 0; i < strlen(tempintent); i++) {
		tempintent[i] = tolower(tempintent[i]);
	}
	if( (strcmp(tempintent,"where")==0) || (strcmp(tempintent,"what")==0) || (strcmp(tempintent,"who")==0) ) {
		return 1;
	}
	else{
		return 0;
	}
	/* Implemented */
}
/*
 * Answer a question.
 *
 * inv[0] contains the the question word.
 * inv[1] may contain "is" or "are"; if so, it is skipped.
 * The remainder of the words form the entity.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after a question)
 */

int chatbot_do_question(int inc, char *inv[], char *response, int n) {

	int skip = 1;
	int entitylength = 0;
	strncpy(response, "", MAX_RESPONSE);
	char inputstore[MAX_INPUT] = "";
	char resstore[MAX_RESPONSE] = "";
	char intentstore[MAX_INTENT] = "";
	char entitystore[MAX_ENTITY] = "";
	for (int i = 0; i < strlen(inv[0]); i++) {
		inv[0][i] = tolower(inv[0][i]);
	}
	strcpy(intentstore, inv[0]);
	/*If inv[1] does not contain "is" or "are", we can include them as entity.*/
	if (!(strcmp(inv[1], "is") == 0 || strcmp(inv[1], "are") == 0)) {
		skip = 0;
	}
	//If inv[1] contains "is" or "are", we can exclude them from entity.
	if (skip == 1) {
		entitylength += snprintf(entitystore + entitylength, n, inv[2]);
		//sprintf(response, inv[2]);
		for (int i = 3; i < inc; i++) {
			//sprintf(response, strlen(response), inv[i]);
			entitylength += snprintf(entitystore + entitylength, n, " ");
			entitylength += snprintf(entitystore + entitylength, n, inv[i]);
		}
	}
	// If inv[1] doesnt contain "is" or "are", we can include them in entity.
	else {
		for (int i = 1; i < inc; i++) {
			if (i != 1) {
				entitylength += snprintf(entitystore + entitylength, n, " ");
			}
			entitylength += snprintf(entitystore + entitylength, n, inv[i]);
		}
	}
	if (knowledge_get(intentstore, entitystore, resstore, n) == KB_NOTFOUND) {
		printf("%s: I don't know. ", chatbot_botname());
		for (int i = 0; i < inc; i++) {
			if (i == inc-1) {
				printf("%s?\n", inv[i]);
			}
			else {
				if (i == 0) {
					if (compare_token(intentstore, "what") == 0) {
						printf("What ");
					}
					else if (compare_token(intentstore, "who") == 0) {
						printf("Who ");
					}
					else if (compare_token(intentstore, "where") == 0) {
						printf("Where ");
					}
				}
				else {
					printf("%s ", inv[i]);
				}

			}

		}

		printf("%s: ", chatbot_username());
		fgets(resstore, n, stdin);
		resstore[strlen(resstore)-1] = '\0';
		knowledge_put(intentstore, entitystore, resstore);
		strncpy(response, "Thank you.", MAX_RESPONSE);
	}
	else if(knowledge_get(intentstore, entitystore, response, n) == KB_OK) {
		//response in buffer. auto return to main function to print. 
	}
	else if (knowledge_get(intentstore, entitystore, response, n) == KB_INVALID) {
		strncpy(response, "Wrong Intent.", MAX_RESPONSE);
	}

	return 0;
}


/*
 * Determine whether an intent is RESET.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "reset"
 *  0, otherwise
 */
 /* Done by CX*/
int chatbot_is_reset(const char* intent) {

	if (compare_token(intent, "reset") == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


/*
 * Reset the chatbot.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after beign reset)
 */
int chatbot_do_reset(int inc, char *inv[1], char *response, int n) {

	knowledge_reset();
	snprintf(response, n, "Chatbot reset.");
	return 0;

}


/*
 * Determine whether an intent is SAVE.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "what", "where", or "who"
 *  0, otherwise
 */
/* Done by CX*/
int chatbot_is_save(const char *intent) {

	/* to be implemented */
	if (compare_token(intent, "SAVE") == 0) {
		return 1;
	}
	else {
		return 0;
	}
}


/*
 * Save the chatbot's knowledge to a file.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after saving knowledge)
 */
int chatbot_do_save(int inc, char *inv[], char *response, int n) {
	int skip = 0;
	int exists = 0;
	if (inc > 3 || inc == 1) {
		snprintf(response, n, "Please enter a valid input.");
		return 0;
	}
	if ((strcmp(inv[1], "as") == 0) || strcmp(inv[1], "to")==0) {
		skip = 1;
	}
	if (skip == 1) {
		if (inc == 2) {
			snprintf(response, n, "Please enter a valid input.");
			return 0;
		}
		snprintf(inv[1], n, inv[2]);
	}
	char* dot = strrchr(inv[1], '.');
	if (!(dot && !strcmp(dot, ".ini"))) {
		snprintf(response, n, "Invalid filename. Please ensure file ends with .ini");
		return 0;
	}
	FILE* f;
	if ((f = fopen(inv[1], "r"))) {
		fclose(f);
		exists = 1;
	}
	if (exists == 1) {
		prompt_user(response, n, "File already exists. Do you want to overwrite it? (Y/N)");
		while (!(compare_token(response, "Y") == 0 || compare_token(response, "N") == 0)) {
			prompt_user(response, n, "Please enter a valid input. File already exists. Do you want to overwrite it? (Y/N)");
		}
		if (compare_token(response, "Y") == 0) {
			f = fopen(inv[1], "w");
			knowledge_write(f);
			fclose(f);
			snprintf(response, n, "Knowledge base saved to %s", inv[1]);
		}
		else if (compare_token(response, "N") == 0) {
			snprintf(response, n, "Knowledge base not saved to %s", inv[1]);
		}
		
	}
	else {
		f = fopen(inv[1], "w");
		knowledge_write(f);
		fclose(f);
		snprintf(response, n, "Knowledge base saved to %s", inv[1]);
	}


	// for SAVE, it may be "as" or "to".
	/* to be implemented */
	return 0;

}



