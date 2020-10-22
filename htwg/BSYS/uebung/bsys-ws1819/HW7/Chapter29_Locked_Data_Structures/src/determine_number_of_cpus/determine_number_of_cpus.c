#include <stdio.h>
#include <sys/sysinfo.h>

int main() {
  printf("Number of CPUs available: %d\n", get_nprocs());
  return 0;
}
