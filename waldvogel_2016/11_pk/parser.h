/*
 * @author Fabian Klopfer
 * @author Jannik Bamberger
 * */

#ifndef parser_7FyMvlsPdp66
#define parser_7FyMvlsPdp66



/* A redirection is represented by a `Redir` struct, the field `fd` is
 * the new descriptor to be generated.  If `file` is NULL, then this
 * redirection duplicates the file descriptor given in `ref`.
 * Otherwise, it opens the file named `file`, passing `flags` to
 * open(2).
 */

typedef struct redir Redir;
struct redir {
	int fd;     /* descriptor to assign */
	char *file; /* file to open, or NULL if duplicating */
	int flags;  /* for use with open(2) */
	int ref;    /* fd to duplicate */
};



/* A pipeline is represented by a linked list of `Command`s, each
 * pointing to the previous one given on the command line:
 *
 *     ls /etc /nope 2>errlog | grep -F .d | sed s/\.d$// | sort
 *
 * is represented as
 *
 *     [sort] -> [sed] -> [grep] -> [ls]
 *
 * where [foo] is respective `Command` struct.  Each `Command`
 * contains:
 *
 *   * The argument vector `argv` suitable for passing to, e.g.,
 *     execvp(3).  So `argv[argc]` is NULL.
 *
 *   * A vector of redirections `redv`, in the order given on the
 *     command line.  This is not NULL-terminated, but `redc` contains
 *     the number of redirections.
 *
 * In above example, `redc` is 0 for all commands except `ls`, where
 * it is 1, and `redv[0]` contains the `Redir`ection described by
 * "2>errlog".
 */

typedef struct command Command;
struct command {
	char **argv;
	size_t argc;
	Redir *redv;
	size_t redc;
	struct command *prev;
};



/* Parse the input `line`, building a list of `Command` structs
 * representing the pipeline.  All memory allocated to that list can
 * be freed with `free_command`, see below.
 *
 * If the parser fails to interpret the passed `line`, it will return
 * NULL, and all internally allocated memory should be `free`d
 * automatically.
 */

Command *parse_command(char *line);

/* Free a list of commands, beginning with `cmd`. */

void free_command(Command *cmd);



/* Two frontend functions for malloc(3) and realloc(3).  These are
 * quaranteed to be successful, or to terminate the program with a
 * usable error message.  So it is not necessary to check the returned
 * pointer for being NULL.
 */

void *safe_malloc(size_t s);

void *safe_realloc(void *p, size_t s);


#endif
