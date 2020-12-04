#include <stdio.h>
#include <math.h>
#include <string.h>

#define HEIGHT 16 
#define WIDTH 64 

const float horizontal_step = 2 * M_PI / (WIDTH);

char grid[HEIGHT][WIDTH];

int main () {
    float x = 0;
    int y;
   
    memset(&grid, 0x20, sizeof(grid));

    for (unsigned int i = 0; i < WIDTH; i++) {
        y = (int) HEIGHT/2 * sin(x) + HEIGHT/2;
        grid[y][i] = '*';
        x += horizontal_step;
    }

    for (int i = 0; i < HEIGHT; i++) {
        printf("%.*s\n", (int) WIDTH, grid[i]);    
    }
    return 0;
}
