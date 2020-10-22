#include <stdio.h>
#include <stdlib.h>     // malloc()

int main() {
  int *p = (int *) malloc(10 * sizeof(int));

  if (p == NULL) {
    fprintf(stderr, "Malloc failed!\n");
    exit(-1);
  }

  return 0;
}
