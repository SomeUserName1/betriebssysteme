#ifndef CONCURRENT_LIST_H_
#define CONCURRENT_LIST_H_

#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct __node_t {
  int              key;
  struct __node_t *next;
  pthread_mutex_t  lock;
} node_t;

typedef struct __list_t {
  node_t          *head;
  pthread_mutex_t  lock;
} list_t;

void init(list_t *list);
void insert_key(list_t *list, int key);
int search_key(list_t *list, int key);
void print(list_t *list);

void init(list_t *list) {
  list->head = NULL;
  int rc = pthread_mutex_init(&list->lock, NULL);
  assert (rc == 0);
}

void insert_key(list_t *list, int key) {
  node_t *new = malloc(sizeof(node_t));

  if (new == NULL) {
    fprintf(stderr, "'malloc()' failed!\n");
    return;
  }

  int rc = pthread_mutex_init(&new->lock, NULL);
  assert(rc == 0);

  new->key = key;

  pthread_mutex_lock(&list->lock);
  new->next = list->head;
  list->head = new;
  pthread_mutex_unlock(&list->lock);

}

int search_key(list_t *list, int key) {
  int return_value = -1;

  pthread_mutex_lock(&list->lock);
  node_t *current = list->head;
  pthread_mutex_lock(&current->lock);

  pthread_mutex_unlock(&list->lock);
  while (current) {
    if (current->key == key) {
      return_value = 0;
      break;
    }
    pthread_mutex_lock(&current->next->lock);
    pthread_mutex_unlock(&current->lock);
    current = current->next;

  }
  pthread_mutex_unlock(&current->lock);
  return return_value;
}

void print(list_t *list) {
  node_t * current = list->head;

  printf("list:");

  if (!current) {
    printf(" []\n\n");
    return;
  } else {
    printf(" ");
  }

  while (current) {
    printf("%d ", current->key);
    current = current->next;
  }

  printf("\n\n");
}

#endif
