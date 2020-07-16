#include <stdio.h>
#include <stdlib.h>    // malloc(), free()

int main() {
  int *data = (int *) malloc(100 * sizeof(int));

  if (data == NULL) {
    fprintf(stderr, "Malloc failed!\n");
    exit(-1);
  }

  int *p = &data[49];

  free(p);

  return 0;
}
