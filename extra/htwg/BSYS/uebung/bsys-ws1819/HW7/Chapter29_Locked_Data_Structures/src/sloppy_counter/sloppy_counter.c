#define _GNU_SOURCE
#define NUMBER_OF_CPUS 4
#define MAX_COUNT_VALUE 4000000

#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "sloppy_counter.h"

typedef struct __workerargs_t {
  int        amount;
  counter_t *counter;
} workerargs_t;

void *worker(void * args);
double get_elapsed_time_in_us(struct timeval *start, struct timeval *end);

int main(int argc, const char *argv[]) {

  if (argc < 4 || argc > 4) {
    fprintf(stderr,
      "Usage: ./sloppy_counter <int: increment_value> <int: threshold> <int: number_of_threads>\n"
    );
    exit(-1);
  }

  const int INCREMENT_VALUE = (int) strtol(argv[1], NULL, 10);
  const int TRESHOLD = (int) strtol(argv[2], NULL, 10);
  const int NUMBER_OF_THREADS = (int) strtol(argv[3], NULL, 10);

  if (INCREMENT_VALUE < 0) {
    fprintf(stderr,
      "Please only enter numbers greater or equal than 0 for <int: INCREMENT_VALUE>!\n"
    );
    exit(-2);
  }

  if (TRESHOLD < 0) {
    fprintf(stderr,
      "Please only enter numbers greater or equal than 0 for <int: TRESHOLD>!\n"
    );
    exit(-3);
  }

  if (NUMBER_OF_THREADS < 1) {
    fprintf(stderr,
      "Please only enter numbers greater than 0 for <int: NUMBER_OF_THREADS>!\n"
    );
    exit(-4);
  }

  counter_t counter;
  init(&counter, TRESHOLD);

  workerargs_t wa;
  wa.amount = INCREMENT_VALUE;
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

  printf("counter value: %d\n", get_global_count_value(&counter));
  printf("expected counter value: %d\n", INCREMENT_VALUE * NUMBER_OF_THREADS);
  printf("elapsed time [us]: %f\n", elapsed_time_in_us);
  printf("elapsed time [s]: %f\n", elapsed_time_in_us / 1000000.0);

  exit(0);
}

void *worker(void *args) {
  workerargs_t *wa = (workerargs_t *) args;

  for (int i = 0; i < wa->amount; i++) {
    update(wa->counter, pthread_self(), 1);
  }

  return NULL;
}

double get_elapsed_time_in_us(struct timeval *start, struct timeval *end) {
  double start_time_in_us = start->tv_sec * 1000000.0 + start->tv_usec;
  double end_time_in_us = end->tv_sec * 1000000.0 + end->tv_usec;
  return end_time_in_us - start_time_in_us;
}
