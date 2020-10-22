/*
 * @author Fabian Klopfer
 * @author Jannik Bamberger
*/

#include <unistd.h>

#define SLABCHARS 20

/* Data structures */
union slabMember;
struct slabBlock;
struct slabHeader;
typedef size_t (*growFunc)(struct slabHeader *);

typedef struct slabElem {
	struct slabElem *next;
	char text[SLABCHARS];
} slabElem;

typedef struct slabHeader {
	size_t maxElems;
	size_t usedElems;
	size_t elemSize;
	growFunc growBy;
	union slabMember *firstFree;
	struct slabBlock *firstBlock;
} slabHeader;

typedef union slabMember {
	slabElem e;
	union slabMember *next;
} slabMember;

typedef struct slabBlock {
	struct slabBlock *nextBlock;
	size_t nElems;
	slabMember m[1];
} slabBlock;

/* Methods */

/* Create/destroy the slabs */
slabHeader *slabCreate(size_t nElems, growFunc growBy);
void slabDestroy(slabHeader *sh);

/* Allocate/free a single element from within the slab */
slabElem *slabAlloc(slabHeader *sh);
void slabFree(slabHeader *sh, slabElem *elem);
