#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "bin_tree.h"

typedef struct __workerargs_t {
  int         start;
  int         end;
  bin_tree_t  *node;
} workerargs_t;

void *worker(void *args);
double get_elapsed_time_in_us(struct timeval *start, struct timeval *end);

int main(int argc, const char* argv[]) {

  if (argc < 3 || argc > 3) {
    fprintf(stderr, "Usage: ./bin_tree <int: number_of_values_to_insert> <int: number_of_threads>\n");
    exit(-1);
  }

  const int NUMBER_OF_VALUES_TO_INSERT = (int) strtol(argv[1], NULL, 10);
  const int NUMBER_OF_THREADS = (int) strtol(argv[2], NULL, 10);

  if (NUMBER_OF_VALUES_TO_INSERT < 0) {
    fprintf(stderr, "Please only enter numbers greater or equal than 0 for <int: increment_value>!\n");
    exit(-2);
  }

  if (NUMBER_OF_THREADS < 1) {
    fprintf(stderr, "Please only enter numbers greater than 0 for <int: number_of_threads>!\n");
    exit(-3);
  }

  bin_tree_t root;
  init(&root);

  workerargs_t wa[NUMBER_OF_THREADS];

  for (int i = 0; i < NUMBER_OF_THREADS; i++) {
    wa[i].start = 1 + i * NUMBER_OF_VALUES_TO_INSERT;
    wa[i].end = (i + 1) * NUMBER_OF_VALUES_TO_INSERT;
    wa[i].node = &root;
  }
  pthread_t threads[NUMBER_OF_THREADS];

  struct timeval start, end;

  if(gettimeofday(&start, NULL) < 0) {
    fprintf(stderr, "Error occured while getting start time!\n");
    exit(-5);
  }

  for (int i = 0; i < NUMBER_OF_THREADS; i++) {
    pthread_create(&threads[i], NULL, worker, &wa[i]);
  }

  for (int i = 0; i < NUMBER_OF_THREADS; i++) {
    pthread_join(threads[i], NULL);
  }

  if (gettimeofday(&end, NULL) < 0) {
    fprintf(stderr, "Error occured while getting end time!\n");
    exit(-6);
  }

  double elapsed_time_in_us = get_elapsed_time_in_us(&start, &end);

  // print_bin_tree(&bin_tree);
  printf("ellapsed time [us]: %f\n", elapsed_time_in_us);
  printf("ellapsed time [s]: %f\n", elapsed_time_in_us / 1000000.0);
}

/* This function pointer is used by the threads specified in the main() method.
   It inserts values into a binary tree. */
void *worker(void *args) {
  workerargs_t *wa = (workerargs_t *) args;

  for (int i = wa->start; i <= wa->end; i++) {
    insert_value_into_bin_tree(wa->node, i);
  }

  return NULL;
}

/* This function returns the ellapsed time in us. */
double get_elapsed_time_in_us(struct timeval *start, struct timeval *end) {
  double start_time_in_us = start->tv_sec * 1000000.0 + start->tv_usec;
  double end_time_in_us = end->tv_sec * 1000000.0 + end->tv_usec;

  return end_time_in_us - start_time_in_us;
}
