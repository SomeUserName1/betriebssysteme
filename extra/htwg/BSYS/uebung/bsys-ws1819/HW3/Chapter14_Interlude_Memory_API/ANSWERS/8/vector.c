#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "vector.h"

struct vector {
  char* data;
  size_t size;
};

vector_t* newVector(vector_t *vector, size_t size) {
  vector = malloc(sizeof(vector_t));
  vector->data = (char*) malloc(size);
  if (vector->data == NULL) {
    fprintf(stderr, "Could not build new vector..\n");
    return (void*) -1;
  }
  vector->size = size;
  memset(vector->data, 1, vector->size - 1);
  vector->data[vector->size-1] = 0;
  return vector;
}

vector_t* alter(vector_t *vector, int size) {
  size_t newSize = vector->size + size;
  vector->data = (char*) realloc(vector->data, newSize);
  if (vector->data == NULL) {
    fprintf(stderr, "Could not alter vector!\n");
    return (void*) -1;
  } else {
    vector->size = newSize;
    memset(vector->data, 1, vector->size - 1);
    vector->data[vector->size-1] = 0;
    return vector;
  }
}

int check(char* data) {
  int size = 0;
  char* i = 0;
  if (data) {
    i = data;
    while (*i != 0) {
      size++;
      i = (data + size);
    }
  }
  return size;
}

int main(void) {
  size_t sizeToAllocate = 100;
  printf("Size to grow/shrink: %d\n\n", (int) sizeToAllocate);

  vector_t *c = NULL;
  c = newVector(c, 100);

  printf("Size of vector: %d\n", (int) c->size);
  printf("Check: %d\n\n", check(c->data));
  alter(c, sizeToAllocate);

  printf("Size of vector after grow: %d\n", (int) c->size);
  printf("Check: %d\n\n", check(c->data));

  alter(c, -sizeToAllocate);

  printf("Size of vector after shrink: %d\n", (int) c->size);
  printf("Check: %d\n\n", check(c->data));

  alter(c, 50);

  printf("Size of vector after second grow: %d\n", (int) c->size);
  printf("Check: %d\n\n", check(c->data));

  alter(c, -20);

  printf("Size of vector after second shrink: %d\n", (int) c->size);
  printf("Check: %d\n", check(c->data));

  free(c->data);
  free(c);

  return 0;
}
