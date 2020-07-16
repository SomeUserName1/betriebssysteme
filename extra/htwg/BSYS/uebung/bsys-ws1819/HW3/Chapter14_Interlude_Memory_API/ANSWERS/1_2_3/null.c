#include <stdio.h>

int main() {
  int x = 42;
  int *i = &x;

  i = 0;

  printf("i: %d\n", *i);

  return 0;
}
