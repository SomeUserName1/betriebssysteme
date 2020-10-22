#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "concurrent_list.h"

typedef struct __fill_workerargs_t {
  int     start;
  int     end;
  list_t *list;
} fill_workerargs_t;

typedef struct __search_workerargs_t {
  int     max_key;
  list_t *list;
} search_workerargs_t;

void *fill_worker(void *args);
void *search_worker(void *args);
double get_elapsed_time_in_us(struct timeval *start, struct timeval *end);

int main(int argc, const char *argv[]) {

  if (argc < 3 || argc > 3) {
    fprintf(stderr, "Usage: ./concurrent_list <int: NUMBER_OF_KEYS_TO_INSERT> <int: NUMBER_OF_THREADS>\n");
    exit(-1);
  }

  const int NUMBER_OF_KEYS_TO_INSERT = (int) strtol(argv[1], NULL, 10);
  const int NUMBER_OF_THREADS = (int) strtol(argv[2], NULL, 10);

  if (NUMBER_OF_KEYS_TO_INSERT < 0) {
    fprintf(stderr, "Please only enter numbers grather or equals than 0 for <int: NUMBER_OF_KEYS_TO_INSERT>!\n");
    exit(-2);
  }

  if (NUMBER_OF_THREADS < 1) {
    fprintf(stderr, "Please only enter numbers grather than 0 for <int: NUMBER_OF_THREADS>!\n");
    exit(-3);
  }

  list_t list;
  init(&list);

  fill_workerargs_t fwa[NUMBER_OF_THREADS];

  for (int i = 0; i < NUMBER_OF_THREADS; i++) {
    fwa[i].start = 1 + i * NUMBER_OF_KEYS_TO_INSERT;
    fwa[i].end = (i + 1) * NUMBER_OF_KEYS_TO_INSERT;
    fwa[i].list = &list;
  }

  search_workerargs_t swa;
  swa.max_key = NUMBER_OF_THREADS * NUMBER_OF_KEYS_TO_INSERT;
  swa.list = &list;

  pthread_t threads[NUMBER_OF_THREADS];

  struct timeval start, end;

  if(gettimeofday(&start, NULL) < 0) {
    fprintf(stderr, "Error occured while getting start time!\n");
    exit(-5);
  }

  for (int i = 0; i < NUMBER_OF_THREADS; i++) {
    pthread_create(&threads[i], NULL, fill_worker, &fwa[i]);
  }

  for (int i = 0; i < NUMBER_OF_THREADS; i++) {
    pthread_join(threads[i], NULL);
  }

  for (int i = 0; i < NUMBER_OF_THREADS; i++) {
    pthread_create(&threads[i], NULL, search_worker, &swa);
  }

  for (int i = 0; i < NUMBER_OF_THREADS; i++) {
    pthread_join(threads[i], NULL);
  }

  if (gettimeofday(&end, NULL) < 0) {
    fprintf(stderr, "Error occured while getting end time!\n");
    exit(-6);
  }

  double elapsed_time_in_us = get_elapsed_time_in_us(&start, &end);

  // print(&list);
  printf("elapsed time [us]: %f\n", elapsed_time_in_us);
  printf("elapsed time [s]: %f\n", elapsed_time_in_us / 1000000.0);
  exit(0);
}

void *fill_worker(void* args) {
  fill_workerargs_t *fwa = (fill_workerargs_t *) args;

  for (int i = fwa->start; i <= fwa->end; i++) {
    insert_key(fwa->list, i);
  }

  return NULL;
}

void *search_worker(void* args) {
  search_workerargs_t *swa = (search_workerargs_t *) args;

  for (int i = 1; i < swa->max_key; i++) {
    int found = search_key(swa->list, i);
    assert(found == 0);
  }

  return NULL;
}

double get_elapsed_time_in_us(struct timeval *start, struct timeval *end) {
  double start_time_in_us = start->tv_sec * 1000000.0 + start->tv_usec;
  double end_time_in_us = end->tv_sec * 1000000.0 + end->tv_usec;

  return end_time_in_us - start_time_in_us;
}
