/**
 * @author Fabian Klopfer
 * @author Jannik Bamberger
 * @credits 3
 * @bonus10
 */

#include <stdio.h>

/*
 * Declares and initializes a char array containing the word "Network\0" and
 * prints it
 * Style errors:
 * - whitspaces instead of tabs
 * - space between function and parantheses containing the arguments
 * - no empty line after declaration
 * - trailing whitespace, spaces at the start of a line
 */
int main(void)
{
	char arr[8] = "Network";
	// Warum habt ihr const hinzugefügt?
	// Fehlerbeschreibung? (-1)

	printf("%s\n", arr); //print array as String until '\0' is reached
	return 0;
}
