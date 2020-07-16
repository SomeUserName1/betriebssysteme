/*
 * @author Fabian Klopfer
 * @author Jannik Bamberger
 * */

#define _POSIX_C_SOURCE  200809L

#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>

#include "parser.h"



void *safe_malloc(size_t s)
{
	void *p = malloc(s);

	if (!p)
		err(1, "safe_malloc");

	return p;
}

#define malloc # "use safe_malloc instead"



void *safe_realloc(void *p, size_t s)
{
	p = realloc(p, s);
	if (s > 0 && !p)
		err(1, "safe_realloc");

	return p;
}

#define realloc # "use safe_realloc instead"




#define ALLOCATE(foo, s) do {     \
		foo##_size = s; \
		foo##_used = 0; \
		foo = safe_malloc(foo##_size * sizeof(*foo)); \
	} while (0)

#define ENOUGH(foo) do {        \
		if (foo##_used == foo##_size) \
			foo = safe_realloc(foo, \
				(foo##_size *= 2) * sizeof(*foo)); \
	} while (0)

#define ADD(foo, val) (foo[foo##_used++] = (val))

#define TRIM(foo) (foo = safe_realloc(foo, foo##_used * sizeof(*foo)))




#define CLEANUP do { \
		free_command(last); \
		free(words); \
		free(redirs); \
	} while (0)



Command *parse_command(char *line)
{
#ifdef DEBUG
	warnx("line=`%s`", line);
#endif

	char *p = strchr(line, '#');

	if (p) {
		*p = '\0';
#ifdef DEBUG
		warnx("\trm comment=`%s`", line);
#endif
	}

	Command *last = NULL;
	char *tokenizer1;

	/* iterate over commands in line */
	for (char *p = strtok_r(line, "|", &tokenizer1);
	     p; p = strtok_r(NULL, "|", &tokenizer1)) {

#ifdef DEBUG
		warnx("\tp=`%s`", p);
#endif

		size_t words_used, words_size;
		char **words;

		ALLOCATE(words, 4);

		size_t redirs_used, redirs_size;
		Redir *redirs;

		ALLOCATE(redirs, 2);

		char *tokenizer2;

		/* iterate over words in command */
		for (char *w = strtok_r(p, " \t\n", &tokenizer2);
		     w; w = strtok_r(NULL, " \t\n", &tokenizer2)) {

			Redir tmp;

			/* look for optionalnumber followed bu < or > */
			char *what;

			tmp.fd = (int)strtol(w, &what, 10);
			if (what[0] == '<' || what[0] == '>') {
				tmp.flags = what[0] == '<' ?
					O_RDONLY :
					(O_WRONLY|O_CREAT|O_TRUNC);

				/* default file descriptor, if none given */
				if (what == w)
					tmp.fd = w[0] == '<' ? 0 : 1;

				if (!what[1]) {
					warnx(
						"Need something to the right of `%c`.",
						what[0]);
					CLEANUP;
					return NULL;
				}

				tmp.file = NULL;
				if (what[1] == '&') {
					char *ep;
					long l = strtol(what + 2, &ep, 10);

					if (what[2] && !*ep)
						tmp.ref = (int)l;
					else {
						warnx(
							"Expected number after `&`, got `%s`.",
							what + 2);
						CLEANUP;
						return NULL;
					}
				} else
					tmp.file = what + 1;

				ENOUGH(redirs);
				ADD(redirs, tmp);
#ifdef DEBUG
				if (tmp.file)
					warnx(
					      "\t\tredir `%s`: fd=%d, file=`%s`, flags=%d",
						w, tmp.fd, tmp.file, tmp.flags);
				else
					warnx(
						"\t\tredir `%s`: fd=%d, ref=%d",
						w, tmp.fd, tmp.ref);
#endif
			} else {
#ifdef DEBUG
				warnx("\t\tcmdv[%zu]=`%s`", words_used, w);
#endif
				ENOUGH(words);
				ADD(words, w);
			}

		}

		if (words_used) {

			Command *c = safe_malloc(sizeof(Command));

			ENOUGH(words); /* I'm too lazy to add just one */
			ADD(words, NULL);
			TRIM(words);
			c->argc = words_used - 1;
			c->argv = words;

			TRIM(redirs);
			c->redc = redirs_used;
			c->redv = redirs;

			c->prev = last;
			last = c;

		} else {
			warnx("Invalid empty command.");
			CLEANUP;
			return NULL;
		}

	}

	return last;
}



void free_command(Command *cmd)
{
	while (cmd) {
		Command *prev = cmd->prev;

		free(cmd->argv);
		free(cmd->redv);
		free(cmd);

		cmd = prev;
	}
}
