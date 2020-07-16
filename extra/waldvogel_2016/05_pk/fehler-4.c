/**
 * @author Fabian Klopfer
 * @author Jannik Bamberger
 * @credits 4
 * @bonus10
 */
#include <stdio.h>


/*
 * Initializes a char array containing "Uni Konstanz\0" and a char pointer on
 * "Uni Konstanz\0", prints both, and the 3rd element of the data from the
 * address the char ptr points to/of the char array. Prints the lenght of the
 * char array and the length of a adress on your machine in bytes
 * (64-bit = 8 Bytes, 32-bit = 4 bytes)
 *
 * Errors: String termination symbol in string literal
 * Style-Errors: same as fehler-1.c
 */
int main(void)
{
	char array[] = "Uni Konstanz";
	const char *str = "Uni Konstanz";

	printf("%s %c\n", array, array[2]);
	printf("%s %c\n", str, str[2]);
	/*len of array and size of pointer*/
	printf("%zu %zu\n", sizeof(array), sizeof(str));

	return 0;
}
