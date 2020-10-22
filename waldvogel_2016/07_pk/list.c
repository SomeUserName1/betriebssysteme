/*
 * @author Fabian Klopfer
 * @author Jannik Bamberger
 * @credits 20
 * */

#include <stdlib.h>
#include <stdio.h>
#include "list.h"

/*
 * print all values in the list beginning at head
 * */
void print(node_t *head)
{
	node_t *curr = head;

	do {
		printf("[%d]", curr->value);
	} while ((curr = curr->next) != NULL);

	printf("\n");
}

/*
 * create a new list head containing value
 * */
node_t *create(int value)
{
	node_t *head = malloc(sizeof(node_t));

	if (head == NULL)
		return NULL;

	head->value = value;
	head->next = NULL;

	return head;
}

/*
 * add value at the end of the list.
 * */
node_t *push(node_t *head, int value)
{
	node_t *curr = head;

	//go to last node
	while (curr->next != NULL)
		curr = curr->next;

	//create new one
	curr->next = malloc(sizeof(node_t));

	if (curr->next == NULL)
		return NULL;

	// set value
	curr->next->value = value;
	curr->next->next = NULL;

	return curr->next;
}

/*
 * Insert value at into the list, where comp(next, value) is false
 * If the list is sorted according to comp, then it will be sorted after
 * the insertion too. If the insertion failed NULL is returned, otherwise
 * the new node containing value is returned.
 * */
node_t* pushComp(node_t *head, int value, int (*comp)(int, int))
{
	node_t *curr = head;

	// find the position of the new node
	while (curr->next != NULL && comp(curr->next->value, value))
		curr = curr->next;

	node_t *next = curr->next;

	// allocate memory for the new node
	curr->next = malloc(sizeof(node_t));

	// allocation failed, return NULL
	if (curr->next == NULL)
		return NULL;

	// allocation successful
	// if value belongs before head, swap head and the new node to maintain
	// outside pointers to head
	if(!comp(head->value, value)) {
		curr->next->value = head->value;
		head->value = value;
		curr->next->next = next;
		return head; // head contains the new value
	} else { //update new node and return it.
		curr->next->value = value;
		curr->next->next = next;
		return curr->next;
	}
}

/*
 * remove the first element from the list, and return a pointer to it.
 * The new head is updated to point to the new head.
 * The memory can't be freed, because a pointer to the given location
 * shall be returned.
 * */
node_t* pop(node_t **head)
{
	node_t *tmp = *head; //initial head

	*head = tmp->next; //update head
	// tmp->next = NULL;
	return tmp;
}

int lessThan(int a, int b)
{
	return a < b;
}

int greaterThan(int a, int b)
{
	return a > b;
}

int main(void)
{
	node_t *head, *head2;
	int (*comp)(int, int) = lessThan;

	head = create(11);
	pushComp(head, 5, comp);
	pushComp(head, 12, comp);
	pushComp(head, 12, comp);
	pushComp(head, 12, comp);
	pushComp(head, 10, comp);
	pushComp(head, 15, comp);
	pushComp(head, 22, comp);

	print(head);
	// expected output: [5][10][11][12][12][12][15][22]

	head2 = create(11);
	pushComp(head2, 12, comp);
	pushComp(head2, 5, comp);
	pushComp(head2, -1, comp);
	pushComp(head2, 0, comp);
	pushComp(head2, 10, comp);
	pushComp(head2, 15, comp);
	pushComp(head2, 22, comp);

	print(head2);
	// expected output: [-1][0][5][10][11][12][15][22]

	printf("[%d]\n", pop(&head2)->value);
	// expected output: [-1]
	printf("[%d]\n", pop(&head2)->value);
	// expected output: [0]
	push(head2, 2);
	print(head2);
	// expected output: [5][10][11][12][15][22][2]

	return 0;
}
