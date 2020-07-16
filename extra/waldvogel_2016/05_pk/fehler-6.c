/**
 * @author Fabian Klopfer
 * @author Jannik Bamberger
 * @credits 4
 * @bonus10
 */
#include <stdio.h>

/*
 * Prints the 7th element of the array
 *
 * Errors: buf length doesn't need to be 10.
 * Style-Errors: as in fehler-1.c
 */
int main(void)
{
	char p;
	char buf[8] = { 1, 2, 3, 4, 5, 6, 9, 8 };

	p = buf[6];  // = *(buf + 6) = *((buf + 1) + 5)
	printf("%d\n", p);

	return 0;
}
