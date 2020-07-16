/*
 * @author Fabian Klopfer
 * @author Jannik Bamberger
 * @bonus10
 * @credits 65
 *
 * Klasse Arbeit!
 *
 * */
#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#include "parser.h"
#include "builtins.h"

#define DELIMITERS " \t\n\f\r\v"
#define INIT_CMD_SIZE 8
#define READ 0
#define WRITE 1

/**
 * apply the redirections mentioned in the command c.
 * Should be applied after pipelining.
 * */
void redirect(Command *c)
{
	for (size_t i = 0; i < c->redc; i++)
		//if a file is mentioned, a redirect is applied,
		//otherwise the file descriptor is duplicated.
		if (c->redv[i].file != NULL) {
			int fd = open(c->redv[i].file, c->redv[i].flags, 0666);
			//check for errors
			if (fd < 0)
				err(1, "open %s", c->redv[i].file);
			if (fd != c->redv[i].fd) {
				if (dup2(fd, c->redv[i].fd) < 0)
					warnx("Error duplicating %d to %d",
						fd, c->redv[i].fd);
				close(fd);
			}
		} else
			if (dup2(c->redv[i].ref, c->redv[i].fd) < 0)
				warnx("Error duplicating %d to %d",
					c->redv[i].ref, c->redv[i].fd);
}

/**
 * Execute cmd with input as stdin and output as stdout,
 * then apply redirections specified in the command.
 * */
void set_pipes(Command *cmd, int in, int out)
{
#ifdef DEBUG
	printf("Command %s with pipe from %d to %d\n", cmd->argv[0], in, out);
#endif
	//prevent closing the stdin
	if (in != STDIN_FILENO) {
		if (dup2(in, STDIN_FILENO) < 0)
			warnx("Error duplicating %d to %d for %s",
				in, STDIN_FILENO, cmd->argv[0]);
		close(in);
	}

	//prevent closing stdout
	if (out != STDOUT_FILENO) {
		if (dup2(out, STDOUT_FILENO) < 0)
			warnx("Error duplicating %d to %d for %s",
				out, STDOUT_FILENO, cmd->argv[0]);
		close(out);
	}

	//pipelining finished, apply redirections
	redirect(cmd);
}

/**
 * returnes the matching builtin func, or null if no match
 * */
void (*get_builtin(char *name))(int, char **)
{
	for (int i = 0; builtin_funcs[i].name; i++)
		if (strcmp(builtin_funcs[i].name, name) == 0)
			return builtin_funcs[i].func;
	return NULL;
}

/**
 * wait for all child processes to terminate
 * */
int wait_for_childs(void)
{
	int pid;
	int status;
	int exitcode = 0;//if there was no command 0 is returned

	//all commands are forked and running. Wait for all of
	//them to terminate.
	while ((pid = wait(&status)) > 0) {
	#ifdef DEBUG
		printf("Child with pid %d terminated\n", pid);
	#endif
		if (WIFEXITED(status)) {
			//if one command fails, the entire pipeline is
			//considered "failed" aka nonzero return value
			exitcode = exitcode || WEXITSTATUS(status);
		} else
			exitcode = 1;
	}
	return exitcode;
}

void close_read(int read)
{
	if (read != STDIN_FILENO)
		close(read);
}

void close_write(int write)
{
	if (write != STDOUT_FILENO)
		close(write);
}

/**
 * The function chains the commands together with pipes, applies
 * redirections and executes the commands.
 * */
int execute_commands(Command *cmd)
{
	//reverse order of commands
	Command *new_head = 0;

	while (cmd) {
		Command *next = cmd->prev;

		cmd->prev = new_head;
		new_head = cmd;
		cmd = next;
	}
	cmd = new_head;

	int read = STDIN_FILENO;
	int write = STDOUT_FILENO;
	int fd[2];

	//loop through commands
	while (cmd != NULL) {
		//if there are more commands another pipe is needed
		if (cmd->prev != NULL) {
			if (pipe(fd) < 0)
				err(1, "pipe");
#ifdef DEBUG
			printf("Created pipe (read: %d, write %d)\n",
				fd[READ], fd[WRITE]);
#endif
			write = fd[1];
		} else {
			//otherwise the commands output is stdout
			write = STDOUT_FILENO;
		}

		int pid = fork();

		if (pid < 0)
			err(1, "fork");
		if (pid == 0) { //child
			//builtin function
			void (*b_func)(int, char **) =
				get_builtin(cmd->argv[0]);

			set_pipes(cmd, read, write);
			if (b_func) { //exec builtin
				b_func((int) cmd->argc, cmd->argv);
				exit(0); //exit when builtin is finished
			} else { //exec extern
				if (execvp(cmd->argv[0], cmd->argv) < 0)
					err(1, "exec");
			}
		} else { //parent
#ifdef DEBUG
			printf("Child id is %d\n", (int) pid);
#endif
			close_write(fd[WRITE]);
			close_read(read);
			//the next command shall read the output of
			//the previous command.
			read = fd[READ];
		}

		cmd = cmd->prev;
	} //end while loop

	return wait_for_childs();
}


int main(void)
{
	/* variables req'd to get individual input lines */
	char *line = NULL;
	size_t line_size = 0;
	ssize_t line_used = -1;

	/* iterate over input lines */
	while (printf("$ "),
		(line_used = getline(&line, &line_size, stdin)) > 0) {

		/* delete trailing newline for nicer output */
		if (line[line_used - 1] == '\n')
			line[--line_used] = '\0';

		/* parse command */
		Command *cmd = parse_command(line);

		/* execute commands*/
		execute_commands(cmd);

		/* free the command */
		free_command(cmd);
		cmd = NULL;
	}
	printf("[exit by end of file]\n");

	return 0;
}
