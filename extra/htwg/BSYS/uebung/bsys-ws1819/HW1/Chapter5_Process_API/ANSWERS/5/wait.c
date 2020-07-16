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
    printf("Child: Try to call wait in child. - Should FAIL!\n");
    int rc = wait(NULL);

    if (rc < 0) {           // wait in child failed; exit
      fprintf(stderr, "Wait in child failed!\n");
      printf("\n");
      exit(2);
    }

    printf("\n");
  } else {                  // parent process
    printf("Parent: Hello, I'm parent of child %d (pid: %d)\n", fpid, (int) getpid());
    printf("Parent: Waiting for child...\n");
    printf("\n");
    pid_t w = wait(NULL);

    if (w < 0) {           // wait in parent failed;
      fprintf(stderr, "Wait in parent failed!\n");
      exit(3);
    }

    printf("Parent: Finished waiting on child.\n");
  }
  return 0;
}
