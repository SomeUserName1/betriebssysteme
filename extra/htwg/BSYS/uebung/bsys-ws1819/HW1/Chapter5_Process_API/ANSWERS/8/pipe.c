#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  int fd[2];

  const char *msg_one = "Hello, World!";
  size_t msg_one_length = strlen(msg_one) + 1;

  char buffer[msg_one_length];

  if (pipe(fd) < 0) { // create pipe failed; exit
    fprintf(stderr, "Failed to create pipe!\n");
    exit(1);
  }

  pid_t fpid_0 = fork();

  if (fpid_0 < 0) { // fork failed; exit
    fprintf(stderr, "Fork failed!\n");
    exit(2);
  } else if (fpid_0 == 0) { // child process;
    printf("Child_0: Hello, I'm child (pid: %d)\n", (int)getpid());
    printf("Child_0: Try to wirte message: \"Hello, World!\" in pipe...\n");

    int bytes_written_in_pipe = write(fd[1], msg_one, msg_one_length);

    if (bytes_written_in_pipe < 0) { // write in pipe failed; exit
      fprintf(stderr, "Write in pipe from child_0 failed!\n");
      exit(3);
    } else if (bytes_written_in_pipe != (int)msg_one_length) {
      fprintf(stderr, "Error occured while writing in pipe from child_0!\n");
      exit(4);
    }

    printf("Child_0: Written succesfully in pipe.\n");
    printf("\n");

    if (close(fd[1]) < 0) { // closing pipe[1] failed; exit
      fprintf(stderr, "closing pipe[1] failed!\n");
      exit(5);
    }
  } else { // parent process
    printf("Parent: Hello, I'm parent of child_0: %d (pid: %d)\n", fpid_0,
           (int)getpid());
    printf("Parent: Waiting on child_0...\n");
    printf("\n");

    pid_t w = wait(NULL);

    if (w < 0) {
      fprintf(stderr, "waiting on child failed!\n");
      exit(11);
    }

    printf("Parent: Waiting on child_0 finished!\n");

    pid_t fpid_1 = fork();

    if (fpid_1 < 0) { // fork failed; exit
      fprintf(stderr, "fork failed!\n");
      exit(6);
    } else if (fpid_1 == 0) { // another child process
      printf("Child_1: Hello, I'm another child_1 (pid: %d)\n", (int)getpid());

      printf("Child_1: Try to read from pipe...\n");
      int bytes_read_from_pipe = read(fd[0], buffer, msg_one_length);

      if (bytes_read_from_pipe < 0) { // read failed; exit
        fprintf(stderr, "Reading from pipe of child_1 failed!\n");
        exit(7);
      } else if (bytes_read_from_pipe !=
                 (int)msg_one_length) { // error occured while reading; exit
        fprintf(stderr,
                "Error occured while reading from pipe of child_1!\n");
        exit(8);
      }

      if (close(fd[0]) < 0) { // closeing pipe[0] failed, exit
        fprintf(stderr, "Closing pipe[0] failed!\n");
        exit(9);
      }

      printf("Child_1: Received message \"%s\".\n", buffer);
      printf("\n");
    } else { // parent process
      printf("Parent: Hello I'm parent of child_1 %d (pid: %d)\n", fpid_1, (int) getpid());
      printf("Parent: Wating on child_1...\n");
      printf("\n");
      pid_t w = wait(NULL);

      if (w < 0) {
        fprintf(stderr, "Waiting in child for child failed!\n");
        exit(10);
      }

      printf("Parent: Waiting on child_1 finished!\n");
    }
  }
  return 0;
}
