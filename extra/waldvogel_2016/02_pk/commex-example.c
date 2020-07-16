#include <stdio.h>

/* this is a comment that must be removed */

/* another one
 * more tricky this time
 * / see?
 * still comment
 */

/* Nesting EOL-comments is ok // no harm */

int main(void) {

	printf("A simple test for the comment remover.\n");

	printf("EOL-style somments are introduced by //, but not\n"
	       "inside double quotes \" or single quotes ' and not\n"
	       "inside multi line comments between /* and */.\n\n");

	char c[] = { 'a/*lala*/', '\\', '/', '*', '\n' /*this is comment */ };

	printf("Also character literals '%c' may contain comments.\n",
	       c[0]);

	return 0;
}
