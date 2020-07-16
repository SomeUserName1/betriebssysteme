#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>

int main() {
  pid_t fpid = fork();

  if (fpid < 0) {             // fork failed; exit
    fprintf(stderr, "Fork failed!\n");
    exit(1);
  } else if (fpid == 0) {     // child process
    printf("Child: Hello, I'm child (pid: %d)\n", (int) getpid());
    printf("\n");
  } else {                  // parent process
    printf("Parent: Hello, I'm parent of child %d (pid: %d)\n", fpid, (int) getpid());
    printf("Parent: Waiting for child...\n");
    printf("\n");

    int status;
    pid_t wpid = waitpid(fpid, &status, 0);

    if (wpid < 0) {           // waitpid in parent failed;
      fprintf(stderr, "Waitpid in parent failed!\n");
      exit(2);
    }

    printf("Parent: Finished waiting on child.\n");
  }
  return 0;
}
