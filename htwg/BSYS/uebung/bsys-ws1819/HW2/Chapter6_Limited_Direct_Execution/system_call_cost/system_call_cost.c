#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

// function declaration
double get_average_system_call_cost(int iterations);

int main(int argc, char *argv[]) {

  if (argc == 1) {
    fprintf(stderr, "No arguments were passed!\nUsage: '$ ./costs_measurement <iterations>'.\n");
    exit(-1);
  } else if (argc > 2) {
    fprintf(stderr,"Too many arguments!\nUsage: '$ ./costs_measurement <iterations>'.\n");
    exit(-2);
  }

  int iterations = strtol(argv[1], NULL, 10);

  if (iterations == 0) {
    fprintf(stderr, "Please only enter numbers greater than 1!\n");
    exit(-3);
  }

  double average_elapsed_time = get_average_system_call_cost(iterations);

  printf("number of iterations (of systemcall): %d\n", iterations);
  printf("average elaped_time: %lfus\n", average_elapsed_time);

  return 0;
}

double get_average_system_call_cost(int iterations) {
  struct timeval start, end;

  if (gettimeofday(&start, NULL) < 0) {
    fprintf(stderr, "Error occured while getting start time!\n");
    exit(-4);
  }

  for (int i = 0; i < iterations; i++) {
    read(STDIN_FILENO, NULL, 0);
  }

  if (gettimeofday(&end, NULL) < 0) {
    fprintf(stderr, "Error occured while getting end time!\n");
    exit(-5);
  }

  double start_time = start.tv_sec * 1000000.0 + start.tv_usec; // in us
  double end_time = end.tv_sec * 1000000.0 + end.tv_usec;       // in us
  double average_elapsed_time = (end_time - start_time) / iterations;

  return average_elapsed_time;
}
