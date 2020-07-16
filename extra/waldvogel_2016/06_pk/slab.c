/*
 * @author Fabian Klopfer
 * @author Jannik Bamberger
 * @credits 30
 * @bonus10
 *
 * Respekt. Die lock/unlock Funktionen sind ein bisschen großzügig, ansonsten
 * spitzen Leistung.
 * */

#include "slab.h"
#include <stdlib.h>
#include <assert.h>

/* "Abstract" functions
 * mutex up or down for an implicit mutex for the given pointer
 * lock(x)   = synchronized(x) {
 * unlock(x) = }
 */
void lock(void *ptr) { ptr = ptr; }
void unlock(void *ptr) { ptr = ptr; }

/**
 * Create a new slabBlock with n elements. Return a pointer to the block.
 *
 * */
static slabBlock *slabGrow(slabHeader *sh, size_t nElems)
{
	lock(sh);
	slabBlock *sb;

	assert(nElems > 0);
	/* The slabBlock already includes the first slabMember */
	sb = (slabBlock *)malloc(sizeof(slabBlock)
				+ (nElems-1) * sizeof(slabMember));
	if (sb != NULL) {
		sb->nElems = nElems;
		sb->nextBlock = sh->firstBlock;
		sh->firstBlock = sb;
		sh->maxElems = sh->maxElems + nElems;
		//link all new Elements
		for (size_t i = 1; i < nElems; i++)
			sb->m[i - 1].next = sb->m + i;
		sb->m[nElems - 1].next = sh->firstFree;
		sh->firstFree = sb->m;
	}
	unlock(sh);
	return sb;
}

/* Create/destroy the slabs */
slabHeader *slabCreate(size_t nElems, growFunc growBy)
{
	slabHeader *sh;

	sh = (slabHeader *)malloc(sizeof(slabHeader));
	if (sh != NULL) {
		slabBlock *sb;

		sh->maxElems = 0;
		sh->usedElems = 0;
		sh->elemSize = sizeof(slabMember);
		sh->growBy = growBy;
		sh->firstBlock = NULL;
		sh->firstFree = NULL;
		sb = slabGrow(sh, nElems);
		if (sb == NULL)
			return NULL;
	}
	return sh;
}

void slabDestroy(slabHeader *sh)
{
	lock(sh);
	slabBlock *tmp;

	//free all blocks
	while (sh->firstBlock != NULL) {
		tmp = sh->firstBlock;
		sh->firstBlock = tmp->nextBlock;
		free(tmp);
	}

	free(sh); //free head
	unlock(sh);
}

/* Allocate/free a single element from within the slab */
slabElem *slabAlloc(slabHeader *sh)
{
	slabMember *tmp;

	lock(sh);
	// there is no more space -> allocate new space
	if (sh->maxElems - sh->usedElems <= 0) {
		slabBlock *sb;

		sb = slabGrow(sh, sh->growBy(sh));
		if (sb == NULL) //allocation failed -> can't return slabElem
			return NULL;
	}

	//there is space, update usedElems, firstFree and return first free one
	tmp = sh->firstFree;
	sh->usedElems = sh->usedElems + 1;
	sh->firstFree = tmp->next;
	unlock(sh);
	return &(tmp->e); //return ptr to slab element
}

void slabFree(slabHeader *sh, slabElem *elem)
{
	lock(sh);
	// add new element at first position
	((slabMember *) elem)->next = sh->firstFree;
	sh->firstFree = (slabMember *) elem;
	sh->usedElems = sh->usedElems - 1;
	unlock(sh);
}
