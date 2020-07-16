/**
 * @author Fabian Klopfer
 * @author Jannik Bamberger
 * @credits 4
 * @bonus10
 */
#include <stdio.h>

/*
 * Initializes a char pointer on a the chars "UNIX" and prints the 4th element.
 * Errors: arguments of printf, missing const keyword
 * Style-Errors: pointer access, same issues as fehler-1.c
 */
int main(void)
{
	const char *ptr = "UNIX";
	// Warum brauchen wir const?

	printf("%c\n", ptr[3]); //gebe den vierten Buchstabe von ptr aus.
	return 0;
}
