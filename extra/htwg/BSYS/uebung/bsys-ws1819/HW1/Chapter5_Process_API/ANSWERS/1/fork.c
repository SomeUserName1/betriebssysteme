#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main() {
  int x = 100;
  pid_t pid = fork();

  if (pid < 0) {             // fork failed; exit
    fprintf(stderr, "fork failed!\n");
    exit(1);
  } else if (pid == 0) {     // child process
    printf("Child: Hello, I'm child (pid: %d)\n", (int) getpid());
    printf("Child: x = %d\n", x);

    x = 0;

    printf("Child: newX = %d\n", x);
  } else {                  // parent process
    printf("Parent: Hello, I'm parent of child %d (pid: %d)\n", pid, (int) getpid());
    printf("Parent: x = %d\n", x);

    x = 42;

    printf("Parent: newX = %d\n", x);
    printf("\n");
  }

  return 0;
}
