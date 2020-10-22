#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

// function declaration
double get_gettimeofday_costs(void);

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "No arguments were passed!\nUsage: '$ "
                    "./context_switch_cost <nloops>'.\n");
    exit(-1);
  } else if (argc > 2) {
    fprintf(stderr, "Too many arguments were passed!\nUsage: '$ "
                    "./context_switch_cost <nloops>'.\n");
    exit(-2);
  }

  int iterations = strtol(argv[1], NULL, 10);

  if (iterations == 0) {
    fprintf(stderr, "Please only enter numbers greater than 1!\n");
    exit(-3);
  }

  double sum = 0;
  for (int i = 0; i < iterations; i++) {
    double elapsed_time = get_gettimeofday_costs();
    sum += elapsed_time;

    printf("Loop: %d\n", i + 1);
    printf("elapsed_time: %lfus.\n", elapsed_time);
    printf("\n");
  }

  printf("average elapsed_time: %lfus.\n", sum / iterations);

  return 0;
}

double get_gettimeofday_costs(void) {
  struct timeval start, end;

  if(gettimeofday(&start, NULL) < 0) {
    fprintf(stderr, "Error occured while getting start time!\n");
    exit(-4);
  }

  if (gettimeofday(&end, NULL) < 0) {
    fprintf(stderr, "Error occured while getting end time!\n");
    exit(-5);
  }

  // calcualte the elapsed time in milliseconds

  double start_time = start.tv_sec * 1000000.0 + start.tv_usec; // us
  double end_time = end.tv_sec * 1000000.0 + end.tv_usec; // us
  double elapsed_time = end_time - start_time;

  return elapsed_time;
}
