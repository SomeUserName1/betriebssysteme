#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() {
  pid_t fpid = fork();

  if (fpid < 0) {           // fork failed; exit
    fprintf(stderr, "Fork failed!\n");
    exit(1);
  } else if (fpid == 0) {   // child process;
    printf("Child: Hello, I'm child (pid: %d)\n", (int) getpid());
    printf("Child: Try to close STDOUT_FILENO...\n");
    printf("\n");

    if (close(STDOUT_FILENO) < 0) {
      fprintf(stderr, "Closing STDOUT_FILENO failed!\n");
      exit(2);
    }

    // THIS SHOULDN'T PRINT!
    printf("Child: Closed STDOUT_FILENO!\n");

  } else {                // parent process;
    printf("Parent: Hello, I'm parent of child %d (pid %d)\n", fpid, (int) getpid());
    printf("Parent: Waiting for child...\n");
    printf("\n");

    pid_t w = wait(NULL);

    if (w < 0) {         // wait failed; exit
      fprintf(stderr, "wait failed!\n");
      exit(3);
    }

    printf("Parent: Finished waiting on child.\n");
  }

  return 0;
}
