/** \file testList.c
 * Test cases for list.c
 * @author Fabian Klopfer
 * @author Jannik Bamberger
 * */

#include <stdio.h>
#include "list.h"

/**
 * Test the rem implementation of list.c
 * @return status code
 * */
int main(void)
{
	node_t *head, *headp, *last, *middle;

	head = create(11);
	headp = push(&head, 5);
	push(&head, 12);
	push(&head, 3);
	middle = push(&head, 7);
	push(&head, 10);
	push(&head, 15);
	last = push(&head, 22);

	printf("Expected:	%s\n", "[22][15][10][7][3][12][5][11]");
	printf("Actual:		");
	print(head);

	rem(&head, headp);
	printf("Expected:	%s\n", "[22][15][10][7][3][12][11]");
	printf("Actual:		");
	print(head);

	rem(&head, middle);
	printf("Expected:	%s\n", "[22][15][10][3][12][11]");
	printf("Actual:		");
	print(head);

	rem(&head, last);
	printf("Expected:	%s\n", "[15][10][3][12][11]");
	printf("Actual:		");
	print(head);

	rem(&head, head);
	printf("Expected:	%s\n", "[10][3][12][11]");
	printf("Actual:		");
	print(head);
}
