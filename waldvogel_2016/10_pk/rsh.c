/**
 * @author Fabian Klopfer
 * @author Jannik Bamberger
 * @credits 50
 * @bonus10
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "rsh.h"
#include "builtin.h"
#include <errno.h>

/**
 * Read an entire line from the standard input. The memory is
 * allocated by getline and must be freed after usage.
 * @return Pointer to the read line
 * */
char *readCommand(void)
{
	size_t n = 0;
	char *line = NULL;

	if (getline(&line, &n, stdin) == -1) {
		printf("EOF\n");
		exit(EXIT_FAILURE);
	} else
		return line;
}

/**
 * Tokenize the line pointed to by line and store the pointer of
 * the token array at tokenStorage. The token count is returned.
 * The memory for the token array is dynamically allocated and
 * has to be freed.
 * Line is modified by parseCommand.
 * @param line The input line
 * @param tokenStorage pointer, where the token array should be stored.
 * @return count of tokens in the line
 * */
int parseCommand(char *line, char ***tokenStorage)
{
	size_t tokenBufferSize = TOKENBUFFER; //initial buffer size
	size_t nextIn = 0; //next tokens position in the array
	char **tokens =
		malloc(sizeof(char *) * tokenBufferSize); //try mem allocation

	if (!tokens) {
		printf("can't allocate enougth memory for the token array\n");
		exit(EXIT_FAILURE);
	}


	char *token = strtok(line, DELIM);

	while (token != NULL) {
		tokens[nextIn] = token;
		nextIn++;
		//not enough space for another token
		if (nextIn >= tokenBufferSize) {
			tokenBufferSize += TOKENBUFFER;
			tokens = realloc(tokens, tokenBufferSize);
			if (tokens == NULL) {
				printf("allocation of token space failed\n");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, DELIM); //continue with same string
	}
	//null terminated list of arguments, just like bash
	tokens[nextIn] = NULL;
	*tokenStorage = tokens;
	return (int) nextIn;
}

/**
 * This function will be used to run extern commands.
 * */
int executeExternCommand(int count, char **tokens)
{
	printf("Tried to execute %s with %d arguments\n", tokens[0], count - 1);
	printf("extern commands can't be executed at the moment.\n");
	return 0;
}

/**
 * ExecuteCommand checks, if the command name is empty or if the
 * command is intern. Then the appropriate command is executed.
 * @param count parameter count
 * @param tokens the list of arguments and command name
 * @return the return code of the command (0 on success)
 * */
int executeCommand(int count, char **tokens)
{
	if (tokens[0] == NULL) //no command entered
		return 1;

	//check, if command is built in
	for (int i = BUILTIN_COUNT - 1; i >= 0; i--) {
		if (strcmp(builtin_funcs[i].name, tokens[0]) == 0)
			return (builtin_funcs[i].func)(count, tokens);
	}

	return executeExternCommand(count, tokens);
}

/**
 * Print the promt and read parse and execute the commands in an
 * infinite loop. If EOL is reached readLine terminates the loop.
 * */
void prompt(void)
{
	while (1) {
		printf("$ ");
		char *line = NULL;
		char **tokens = NULL;

		line = readCommand();

		int count = parseCommand(line, &tokens);

		executeCommand(count, tokens);

		free(line);
		free(tokens);

	}
}

int main(void)
{
	prompt(); // print the promt and handle all the input/output
}
