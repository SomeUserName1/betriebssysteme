/**
 * @author Fabian Klopfer
 * @author Jannik Bamberger
 * @credits 6
 * @bonus10
 */
#include <stdio.h>

/*
 * Initializes an int array of length 5 containing the numbers from 1 to 5 and
 * a pointer to the first element after the array. Then print the the second
 * and last value of the array.
 *
 * Errors: None
 * Style-Errors: as fehler-1.c
*/
int main(void)
{
	int a[5] = { 1, 2, 3, 4, 5 };
	// pointer to first element of array incremented by one array length,
	// so it points to the first position after the array and is
	// casted to (int *)
	int *ptr = (int *)(&a + 1);

	// print the second and last element of a
	// *(ptr - 1) decrements ptr by one int size instead of one array size,
	// because the pointer was casted to an int pointer.
	//same as printf("%d %d\n", a[1], a[4];
	printf("%d %d\n", *(a + 1), *(ptr - 1));

	return 0;
}
