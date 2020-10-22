/*
 * @author Fabian Klopfer
 * @author Jannik Bamberger
 * @credits 14
 * @bonus10
 *
 * Da nirgendswo stand, wie man den Speicher verdoppeln soll, gab es für die
 * verkettete Liste keinen Abzug. Nur dafür, dass der Speicher nicht wie gefordert
 * verdoppelt wurde (-1).
 *
 * Speicher wird nicht wieder freigegeben (-3)
 */

#include <stdio.h>
#include <stdlib.h>

/* Blocks of allocated memory, containing references to the
predecessor so the chars can be printed in reverse order*/
typedef struct block {
	struct block *predecessor;
	char *begin; //first element
	char *end; //one position after the last element
} block;


/*
 * Allocate a new block of memory and initialize it for usage.
 * @param b pointer to the predecessor
 * @return pointer to the newly allocated block or NULL on failure
 */
block *getNewBlock(block *b)
{
	//struct + CHARS characters
	static const size_t blocksize = sizeof(block) + 1024 * sizeof(char);
	block *tmp;

	tmp = malloc(blocksize); //get mem from system
	if (tmp != NULL) {
		tmp->predecessor = b;
		tmp->begin = (char *) (tmp + 1);
		tmp->end = ((char *) tmp) + blocksize; // > Nimmt sizeof(char) == 1 an

		return tmp;
	}
	//allocation failed, return NULL and print error
	printf("Kann keinen weiteren Speicher allokieren.");
	return NULL;
}

int main(void)
{
	int c; //temp var for read chars
	int sawNewline;
	block *current; //the newest block of memory
	char *storage; //the storage position of the next char

	/* init first block */
	current = getNewBlock(NULL);
	if (current == NULL)
		return 1;

	/* init storage position according to the new block address*/
	storage = current->begin;
	while ((c = getchar()) != EOF) {
		if (storage >= current->end) { //block ended, get new one
			block *tmp = getNewBlock(current);

			if (tmp == NULL)
				return 1;

			current = tmp;
			storage = current->begin;
		}
		*(storage) = (char) c;
		storage++;
	}
	/* storage points to the location of the next char, so we have to go
	back by one */
	storage--;
	sawNewline = 0;
	while (1) {
		if (storage < current->begin) { //block ended, get next one
			current = current->predecessor;
			//end of first block reached, quit
			if (current == NULL) {
				if (sawNewline == 1) // > es wird nicht nur das letzte Zeichen für das abschließende Newline beachtet (-2)
					putchar('\n');
				return 0;
			}
			storage = current->end - 1;
		}
		c = *(storage);
		if (c == '\n') {
			if (sawNewline == 1)
				putchar('\n');
			sawNewline = 1;
		} else {
			putchar(c);
		}
		storage--;
	}
}
