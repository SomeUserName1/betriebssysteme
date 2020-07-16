/**
 * @author Fabian Klopfer
 * @author Jannik Bamberger
 * @credits 15
 * @bonus10
 */

#include <stdio.h>
#include <math.h>

#define PI 3.14159265359
#define HALF 7 // half of the height
#define HEIGHT (2 * HALF + 1) // + 1 so the zero line is in the middle
#define WIDTH 64 // width of the graph
#define PERIOD (2 * PI) // indicates how many periods of the sin are drawn
#define SEGMENT (PERIOD / WIDTH) // width of one datapoint

/**
Der Sinus kann entweder Zeilen- oder Spaltenweise aufgebaut werden.
Wenn er Zeilenweise aufgebaut wird koennen die berechneten Werte direkt auf
die Konsole geschrieben werden, und es sind keine Zwischenspeicher noetig,
in denen die gesamte Loesung aufgebaut wird. Es ist aber komplizierter eine
gute Loesung dieser Form zu schreiben. Bei der Spaltenweisen Methode wird
zuerst die Gesamte Loesung im Speicher aufgebaut und am Ende ausgegeben.
Diese Loesung ist einfach zu implementieren.
*/
int main(void)
{
	int buffer[HEIGHT][WIDTH];
	int i = 0;
	int j = 0;
//  set all array values to 0
	for (i = 0; i < HEIGHT; i++)
		for (j = 0; j < WIDTH; j++)
			buffer[i][j] = 0;

//  plot one value in each array field in x direction
	for (i = 0; i < WIDTH; i++) {
		int index = (int) ((HALF + sin(SEGMENT * i) * HALF) + 0.5);

		if (index >= 0 && index < HEIGHT)
			buffer[index][i] = 1;
	}

//  fill missing holes, where one value per column isn't enough
	for (i = 0; i < WIDTH; i++) {
		double v1 = (HALF + sin(SEGMENT * i) * HALF);
		double v2 = (HALF + sin(SEGMENT * (i + 1)) * HALF);

		for (j = 0; j < HEIGHT; j++)
			if ((v1 <= j && j <= v2) || (v1 >= j && j >= v2))
				buffer[j][i] = 1;
	}

//  draw the array
	for (j = HEIGHT - 1; j >= 0; j--) {
		for (i = 0; i < WIDTH; i++)
			printf(buffer[j][i] == 1 ? "x" : " ");
		printf("\n");
	}
	return 0;
}
