/** \file list.c
 * Stack implementation.
 * @author Fabian Klopfer
 * @author Jannik Bamberger
 * */

#include <stdlib.h>
#include <stdio.h>
#include "list.h"

void print(node_t *head)
{
	node_t *curr = head;

	do {
		printf("[%d]", curr->value);
	} while ((curr = curr->next) != NULL);

	printf("\n");
}

node_t *create(int value)
{
	node_t *head = malloc(sizeof(node_t));

	if (head == NULL)
		return NULL;

	head->value = value;
	head->next = NULL;

	return head;
}

node_t *push(node_t **head, int value)
{
	node_t *oldHead = *head;

	*head = create(value);

	if (*head != NULL)
		(*head)->next = oldHead;

	return *head;
}

node_t *pop(node_t **head)
{
	node_t *el = *head;

	*head = (el != NULL) ? el->next : NULL;

	return el;
}

/**
 * Remove specific element from stack. Update user visible stack
 * head if nessecary.
 * @param **head stack end
 * @param *element Element to remove
 * */
void rem(node_t **head, node_t *element)
{
	node_t *curr = *head;

	if (curr == NULL)
		return;
	if (curr == element) { //delete head
		if (curr->next != NULL) //next elem availible
			*head = curr->next; //update head pointer
		else
			*head = NULL;
		free(curr);
		return;
	}
	while (curr->next != NULL) {
		if (curr->next == element) {
			node_t *del = curr->next;

			curr->next = del->next;
			free(del);
			return;
		}
		curr = curr->next;
	}
}
