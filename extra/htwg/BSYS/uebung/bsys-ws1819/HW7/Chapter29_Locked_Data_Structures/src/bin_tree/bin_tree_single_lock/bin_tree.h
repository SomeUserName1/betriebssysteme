typedef struct ___bin_tree_node_t {
  int                        data;
	struct ___bin_tree_node_t *left;
	struct ___bin_tree_node_t *right;
} bin_tree_node_t;

typedef struct __bin_tree_t {
  bin_tree_node_t *root;
  pthread_mutex_t  lock;
} bin_tree_t;

void init(bin_tree_t *bin_tree);
bin_tree_node_t *create_new_node(int value);
void insert_value_into_bin_tree(bin_tree_t *bin_tree, int value);
bin_tree_node_t *insert_into_node(bin_tree_node_t *node, int value);
void print_node(bin_tree_node_t *node);
void print_bin_tree(bin_tree_t *bin_tree);

void init(bin_tree_t *bin_tree) {
  bin_tree->root = NULL;
  pthread_mutex_init(&bin_tree->lock, NULL);
}

bin_tree_node_t *create_new_node(int value) {
  bin_tree_node_t *new_node = (bin_tree_node_t *) malloc(sizeof(bin_tree_node_t));

  if (new_node == NULL) {
    fprintf(stderr, "'malloc()' in 'new_node()' failed!\n");
    exit(-1);
  }

  new_node->data = value;
  new_node->left = NULL;
  new_node->right = NULL;
  return new_node;
}

void insert_value_into_bin_tree(bin_tree_t *bin_tree, int value) {
  pthread_mutex_lock(&bin_tree->lock);
  bin_tree->root = insert_into_node(bin_tree->root, value);
  pthread_mutex_unlock(&bin_tree->lock);
}

bin_tree_node_t *insert_into_node(bin_tree_node_t *node, int value) {
	if (node == NULL) {
    return create_new_node(value);
  }

	if (value < node->data) {
    node->left = insert_into_node(node->left, value);
  }
	else {
    node->right = insert_into_node(node->right, value);
  }

	return node;
}

bin_tree_node_t *get_min_value_of_node(bin_tree_node_t *node) {
	bin_tree_node_t *current = node;

	while (current->left != NULL) {
    current = current->left;
  }

	return current;
}

void print_node(bin_tree_node_t *node) {
	if (node != NULL) {
		print_node(node->left);
		printf("%d ", node->data);
		print_node(node->right);
	}
}

void print_bin_tree(bin_tree_t *bin_tree) {
  printf("Binary tree (inorder traversed): ");
  print_node(bin_tree->root);
  printf("\n");
}
