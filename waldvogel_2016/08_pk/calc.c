/** \file calc.c
 * the main Calculator
 * @author Fabian Klopfer
 * @author Jannik Bamberger
 * @credits 49
 * @bonus10
 *
 * Rückgabewert falsch (-1)
 * */

#include <stdlib.h>
#include <stdio.h>
#include "token.h"
#include "list.h"

#define SUCCESS 1
#define FAIL !SUCCESS

/** stack*/
node_t *head = NULL;

/**
 * Push a value to the stack. If the operation fails return FAIL.
 * @param value int to push to the stack
 * @return SUCCESS or FAIL
 * */
int put(int value)
{
	node_t *new = NULL;

	if (head == NULL) {
		new = create(value);
		if (new != NULL) {
			head = new;
			return SUCCESS;
		}
	} else {
		new = push(&head, value);
		if (new != NULL)
			return SUCCESS;
	}
	printf("error: allocation failed (File: %s Line %d)\n",
		__FILE__, __LINE__);
	return FAIL;
}

/**
 * Get a value from the stack. Return FAIL if an error occures.
 * @param *value Pointer where the value should be stored.
 * @return SUCCESS if successful
 * */
int get(int *value)
{
	if (head != NULL) {
		node_t *n = pop(&head);
		*value = n->value;
		free(n);
		return SUCCESS;
	}
	printf("error: can't get from empty stack (File: %s Line %d)\n",
		__FILE__, __LINE__);
	return FAIL;
}

/**
 * reverse polish calculator. Get input from stdin. q to quit.
 * Returns on input error.
 * @return status code
 */
int main(int argc, char *argv[])
{
	int type; /* kind of input token */
	int op1, op2;

	init(argc, argv);

	while ((type = gettoken(&op1)) != EOF) {
		switch (type) {
		case NUMBER:
			#ifdef DEBUG
			printf("Lese Zahl %d\n", op1);
			#endif
			if (put(op1) != SUCCESS)
				return 0;
			break;
		case '+':
			#ifdef DEBUG
			printf("Berechne Zwischenergebnis\n");
			#endif
			if (get(&op1) && get(&op2)) {
				if (put(op2 + op1) == SUCCESS)
					break;
			}
			return 0;
		case '*':
			#ifdef DEBUG
			printf("Berechne Zwischenergebnis\n");
			#endif
			if (get(&op1) && get(&op2)) {
				if (put(op2 * op1) == SUCCESS)
					break;
			}
			return 0;
		case '-':
			#ifdef DEBUG
			printf("Berechne Zwischenergebnis\n");
			#endif
			if (get(&op1) && get(&op2)) {
				if (put(op2 - op1) == SUCCESS)
					break;
			}
			return 0;
		case '/':
			#ifdef DEBUG
			printf("Berechne Zwischenergebnis\n");
			#endif
			if (get(&op1) && get(&op2)) {
				if (op1 == 0) {
					printf(
						"error: divison by zero (File: %s Line %d)\n",
						__FILE__, __LINE__);
					return 0;
				}
				if (put(op2 / op1) == SUCCESS)
					break;
			}
			return 0;
		case '\n':
			#ifdef DEBUG
			printf("EOL, Ergebnis ausgeben\n");
			#endif
			if (get(&op1) == SUCCESS)
				printf("Ergebnis:\t%d\n", op1);
			break;
		case 'q':
			#ifdef DEBUG
			printf("Programm beenden\n");
			#endif
			return 0;
		default:
			#ifdef DEBUG
			printf("Unbekanntes Token gelesen\n");
			#endif
			printf(
				"error: unknown token %c (File: %s Line %d)\n",
				type, __FILE__, __LINE__);
			return 0;
		}
	}
	return 0;
}
