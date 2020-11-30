#include <stdio.h>

void swap(int a, int b);

int main(void) {
    int a = 42, b = 777;
    swap(a, b);
}

void swap(int a, int b) {
    a = a^b;
    b = a^b;
    a = a^b;
    printf("a: %i, b: %i\n", a, b);
}
