#define _GNU_SOURCE     // ???
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
  pid_t fpid = fork();

  if (fpid < 0) {           // fork failed; exit
    fprintf(stderr, "Fork failed!\n");
    exit(1);
  } else if (fpid == 0) {   // child process;
      // exec()-call specification:

      // Calls with v in the name:
      //     take an array parameter to specify the argv[] array of the new
      //     program

      // Calls with l in the name:
      //     take the arguments of the new program as a variable-length argument
      //     list to the function itself

      // Calls with e in the name:
      //     take an extra argument to provide the enviroment of the new program;
      //     otherwise, the program inherits the current process's enviroment

      // Calls with p in the name:
      //     search the PATH enviroment variable to find the program if it
      //     doesen't have a directory in it (means doesen't contain a /
      //     character). Otherwise, the program name is always treated as a path
      //     to the executable


      printf("Child: Hello, I'm child (pid: %d)\n", (int) getpid());
      char *const params[] = {"ls", "-la", ".", NULL};    // param list for ls

      // variant execl():
      // printf("Child: Try to execute 'ls' in child process with 'execl()'...\n");
      // printf("\n");
      // execl("/bin/ls", "ls", "-la", ".", NULL);

      // variant execle():
      // printf("Child: Try to execute 'ls' in child process with 'execle()'...\n");
      // printf("\n");
      // execle("/bin/ls", "ls", "-la", ".", NULL, NULL);

      // variant execlp():
      // printf("Child: Try to execute 'ls' in child process with 'execlp()'...\n");
      // printf("\n");
      // execlp("ls", "ls", "-la", ".", NULL);
      // execlp("/bin/ls", "ls", "-la", ".", NULL);

      // variant execv():
      printf("Child: Try to execute 'ls' in child process with 'execv()'...\n");
      printf("\n");
      execv("/bin/ls", params);

      // variant execvp():
      // printf("Child: Try to execute 'ls' in child process with 'execvp()'...\n");
      // printf("\n");
      // execvp("ls", params);
      // execvp("/bin/ls", params);

      // variant execvpe():
      // printf("Child: Try to execute 'ls' in child process with 'execvpe()'...\n");
      // printf("\n");
      // execvpe("ls", params, NULL);
      // execvpe("/bin/ls", params, NULL);
  } else {                // parent process;
    printf("Parent: Hello, im parent of %d (pid: %d).\n", fpid, (int) getpid());
    printf("Parent: Waiting for child...\n");
    printf("\n");

    pid_t w = wait(NULL);

    if (w < 0) {
      fprintf(stderr, "Waiting for child failed!\n");
      exit(2);
    }

    printf("\n");
    printf("Parent: Wating for child completed!\n");
  }

  return 0;
}
