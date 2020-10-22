// #define _GNU_SOURCE

#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "concurrent_counter.h"

typedef struct __workerargs_t {
  int        inc;
  counter_t *counter;
} workerargs_t;

void *worker(void *arg);
double get_elapsed_time_in_us(struct timeval *start, struct timeval *end);


int main(int argc, const char *argv[]) {

  if (argc < 3 || argc > 3) {
    fprintf(stderr, "Usage: ./concurrent_counter <int: INCREMENT_VALUE> <int: NUMBER_OF_THREADS>\n");
    exit(-1);
  }

  const int INCREMENT_VALUE = (int) strtol(argv[1], NULL, 10);
  const int NUMBER_OF_THREADS = (int) strtol(argv[2], NULL, 10);

  if (INCREMENT_VALUE < 0) {
    fprintf(stderr, "Please only enter numbers greater or equal than 0 for <int: increment_value>!\n");
    exit(-2);
  }

  if (NUMBER_OF_THREADS < 1) {
    fprintf(stderr, "Please only enter numbers greater than 0 for <int: number_of_threads>!\n");
    exit(-3);
  }

  counter_t counter;
  init(&counter);

  workerargs_t wa;

  wa.inc = INCREMENT_VALUE;
  wa.counter = &counter;

  pthread_t threads[NUMBER_OF_THREADS];

  struct timeval start, end;

  if(gettimeofday(&start, NULL) < 0) {
    fprintf(stderr, "Error occured while getting start time!\n");
    exit(-5);
  }

  for (int i = 0; i < NUMBER_OF_THREADS; i++) {
    pthread_create(&threads[i], NULL, worker, &wa);
  }

  for (int i = 0; i < NUMBER_OF_THREADS; i++) {
    pthread_join(threads[i], NULL);
  }

  if (gettimeofday(&end, NULL) < 0) {
    fprintf(stderr, "Error occured while getting end time!\n");
    exit(-6);
  }

  double elapsed_time_in_us = get_elapsed_time_in_us(&start, &end);

  printf("counter value: %d\n", get_value(&counter));
  printf("expected counter value: %d\n", INCREMENT_VALUE * NUMBER_OF_THREADS);
  printf("ellapsed time [us]: %f\n", elapsed_time_in_us);
  printf("ellapsed time [s]: %f\n", elapsed_time_in_us / 1000000.0);
  exit(0);
}

void *worker(void *args) {
  workerargs_t *wa = (workerargs_t *) args;

  for (int i = 0; i < wa->inc; i++) {
    increment(wa->counter);
  }

  return NULL;
}

double get_elapsed_time_in_us(struct timeval *start, struct timeval *end) {
  double start_time_in_us = start->tv_sec * 1000000.0 + start->tv_usec;
  double end_time_in_us = end->tv_sec * 1000000.0 + end->tv_usec;

  return end_time_in_us - start_time_in_us;
}
