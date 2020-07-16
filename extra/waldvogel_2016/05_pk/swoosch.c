/**
 * @author Fabian Klopfer
 * @author Jannik Bamberger
 * @credits 19
 * @bonus10
 *
 * Fehler 2 nicht gefunden: Mehrere spaces (-5)
 */
#include <stdio.h>
#include <ctype.h>

/* Swoosch takes a pointer to a string (char pointer). Swoosch loops over
 * the characters of the String, until the String ends or there is a space.
 * The String pointer is incremented, so it points to the found space or nul.
 * Then it is checked, if this location is a space. If it's a space, nul is
 * written there and the pointer is incremented again. Finally the initial
 * location of the pointer is returned. Simplified, swoosch writes nul after
 * the first word, sets the string beginning to the first char after nul and
 * returns the initial beginning of the string.
 */
char *swoosch(char **x)
{
	// x is a pointer to a string (char pointer)
	// > und wieso? (-3)
	// r is the initial begin of the string. It won't be modified.
	char *r = *x;

	// until there is a space or nul at the start of the string, set the
	// start one position to the right.
	// > Warum war die zweite Abbruchbedingung nötig? (-1)
	while (!isspace(**x) && **x != '\0')
		(*x)++;

	// if there is a space, replace it with nul set the start one to the
	// right.
	if (isspace(**x))
		*(*x)++ = '\0';

	// return the initial start of the string
	return r;
}



int main(void)
{
	// init a writable string
	char arr[36] = "42 is the answer to which question?";

	// s is a pointer to the start of arr.
	// > die ganze Zeit? (-2)
	// w is the start of the string before it is passed to swoosh.
	// the loop prints every word of the string to a single line.
	for (char *s = arr, *w = swoosch(&s); //init s and w
		 *w; //end of string reached, if *w == nul
		w = swoosch(&s)) //move w to next word
		printf("%s\n", w); //print the word on a single line

	return 0;
}
