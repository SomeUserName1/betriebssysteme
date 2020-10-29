#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(void) {
    printf("1 \n " );
    fork();
    printf("2 \n " );
    fork();
    printf("3 \n " );
    return 0;
}

