/**
 * @author Fabian Klopfer
 * @author Jannik Bamberger
 * @credits 24
 */
/*
 names?! :D
*/

#include <stdio.h>
#include <ctype.h>

// declare foo1 or move foo1 up here
void foo1(int num, int diff);

//print diagram
void foo2(int uni[])
{
	int diff = 0;

	for (int i = 0; i < 16; i++)
		diff += uni[i];

	for (int i = 1; i < 16; i++) { //array has only 16 fields, not 20
		printf("%d\t", i); //print the word length, add whitespace
		foo1(uni[i], diff);
		putchar('\n');
	}
	//add describtions
	printf("words longer than 15 chars: %d.\n", uni[0]);
	printf("word count: %d\n", diff);
}

//print visualisation
void foo1(int num, int diff)
{
	float p = (float)num / (float)diff;
	int nust = (int)(p * 100);//semicolon and scaling factor missing

	printf("%.2f%% ", 100 * p); //also print % symbol
	for (int i = 0; i < nust; i++)
		putchar('x');
}

//get next wordlength
int foo3(void)
{
	int l = 0;
	int ch;

//drop whitespaces
	while ((ch = getchar()) != EOF && isspace(ch))
		;

	if (ch == EOF)
		return 0;
	else
		l = 1; // was non whitespace

//count word chars
	while ((ch = getchar()) != EOF && !isspace(ch))
		++l;

	return l;
}

int main(void)
{
	int uni[16] = {0}; //wordcount per length, 0 is longer words
	int l;

	while ((l = foo3())) { //loop through all words
		if (l < 16) //17 is out of bounds
			++uni[l];
		else
			++uni[0]; //counts words that are longer than 16 chars
	}

	foo2(uni);

	return 0;
}
