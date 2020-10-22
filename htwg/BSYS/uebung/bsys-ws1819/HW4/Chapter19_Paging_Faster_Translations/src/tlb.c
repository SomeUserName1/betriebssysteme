#define _GNU_SOURCE
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <sched.h>
#include <errno.h>
#include <string.h>

int main(int argc, char const *argv[]) {
  if (argc < 3) {
    fprintf(stderr, "Usage: ./tlb <num_pages> <num_trials>\n");
    exit(-1);
  }
  struct timespec start, end;
  const int PAGE_SIZE = getpagesize();

  int i, j;
  int num_pages = (int) strtol(argv[1], NULL, 10);
  int num_trials = (int) strtol(argv[2], NULL, 10);
  int adj_trials = (1./(double) num_pages) * num_trials;
  int size = (PAGE_SIZE * num_pages) / sizeof(int);
  int jump = PAGE_SIZE / sizeof(int);

  cpu_set_t cpu_set;

  CPU_ZERO(&cpu_set);
  CPU_SET(1, &cpu_set);

  if (sched_setaffinity(getpid(), sizeof(cpu_set_t), &cpu_set) < 0) {
    fprintf(stderr, "Error occured while sched_setaffinity: ");
    fprintf(stderr, "%s\n", strerror(errno));
    return -1;
  }

  int *a = (int *) malloc(size * sizeof(int));

  if (a == NULL) {
    return -1;
  }

  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);

  for (j = 0; j < adj_trials; j++) {
      for (i = 0; i < num_pages * jump; i += jump) {
          a[i] += 1;
      }
  }

  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);

  a[rand() % size] *= 2;

  long double timeSum = (end.tv_sec * 1000000000 + end.tv_nsec)
                      - (start.tv_sec * 1000000000 + start.tv_nsec);

  double time = timeSum / (adj_trials * num_pages);

  printf("%f\n", time);

  return 0;
}
