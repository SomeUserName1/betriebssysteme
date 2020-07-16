/**
 * @author Fabian Klopfer
 * @author Jannik Bamberger
 * Danke!
 *
 * @credits 18
 * @bonus10
 *
 * Keine zufällige Anzahl von Spalten und Reihen (-2)
 */
#include <stdio.h>
#include <stdlib.h>

void draw(int sidelen, int *array);

void draw1(int sidelen, int *array);

void draw2(int sidelen, int *array);

void draw3(int sidelen, int *array);

void draw4(int sidelen, int *array);

void draw5(int sidelen, int *array);


int main(void)
{
	int sidelen = 17;
	int *array = malloc((unsigned int)(sidelen * sidelen) * sizeof(*array));

	if (array == NULL) {
		printf("failed mem allocation!\n");
		return EXIT_FAILURE;
	}

	printf("Array 1:\n");
	draw1(sidelen, array);
	printf("\nArray 2:\n");
	draw2(sidelen, array);
	printf("\nArray 3:\n");
	draw3(sidelen, array);
	printf("\nArray 4:\n");
	draw4(sidelen, array);
	printf("\nArray 5:\n");
	draw5(sidelen, array);

	free(array);
	return EXIT_SUCCESS;
}

void draw1(int sidelen, int *array)
{
	int cnt = 0;
	int direction = 1;

	for (int i = sidelen - 1; i >= 0; --i) {
		int x = direction ? 0 : sidelen - 1;

		for (int j = 0; j < sidelen; ++j) {

			*(array + sidelen * i + x) = cnt;
			cnt++;
			if (direction)
				x++;
			else
				x--;

		}
		direction = !direction;
	}
	draw(sidelen, array);
}

void draw2(int sidelen, int *array)
{
	int direction = 0;
	int offset = 0;
	int x = 0;
	int y = sidelen - 1;

	for (int i = 0; i < sidelen * sidelen; ++i) {
		*(array + sidelen * y + x) = i;
		switch (direction) {
		case 0: //right
			if (x == sidelen - offset - 1) {
				direction = 1;
				y--;
			} else
				x++;

			break;
		case 1: // up
			if (y == offset) {
				direction = 2;
				x--;
			} else
				y--;

			break;
		case 2: // left
			if (x == offset) {
				direction = 3;
				y++;
			} else
				x--;

			break;
		case 3: // down
			if (y == sidelen - offset - 2) {
				direction = 0;
				x++;
				offset++;
			} else
				y++;

			break;
		}
	}
	draw(sidelen, array);
}

void draw3(int sidelen, int *array)
{
	int cnt = 0;
	int direction = 0;
	int x = 0;
	int y = sidelen - 1;

	for (int i = 0; i < sidelen; ++i)
		*(array + sidelen * y + i) = cnt++;

	x = sidelen - 1;
	y--;
	for (int j = 1; j < sidelen; ++j)
		*(array + sidelen * y-- + x) = cnt++;

	for (int i = 0; i < sidelen - 1; ++i) {
		x = direction ? 0 : sidelen - 2;
		for (int j = 0; j < sidelen - 1; ++j) {

			*(array + sidelen * i + x) = cnt;
			cnt++;
			if (direction)
				x++;
			else
				x--;

		}
		direction = !direction;
	}

	draw(sidelen, array);
}

void draw4(int sidelen, int *array)
{
	int cnt = 0;
	int direction = 0;

	for (int i = sidelen - 1; i >= 0; --i) {
		int x = direction ? 0 : sidelen - 1;

		for (int j = 0; j < sidelen; ++j) {
			*(array + sidelen * x + i) = cnt;
			cnt++;

			if (direction)
				x++;
			else
				x--;

		}
		direction = !direction;
	}

	draw(sidelen, array);
}


void draw5(int sidelen, int *array)
{
	int turnDirection = 1;
	int direction = 0;
	int offset = 0;
	int x = 0;
	int y = sidelen - 1;

	for (int i = 0; i < sidelen * sidelen; ++i) {
		*(array + sidelen * y + x) = i;

		if (turnDirection) {
			switch (direction) {
			case 0: //right
				if (x == sidelen - offset - 1) {
					direction = 1;
					y--;
				} else
					x++;

				break;
			case 1: // up
				if (y == offset) {
					direction = 2;
					x--;
				} else
					y--;

				break;
			case 2: // left
				if (x == offset) {
					direction = 3;
					y++;
				} else
					x--;

				break;
			case 3: // down
				if (y == sidelen - offset - 2) {
					direction = 1;
					x++;
					offset++;
					turnDirection = !turnDirection;
				} else
					y++;

				break;
			}
		} else {
			switch (direction) {
			case 1: // up
				if (y == offset) {
					direction = 0;
					x++;
				} else
					y--;

				break;
			case 0: //right
				if (x == sidelen - offset - 1) {
					direction = 3;
					y++;
				} else
					x++;

				break;
			case 3: // down
				if (y == sidelen - offset - 1) {
					direction = 2;
					x--;
				} else
					y++;

				break;
			case 2: // left
				if (x == offset + 1) {
					direction = 0;
					offset++;
					turnDirection = !turnDirection;
					y--;
				} else
					x--;

				break;
			}
		}

	}
	draw(sidelen, array);
}

/*
 * Draw Array to standard out
 * */
void draw(int sidelen, int *array)
{
	for (int i = 0; i < sidelen; ++i) {
		for (int k = 0; k < sidelen; ++k)
			printf("+---");

		printf("+\n");
		for (int j = 0; j < sidelen; ++j)
			printf("|%3d", *(array + sidelen * i + j) + 1);

		printf("|\n");
	}
	for (int k = 0; k < sidelen; ++k)
		printf("+---");

	printf("+\n");
}
