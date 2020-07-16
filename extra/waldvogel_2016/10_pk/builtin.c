/**
 * @author Fabian Klopfer
 * @author Jannik Bamberger
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "builtin.h"

int echo(int argc, char **argv);
int help(int argc, char **argv);
int pwd(int argc, char **argv);
int cd(int argc, char **argv);

builtin_func builtin_funcs[BUILTIN_COUNT] = {
		{.name = "help",
		.help = "Display information about builtin functions.",
		.func = help},
		{.name = "echo",
		.help = "Write arguments to the standard output.",
		.func = echo},
		{.name = "pwd",
		.help = "Print the current working directory.",
		.func = pwd},
		{.name = "cd",
		.help = "Change the current working direktory.",
		.func = cd}
	};

/**
 * Echo command prints all arguments separated by one whitespace.
 * @param argc arg count
 * @param argv arguments and command name
 * @return successful
 * */
int echo(int argc, char **argv)
{
	for (int i = 1; i < argc; i++)
		printf("%s ", argv[i]);
	printf("\n");
	return 0;
}

/**
 * Help command prints all builtin functions and a short description.
 * @param argc arg count
 * @param argv arguments and command name
 * @return successful
 * */
int help(int argc, char **argv)
{
	if (argc > 1) {
		printf("The following arguments are invalid: ");
		echo(argc, argv);
		return 1;
	}
	printf("Builtin commands:\n");
	for (int i = 0; i < BUILTIN_COUNT; i++)
		printf("%s:\t%s\n", builtin_funcs[i].name,
			builtin_funcs[i].help);
	return 0;
}

/**
 * pwd prints the current working dir of the rsh.
 * @param argc arg count
 * @param argv arguments and command name
 * @return successful
 * */
int pwd(int argc, char **argv)
{
	if (argc > 1) {
		printf("The following arguments are invalid: ");
		echo(argc, argv);
		return 1;
	}
	char *path = getcwd(NULL, 0);

	printf("%s\n", path);
	free(path);
	return 0;
}

/**
 * cd changes the current working directory of the rsh.
 * @param argc arg count
 * @param argv arguments and command name
 * @return successful
 * */
int cd(int argc, char **argv)
{
	if (argc > 2) {
		printf("The following arguments are invalid: ");
		echo(argc - 1, &(argv[1]));
		return 1;
	}
	const char *path = argv[1];

	if (path == NULL)
		path = getenv("HOME");
	if (chdir(path) != 0)
		printf("failed to change directory to %s\n", path);
	return 0;
}
