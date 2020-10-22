/*
 * @author Fabian Klopfer
 * @author Jannik Bamberger
 * */

#ifndef builtins_nasvgqzIRhPb
#define builtins_nasvgqzIRhPb

struct builtin_func {
	const char *name;
	const char *help;
	void (*func)(int argc, char **argv);
};

extern struct builtin_func builtin_funcs[];

#endif
