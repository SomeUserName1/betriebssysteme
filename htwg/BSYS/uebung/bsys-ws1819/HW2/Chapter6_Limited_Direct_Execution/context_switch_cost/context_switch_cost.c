#define _GNU_SOURCE
#include <sched.h>     // CPU_ZERO(), CPU_SET(), sched_setaffinity()
#include <stdio.h>
#include <stdlib.h>    // exit()
#include <string.h>    // strlen()
#include <sys/time.h>  // gettimeofday()
#include <sys/types.h> // pid_t
#include <sys/wait.h>  // wait()
#include <unistd.h>    // fork()

// function declaration
double get_context_switch_cost(void);

// main routine
int main(int argc, char *argv[]) {

  if (argc < 2) {
    fprintf(stderr, "No arguments were passed!\nUsage: '$ ./context_switch_cost <nloops>'.\n");
    exit(-1);
  } else if (argc > 2) {
    fprintf(stderr, "Too many arguments were passed!\nUsage: '$ ./context_switch_cost <nloops>'.\n");
    exit(-2);
  }

  int iterations = strtol(argv[1], NULL, 10);

  if (iterations == 0) {
    fprintf(stderr, "Please only enter numbers greater than 1!\n");
    exit(-3);
  }

  double sum = 0;
  for (int i = 0; i < iterations; i++) {
    printf("Loop: %d\n", i + 1);
    double elapsed_time = get_context_switch_cost();
    sum += elapsed_time;
    printf("elapsed_time: %lfus\n", elapsed_time);
    printf("\n");
  }

  printf("average ellapsed_time: %lfus\n", sum / iterations);
  return 0;
}

// The function get_context_switch_cost returns the amount of time, that one
// context switch costs.
double get_context_switch_cost(void) {
  double elapsed_time;
  struct timeval start, end;

  cpu_set_t set;
  CPU_ZERO(&set);

  CPU_SET(1, &set);

  if (sched_setaffinity(getpid(), sizeof(set), &set) < 0) {
    fprintf(stderr, "sched_setaffinit failed!\n");
    exit(-4);
  }

  int fd[2];
  int fd2[2];

  int p1 = pipe(fd);

  if (p1 < 0) { // pipe failed; exit
    fprintf(stderr, "Creating first pipe failed!\n");
    exit(-5);
  }

  int p2 = pipe(fd2);

  if (p2 < 0) {
    fprintf(stderr, "Creating second pipe failed!\n");
    exit(-6);
  }

  pid_t fpid = fork();

  if (fpid < 0) { // fork failed; exit
    fprintf(stderr, "Fork failed!\n");
    exit(-7);
  } else if (fpid == 0) { // child process

    if (gettimeofday(&end, NULL) < 0) {
      fprintf(stderr, "Error occured while getting end time!\n");
      exit(-8);
    }

    ssize_t num_of_bytes_read = read(fd[0], NULL, 0);

    if (num_of_bytes_read < 0) { // read failed; exit
      fprintf(stderr, "Read failed!\n");
      exit(-9);
    } else if (num_of_bytes_read != 0) {
      fprintf(stderr, "Error occurred while reading!\n");
      exit(-10);
    }

    if (close(fd[0]) < 0) {
      fprintf(stderr, "Close failed!\n");
      exit(-11);
    }

    double end_time = end.tv_sec * 1000000.0 + end.tv_usec;

    ssize_t num_of_bytes_written = write(fd2[1], &end_time, sizeof(double));

    if (num_of_bytes_written < 0) {
      fprintf(stderr, "Write failed!\n");
      exit(-12);
    } else if (num_of_bytes_written != sizeof(double)) {
      fprintf(stderr, "Error occurred while reading!\n");
      exit(-13);
    }

    exit(0);
  } else { // parent process
    ssize_t num_of_bytes_written = write(fd[1], NULL, 0);

    if (num_of_bytes_written < 0) { // write failed; exit
      fprintf(stderr, "Write failed!\n");
      exit(-14);
    } else if (num_of_bytes_written != 0) {
      // error while writing; exit
      fprintf(stderr, "Error occurred while writing!\n");
      exit(-15);
    }

    if (close(fd[1]) < 0) {
      fprintf(stderr, "Close failed!\n");
      exit(-16);
    }

    double buf[1];

    if (gettimeofday(&start, NULL) < 0) {
      fprintf(stderr, "Error occured while getting start time!\n");
      exit(-17);
    }

    ssize_t num_of_bytes_read = read(fd2[0], buf, sizeof(double));

    if (num_of_bytes_read < 0) {
      fprintf(stderr, "Read failed!\n");
      exit(-18);
    } else if (num_of_bytes_read != sizeof(double)) {
      fprintf(stderr, "Error occured while reading!\n");
      exit(-19);
    }

    double start_time = start.tv_sec * 1000000.0 + start.tv_usec;
    double end_time = buf[0];

    elapsed_time = end_time - start_time;
  }

  return elapsed_time;
}
