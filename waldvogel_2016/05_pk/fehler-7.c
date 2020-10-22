/**
 * @author Fabian Klopfer
 * @author Jannik Bamberger
 * @credits 4
 * @bonus10
 */
#include <stdio.h>

/*
 * f takes a pointer to an array of strings and prints the sizeof(int)th
 * Element
 *
 * Errors: assigning p, sizeof(int) is machine dependent, so if an integer is
 *         8 bytes long, the array access is undefined
 *         the parameter of f should be constant in both, or at least the
 *         array content pointer.
 * Style-Errors: as in fehler-1.c, sizeof(int) should go into the [.].
 */
void f(const char * const *p)
{
	const char *t;

	// assign t the pointer to the sizeof(int)th element
	t = p[sizeof(int) - 1];
	// print the Sting pointed to by t
	printf("%s\n", t);
}

/*
 * Initialize an array of strings and call f with it as argument
 * The array should contain const pointers, so the string literals can't
 * be modified.
 */
int main(void)
{
	static const char * const argv[] = { "ab", "cd", "ef", "gh", "ij",
		"kl"};

	f(argv);

	return 0;
}
