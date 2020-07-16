/** \file list.h
 * list definitions
 * @author Fabian Klopfer
 * @author Jannik Bamberger
 * */
#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
#define FOO 1

typedef struct node {
	struct node *next;
	int value;
} node_t;

int lessThan(int a, int b);
int greaterThan(int a, int b);

node_t *create(int value);
node_t *push(node_t **head, int value);
node_t *pop(node_t **head);
void rem(node_t **head, node_t *element);

void print(node_t *head);

#ifndef FOO
#define FOO
#endif
#endif
