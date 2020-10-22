/*
 * @author Fabian Klopfer
 * @author Jannik Bamberger
 * @credits 20
 * @bonus10
 *
 * Hat seine Probleme, aber insgesamt gut. Schöne Debug Meldungen.
 * */
#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>

#include "builtins.h"
#include "parser.h"

#define DELIMITERS " \t\n\f\r\v"
#define INIT_CMD_SIZE 8

int child = -1;
int children = 0;

void wait_for_childs(void)
{
	int pid;
	int status;

	//all commands are forked and running. Wait for all of
	//them to terminate.
	while ((pid = wait(&status)) > 0) {
		if (pid == child)
			child = -1;
		if (WIFEXITED(status))
			printf("\x1b[36mChild %u returned %d.\x1b[m\n", pid, WEXITSTATUS(status));
		else
			printf("\x1b[1;31mChild %u returned for unknown reason.\x1b[m\n", pid);
	}
}

void sig_handler(int sig)
{
	switch (sig) {
	case SIGINT:
#ifdef DEBUG
		printf("parent ignoring sigint\n");
#endif
		children = 0; //all childs received SIGINT
		if (child > 0) {
			kill(child, SIGKILL); //kill sleeping child process
			child = -1; //the background job is terminated, too.
		}
		wait_for_childs(); //wait for them to terminate
		return;
	case SIGUSR1:
#ifdef DEBUG
		printf("sending sigstop to %d\n", child);
#endif
		if (child > 0) {
			children--; //the child will be paused
			kill(child, SIGSTOP); //send SIGSTOP to the first child
		}
		return;
	case SIGUSR2:
#ifdef DEBUG
		printf("sending sigcont to %d\n", child);
#endif
		if (child > 0) {
			children++; //child will be restarted
			kill(child, SIGCONT); //send SIGCONT to child
		}
		return;
	default:
		err(1, "rsh is not registered for %d signal", sig);
	}
}

/**
 * Get the builtin command struct matching the name of c.
 * NULL, if no match is found.
 * */
struct builtin_func *get_builtin(Command *c)
{
	for (int i = 0; builtin_funcs[i].name; i++)
		if (strcmp(builtin_funcs[i].name, c->argv[0]) == 0) {
			return &builtin_funcs[i];
		}
	return NULL;
}

void run(Command *c)
{
	/* manage local redirections */
	for (size_t i = 0; i < c->redc; i++) {
		if (c->redv[i].file) {
			int ofd = open(c->redv[i].file, c->redv[i].flags, 0666);

			if (ofd < 0)
				err(1, "open(%s)", c->redv[i].file);
			if (dup2(ofd, c->redv[i].fd) < 0)
				err(1, "dup2");
			close(ofd);
		} else {
			if (dup2(c->redv[i].ref, c->redv[i].fd) < 0)
				err(1, "dup2");
		}
	}

	/* search builtin command */
	for (int i = 0; builtin_funcs[i].name; i++)
		if (strcmp(builtin_funcs[i].name, c->argv[0]) == 0) {
			builtin_funcs[i].func((int)(c->argc), c->argv);
			exit(0);
		}

	/* was not builtin, evoke the child */
	execvp(c->argv[0], c->argv);
	err(1, "execvp %s", c->argv[0]);
}



int main(void)
{
	/* variables req'd to get individual input lines */
	char *line = NULL;
	size_t line_size = 0;
	ssize_t line_used = -1;

	printf("This is `rsh`, pid=%u\n\x1b[1;35m$\x1b[m ", getpid());

	// initialize the signal handler
	struct sigaction sa = {
		.sa_handler = &sig_handler//,
		//.sa_flags = SA_RESTART
	};

	//set handlers for SIGINT, SIGUSR1 and SIGUSR2
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);

	/* iterate over input lines */
	while (1) {

		errno = 0;
		line_used = getline(&line, &line_size, stdin);

		//the getLine command was interrupted
		//getline is not restarted automatically
		if (errno == EINTR) {
#ifdef DEBUG
			printf("errno is %s\n", strerror(errno));
#endif
			//reset error flag of stdin so it can be used again
			clearerr(stdin);
			//reprint prompt
			printf("\n\x1b[1;35m$\x1b[m ");
			//restart loop
			continue;
		}
		if (line_used <= 0) {
			printf("[exit by end of file]\n");
			return 0;
		}

		/* delete trailing newline for nicer output */
		if (line[line_used - 1] == '\n')
			line[--line_used] = '\0';
		/* parse command */
		Command *cmd = parse_command(line);

		children = 0;
		int pipefd[2];
		int output;

		output = dup(STDOUT_FILENO);
		for (Command *c = cmd; c; c = c->prev) {

			//check, if command is builtin, and shall run in a
			//detatched shell process, or directly in the parent
			//this is important, so that exit can actually
			//exit the shell and cd works
			struct builtin_func *bif = get_builtin(c);
			if (bif != NULL && !bif->detatched) {
				bif->func((int) c->argc, c->argv);
				break;
			}

			if (c->prev) {
				if (pipe(pipefd))
					err(1, "pipe");
			}

			pid_t pid = fork();

			/* the child process */
			if (pid == 0) {

				// restore default handlers for child processes
				//so they can actually be interrupted.
				struct sigaction def = {
						.sa_handler = SIG_DFL
				};
				sigaction(SIGINT, &def, NULL);
				sigaction(SIGUSR1, &def, NULL);
				sigaction(SIGUSR2, &def, NULL);

				if (c->prev) {
					//pipefd[1] refers to the write end of the pipe
					close(pipefd[1]);

					if (dup2(pipefd[0], STDIN_FILENO) < 0)
						err(1, "dup2");
					close(pipefd[0]);
				}

				if (output != STDOUT_FILENO)
					if (dup2(output, STDOUT_FILENO) < 0)
						err(1, "dup2");

				run(c);
				errx(1, "child() returned.");
			}

			/* the parent process */
			if (pid < 0)
				err(1, "%s: cannot fork", c->argv[0]);

			if (child < 0)
				child = pid;

			printf("\x1b[36mForked %u: %s\x1b[m\n", pid, c->argv[0]);

			close(output);
			if (c->prev) {
				close(pipefd[0]);
				output = pipefd[1];
			}

			children++;
		}

		close(output);

		/* done with launching the pipeline */
		free_command(cmd);
		cmd = NULL;

		int pid;
		int status;
		//wait for all active childs
		while (children-- > 0 && (pid = wait(&status)) > 0) {
			//if the background process is terminated, a new
			//background process may added
			if (pid == child)
				child = -1;
			if (WIFEXITED(status))
				printf("\x1b[36mChild %u returned %d.\x1b[m\n", pid, WEXITSTATUS(status));
			else
				printf("\x1b[1;31mChild %u returned for unknown reason.\x1b[m\n", pid);
		}

		printf("\x1b[1;35m$\x1b[m ");
	}

	return 0;
}
