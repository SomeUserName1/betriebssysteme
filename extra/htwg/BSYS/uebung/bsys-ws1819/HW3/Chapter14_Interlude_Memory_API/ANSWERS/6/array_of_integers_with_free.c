
#include <stdio.h>
#include <stdlib.h>    // malloc(), free()

int main() {
  int *data = (int *) malloc(100 * sizeof(int));

  if (data == NULL) {
    fprintf(stderr, "Malloc failed!\n");
    exit(-1);
  }

  free(data);

  printf("data[0]: %d\n", data[0]);

  return 0;
}
