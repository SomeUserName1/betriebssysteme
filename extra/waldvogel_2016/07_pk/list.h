/*
 * @author Fabian Klopfer
 * @author Jannik Bamberger
 * */
typedef struct node {
  struct node *next;
  int value;
} node_t;

int lessThan(int a, int b);
int greaterThan(int a, int b);

node_t* create(int value);
node_t* push(node_t *head, int value);
node_t* pushComp(node_t *head, int value, int (*comp)(int, int));
node_t* pop(node_t **head);

void print(node_t *head);
