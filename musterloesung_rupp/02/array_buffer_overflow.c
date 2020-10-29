#include <stdio.h>

#define N 5
#define M 6

static int array[N][M] =  {
    { 1, 2, 3, 4, 5, 6},
    { 7, 8, 9, 10, 11, 12},
    {13, 14, 15, 16, 17, 18},
    {19, 20, 21, 22, 23, 24},
    {25, 26, 27, 28, 29, 30}
};


void print_rows() {
    for (unsigned int i = 0; i < N; i++) {
        for (unsigned int j = 0; j < M; j++) {
            printf("%i ", array[i][j]);
        }
        printf("\n");
    }
}

void print_cols() {
    for (unsigned int i = 0; i < N; i++) {
        for (unsigned int j = 0; j < M; j++) {
            printf("%i ", array[j][i]);
        }
        printf("\n");
    }
}

void print_rows_single() {
    for (unsigned int i = 0; i < N * M; i++) {
        printf("%i ", array[i / N][i % M]);  
        if (i % M == M - 1) {
            printf("\n");
        }
    }
}

int main(void) {
    printf("Print rows using two for loops\n");
    print_rows();
    printf("Print columns using two for loops\n");
    print_cols();
    printf("Print rows using one for loop\n");
    print_rows_single();
}
