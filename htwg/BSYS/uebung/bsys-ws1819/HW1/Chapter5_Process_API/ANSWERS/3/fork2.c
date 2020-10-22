#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() {
  pid_t fpid = fork();

  if (fpid < 0) {           // fork failed; exit
    fprintf(stderr, "fork failed!\n");
    exit(1);
  } else if (fpid == 0) {   // child process;
    printf("Child: hello\n");
  } else {
    pid_t wc = wait(NULL);

    if (wc < 0) {           // wait failed; exit
      fprintf(stderr, "wait failed!\n");
      exit(2);
    }

    // works instead of wait()

    // int status;
    // pid_t w = waitpid(fpid, &status, 0);
    // if (w < 0) {        // waitpid failed; exit
    //   fprintf(stderr, "waitpid failed!\n");
    //   exit(3);
    // }

    // sleep(1);        // works also instead of wait(), but is dangerous!

    printf("Parent: goodbye\n");
  }

  return 0;
}
