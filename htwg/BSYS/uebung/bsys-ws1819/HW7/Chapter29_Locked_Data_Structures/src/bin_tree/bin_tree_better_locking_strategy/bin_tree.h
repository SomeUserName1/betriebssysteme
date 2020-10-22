#ifndef bin_tree_h
#define bin_tree_h

typedef struct node Node;

struct node {
  int             key;
  Node            *left, *right, *parent;
  pthread_mutex_t lock;
};

Node *newNode(Node * parent) {
  Node * n = malloc(sizeof(Node));
  assert(n != NULL);
  assert(pthread_mutex_init(&n->lock, NULL) == 0);
  n->key = 0;
  n->left = NULL;
  n->right = NULL;
  n->parent = parent;
  return n;
}

Node *insert(Node *root, int val) {

  Node * tmp = root;
  pthread_mutex_lock(&tmp->lock);

  while (tmp->key != 0) {

    if (tmp->key < val) {
      if (!tmp->left) {
        tmp->left = newNode(tmp);
      }
      pthread_mutex_lock(&tmp->left->lock);
      tmp = tmp->left;
      pthread_mutex_unlock(&tmp->parent->lock);
    } else if (tmp->key > val) {
      if (!tmp->right) {
        tmp->right = newNode(tmp);
      }
      pthread_mutex_lock(&tmp->right->lock);
      tmp = tmp->right;
      pthread_mutex_unlock(&tmp->parent->lock);
    } else {
      pthread_mutex_unlock(&tmp->lock);
      return root;
      // do nothing / no duplicates
    }
  }
  tmp->key = val;
  pthread_mutex_unlock(&tmp->lock);
  return root;
}

void print_node(Node *node) {
	if (node) {
		print_node(node->left);
		printf("%d ", node->key);
		print_node(node->right);
	}
}

#endif
