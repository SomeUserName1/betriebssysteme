/** \file token.c
 * Token retival and processing.
 * @author Fabian Klopfer
 * @author Jannik Bamberger
 * */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "token.h"

#define MAXOP 32 /** max size of token */

static int back = EOF; /** Pushed back character, or EOF if none. */
int argc; /**argv size*/
char **argv; /** pointer to cmd args array */
int arg = 1; /** String counter variable (0 is the program name)*/
int c = 0; /** char counter variable */

/**
 * Initialize the argument count and argument pointer.
 * @param argcnt Length of argvec
 * @param **argvec Argument vector containing the program name and args.
 * */
void init(int argcnt, char **argvec)
{
	argc = argcnt;
	argv = argvec;
}

/**
 * Get a (possibly pushed back) character from command
 * line args. Works only, if init was invoked before.
 * @return next char or EOF
 * */
static int getch(void)
{
	if (back != EOF) { //there is a char pushed back
		int r = back;

		back = EOF;
		return r;
	}
	if (arg == argc) { //newline to print the result
		arg++;
		return '\n';
	}
	if (arg > argc) { //no more input > quit
		return 'q';
	}
	if (argv[arg][c] == '\0') { //end of single argument string
		arg++;
		c = 0;
		return ' ';
//Warum gibt checkpatch eine warnung, wenn diese Zeile Fehlt?
	} else { //char inside string
		char r = argv[arg][c];

		c++;
		return r;
	}
}

/**
 * Push character back on input.
 * @param c char to add to input
 * */
static void ungetch(int c)
{
	if (back != EOF) {
		printf("error: can only store one char(File: %s Line %d)\n",
			__FILE__, __LINE__);
		exit(1);
	}
	back = c;
}

/**
 * gettoken: get next operator or numeric operand
 * @param *num token storage
 * @return NUMBER if the token is a number
 * */
int gettoken(int *num)
{
	int i, c;
	char buf[MAXOP + 1]; /* one for NUL */

	while (isblank(c = getch()))
		;
	if (!isdigit(c))
		return c; /* it's not a number, may be EOF */
	buf[0] = (char) c;
	i = 1; /* number of digits in buffer */
	while (isdigit(c = getch())) { /* collect integer part */
		if (i >= MAXOP) {
			printf("error: number too long! (File: %s Line %d)\n",
				__FILE__, __LINE__);
			return EOF;
		}
		buf[i++] = (char) c;
	}
	buf[i] = '\0';
	if (c != EOF) /* we have to deal with that character later! */
		ungetch(c);
	*num = atoi(buf); /* store number in return parameter; cf. atof(3) */
	return NUMBER; /* signal that we have found a number */
}
