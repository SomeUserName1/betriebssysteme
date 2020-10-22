/**
 * @author Fabian Klopfer
 * @author Jannik Bamberger
 * @credits 4
 * @bonus10
 */
#include <stdio.h>


/*
* Same as in fehler-1.c only that the char array contains
* "Ich liebe Zeichenketten! and had the wrong length (11 instead of 25)"
*/
int main(void)
{
	char arr[25] = "Ich liebe Zeichenketten!";

	printf("%s\n", arr);

	return 0;
}
