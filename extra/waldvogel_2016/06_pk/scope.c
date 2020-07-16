/*
 * @author Fabian Klopfer
 * @author Jannik Bamberger
 * @credits 10
 */

#include <stdio.h>

/**
 * 1. Es werden a und b deklariert und initialisiert, so dass sie für allen
 * Code darunter gültig sind. Dann wird g deklariert und ist ebenfalls für
 * alles darunter gültig. In g wird c deklariert und ist ab der deklaration
 * bis zum Ende von g gültig. Es wird noch ein a deklariert, welches das
 * bestehende a überdeckt und bis an das Ende von g gültig ist. In dem if
 * werden a und b deklatiert, die jeweils die bestehenden Variablen mit
 * gleichem Name überdecken. Sind bis ans Ende des if-Blocks gültig. Zum
 * Schluss werden noch f und main deklariert, und sind jeweils ab der
 * Deklaration bis nach ganz unten gültig.
 *
 * 2. Ein Vorteil ist, dass unter Umständen Speicher gespart wird, wenn die
 * Variablen nur in einem kleinen Abschnitt benötigt werden. Dann müssen sie
 * nicht während der gesamten Laufzeit im Speicher gehalten werden.
 * Es hat allerdings den Nachteil, dass Variablen die sehr oft benötigt
 * werden, und deren Wert sich nicht ändert, jedes mal neu initialisiert
 * werden müssen.
 *
 * 3. Die Funktion f wird aufgerufen bevor sie deklariert wurde. Dies kann
 * behoben werden indem "int f(void);" unter die include-Statements
 * geschrieben wird.
 *
 * */

int a = 1, b = 2; //begin a1, b1; decl a1 (a), b1 (b)

int g(void) //begin g
{
	int c = f();//begin c; decl c

	printf("%i\n", a);

	int a = 5; //begin a2; end a1; decl a2 (a)

	if (c > 0) {
		int a = 3; //begin a3; end a2; decl a3 (a)

		printf("%i\n", a);

		int b = 4; //begin b2; decl b2 (b)

		printf("%i\n", b);
	} //end a3, b2; begin a2

	printf("%i\n", a);

	return 0;
} //end a2, c; begin a1

int f(void) //begin f
{
	return a + b;
}

int main(void) //begin main
{
	g();

	return 0;
}
//end a1, b1, g, f, main
