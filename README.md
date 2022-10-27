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
