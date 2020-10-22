#include "slab.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define NELEMS 10

static size_t exponentialGrowth(slabHeader *sh)
{
	printf("\nGrowing exponentially by %zd\n\n", sh->maxElems);
	return sh->maxElems;
}

static size_t linearGrowth(slabHeader *sh)
{
	sh = sh;
	printf("\nGrowing linearily by %d\n\n", NELEMS);
	return NELEMS;
}

void dumpHeader(slabHeader *sh)
{
	slabBlock *sb;
	slabMember *sm;
	size_t count;

	printf("\nDump follows\n");
	printf("- maxElems=%zd usedElems=%zd elemSize=%zd\n",
		sh->maxElems, sh->usedElems, sh->elemSize);
	sb = sh->firstBlock;
	printf("Blocks:\n");
	while (sb != NULL) {
		printf("- Block with %zd elements\n", sb->nElems);
		sb = sb->nextBlock;
	}

	count = 0;
	sm = sh->firstFree;
	while (sm != NULL) {
		count++;
		sm = sm->next;
	}
	printf("%zd free members found\n\n", count);
}

/* Dump list in reverse order, possibly with huge stack requirements */
void dumpList(slabElem *e, int count)
{
	/* We need to test for NULL first,
	 * because main() may call us with NULL
	 */
	if (e != NULL) {
		dumpList(e->next, count+1);
		if (e->next == NULL)
			printf("NULL %s\n", e->text);
		else if (e->next > e)
			printf("---- %s\n", e->text);
		else
			printf("---- %s\n", e->text);
	} else
		printf("%d texts found:\n", count);
}

void cleanBuf(char *s)
{
	while (*s != '\0') {
		if ((unsigned char)*s < ' ')
			*s = ' ';
		s++;
	}
}

int main(int argc, char **argv)
{
	char buf[SLABCHARS];
	slabHeader *sh;
	slabElem *head = NULL;

	if (argc != 2) {
		fprintf(stderr,
			"Usage: %s [lin|exp]\n\t(liner or exponential allocator)\n",
			argv[0]);
		return 1;
	}
	if (strcmp(argv[1], "lin") == 0)
		sh = slabCreate(NELEMS, linearGrowth);
	else
		sh = slabCreate(NELEMS, exponentialGrowth);

	if (sh == NULL) {
		fprintf(stderr, "Cannot allocate slabHeader\n");
		return 1;
	}
	while (fgets(buf, sizeof(buf), stdin) != NULL) {
		if (buf[0] == '\n') {
			/* End of paragraph:
			 * Remove all blocks not starting with alpha chars
			 */
			if (head != NULL) {
				slabElem *e = head;
				slabElem **prev = &head;

				while (e != NULL) {
					if (!isalpha(e->text[0])) {
						/* Dequeue */
						printf("dequeue(%s)\n",
							e->text);
						*prev = e->next;
						slabFree(sh, e);
						e = *prev;
					} else {
						prev = &(e->next);
						e = e->next;
					}
				}
			}
		} else {
			/* Not end of paragraph, enqueue this block */
			slabElem *e = slabAlloc(sh);

			if (e == NULL) {
				fprintf(stderr, "Cannot allocate slabElem\n");
				dumpHeader(sh);
				dumpList(head, 0);
				return 1;
			}
			strncpy(e->text, buf, SLABCHARS);
			cleanBuf(e->text);
			printf("enqueue(%s)\n", e->text);
			/* Insert at head */
			e->next = head;
			head = e;
		}
	}
	printf("\n\nCompleted!\n\n");
	dumpHeader(sh);
	dumpList(head, 0);
	slabDestroy(sh);
	return 0;
}
