# INF_1002_C_T11

main.c contains the main loop and some utility functions. It prompts the user to type in a
question, gathers the response, and divides it into words. You should not need to modify this
file.

## chatbot.c 
implements the behaviour of the chatbot. It is required to:
1. Identify the intent and entity in each line of input from the user.
2. If the intent is an instruction, carry it out.
3. If the intent is a question, search the knowledge base (see below) for an answer.
4. If the knowledge base does not contain an answer, ask the user for an answer, and add
the new answer to the knowledge base.

## knowledge.c 
implements the chatbot’s knowledge base, as described in the next section. For
each question intent understood by the chatbot, the knowledge base should support
1. Searching the knowledge base for an answer corresponding to the entity in the question.
2. Adding a new entity with a corresponding answer to the question.
3. Erasing the existing entities and answers.

# Stages check

1. Implement a preliminary version of knowledge_get() that simply returns a few hard-coded
responses to questions, and implement chatbot_is_question() and
chatbot_do_question() to use it.
2. Implement knowledge_put() so that you can add new entities to the knowledge base and
re-implement knowledge_get() to retrieve these entities
3. Modify chatbot_do_question() so that it asks the user for new knowledge whenever the
user asks a question that is not in the knowledge base.
4. Implement chatbot_do_reset() so that it erases all of the knowledge created by
knowledge_put(). The main function resets the chatbot at the beginning of the program,
and again whenever the user issues the RESET intent.
5. Implement chatbot_do_save() and chatbot_do_load().
