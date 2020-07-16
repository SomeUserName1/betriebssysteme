#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int main() {
  int fd = open("testFile.txt", O_WRONLY | O_TRUNC);
  pid_t pid = fork();

  if (fd < 0) {             // open failed; exit
    fprintf(stderr, "coud not open file!\n");
    exit(1);
  }

  if (pid < 0) {             // fork failed; exit
    fprintf(stderr, "fork failed!\n");
    close(fd);
    exit(2);

  } else if (pid == 0) {     // child process;
    printf("Child: Hello, I'm child (pid: %d)\n", (int) getpid());
    printf("Child: fd = %d\n", fd);

    const char buff[] = "Hello, World from child!\n";
    const int buff_size = strlen(buff);

    printf("Child: Try to write to file from child...\n");
    ssize_t bytes_written = write(fd, buff, buff_size);

    if (bytes_written < 0) { // write failed; exit
      fprintf(stderr, "could not write to file!\n");
      close(fd);
      exit(3);
    } else if (bytes_written != buff_size) {
      fprintf(stderr, "error occurred while writing to file from child process!\n");
      close(fd);
      exit(4);
    }

    printf("Child: Writing successfull into file.\n");
    printf("\n");

  } else {                  // parten process;
    printf("Parent: Hello, I'm parent of child %d (pid: %d)\n", pid, (int) getpid());
    printf("Parent: fd = %d\n", fd);

    const char buff[] = "Hello, World from parent!\n";
    const int buff_size = strlen(buff);

    printf("Parent: Try to write to file...\n");
    ssize_t bytes_written = write(fd, buff, buff_size);


    if (bytes_written < 0) {  // write failed; exit
      fprintf(stderr, "could not write to file from parent process!\n");
      close(fd);
      exit(5);
    } else if (bytes_written != buff_size) {
      fprintf(stderr, "error occured while writing to file from parent process!\n");
      close(fd);
      exit(6);
    }

    printf("Parent: Writing successfull in file.\n");
    printf("\n");
  }

  if (close(fd) < 0) {
    fprintf(stderr, "closing file failed!\n");
    exit(7);
  }

  return 0;
}
