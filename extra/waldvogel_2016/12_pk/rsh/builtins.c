/*
 * @author Fabian Klopfer
 * @author Jannik Bamberger
 * */
#include <stdio.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include <err.h>
#include <unistd.h>

#include "builtins.h"



void help_func(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	printf("\nBuiltin commands:\n\n");
	for (int i = 0; builtin_funcs[i].name; i++)
		printf("  %s\n    %s\n\n",
			builtin_funcs[i].name,
			builtin_funcs[i].help);

}



void echo_func(int argc, char **argv)
{
	if (argc > 1)
		printf("%s", argv[1]);
	for (int i = 2; i < argc; i++)
		printf(" %s", argv[i]);
	printf("\n");
}



void pwd_func(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	char *path = getcwd(NULL, 0);

	if (path) {
		printf("%s\n", path);
		free(path);
	} else
		warn("Failed to getcwd");
}



void cd_func(int argc, char **argv)
{
	if (argc > 1) {
		if (chdir(argv[1]))
			warn("cd: %s", argv[1]);
	} else {
		char *p = getenv("HOME");

		if (p) {
			if (chdir(p))
				warn("cd: %s", argv[1]);
		} else
			warn("cd: failed to get HOME");
	}
}

void exit_func(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	printf("[exit by exit command]\n");
	exit(0);
}



struct builtin_func builtin_funcs[] = {
	{
		.name = "help",
		.help = "Display information about builtin commands.",
		.detatched = 1,
		.func = help_func
	},
	{
		.name = "echo",
		.help = "Write arguments to the standard output.",
		.detatched = 1,
		.func = echo_func
	},
	{
		.name = "pwd",
		.help = "Print the name of the current working directory.",
		.detatched = 1,
		.func = pwd_func
	},
	{
		.name = "cd",
		.help = "Change the shell working directory.",
		.detatched = 0,
		.func = cd_func
	},
	{
		.name = "exit",
		.help = "Terminate the shell.",
		.detatched = 0,
		.func = exit_func
	},
	{
		.name = NULL
	}
};
