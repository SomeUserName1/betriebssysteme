/**
 * @author Fabian Klopfer
 * @author Jannik Bamberger
 */

#ifndef RSH_BUILTIN_H
#define RSH_BUILTIN_H
#define BUILTIN_COUNT 4

typedef struct builtin_func {
	/* Name des Kommandos */
	const char *name;
	/* Kurze Beschreibung */
	const char *help;

	/* Funktion die aufgerufen werden soll.
	* Argumente analog zu `main`: `argc` ist die Zahl der Token.
	* `argv` enthalt alle Token, `argv[argc]` ist immer `NULL`.
	*/
	int (*func)(int argc, char **argv);
} builtin_func;

extern builtin_func builtin_funcs[];

#endif //RSH_BUILTIN_H
