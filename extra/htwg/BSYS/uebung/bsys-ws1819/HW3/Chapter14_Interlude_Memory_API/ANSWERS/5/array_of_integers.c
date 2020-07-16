#include <stdio.h>
#include <stdlib.h>    // malloc()

int main() {
  int *data = malloc(100 * sizeof(int));

  if (data == NULL) {
    fprintf(stderr, "Malloc failed!\n");
    exit(-1);
  }

  data[100] = 0;
  return 0;
}
