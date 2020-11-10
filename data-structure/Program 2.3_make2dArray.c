#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int** make2dArray(int rows, int cols);
void add(int** a, int** b, int** c, int rows, int cols);

void main(void) {
	int rows = 2, cols = 3;
	int** x = 	make2dArray(rows, cols);
	int** y = make2dArray(rows, cols);
	int** z = make2dArray(rows, cols);

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			x[i][j] = 1;
			y[i][j] = 2;
		}
	}

	add(x, y, z, rows, cols);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			printf("%d  ", z[i][j]);
		}
		printf("\n");
	}
}

///* EX2.2-3, p59 *///
void add(int** a, int** b, int** c, int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++)
			c[i][j] = a[i][j] + b[i][j];
	}
}


int** make2dArray(int rows, int cols) {
	// create a two dimensional rows * col arrays
	int** x, i;
	// get memory for row pointers
	x = (int**)malloc(sizeof(*x) * rows);
	for (i = 0; i < rows; i++) {
		//x[i] = (int*)malloc(sizeof(int) * cols);

		///* EX2.2-1, p59 *///
		x[i] = (int*)calloc(cols, sizeof(int));
	}
	return x;
}

