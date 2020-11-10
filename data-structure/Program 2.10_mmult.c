#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 101

typedef struct {
	int col;
	int row;
	int value;
} term;

void fast_transpose(term a[], term b[]);

void mmult(term a[], term b[], term d[]){
	int i, j, column, totalb = b[0].value, totald = 0;
	int rows_a = a[0].row, cols_a = a[0].col, totala = a[0].value;
	int cols_b = b[0].col;
	int row_begin = 1, row = a[1].row, sum = 0;
	term new_b[MAX_TERMS];
	if (cols_a != b[0].row) {
		fprintf(stderr, "Incompatible matrices\n");
		exit(1);
	}
	fast_transpose(b, new_b);
	/*set boundary condition*/
	a[totala + 1].row = rows_a;
	new_b[totalb + 1].row = cols_b; new_b[totalb+1].col = -1;

	for (i = 1; i <= totala;) {
		column = new_b[1].row;
		for (j = 1; j <= totalb + 1;) {
			/*multiply row of a by column of b*/
			if (a[i].row != row) {
				// storesum(d, &totald, row, column, &sum);
				i = row_begin;
				for (; new_b[j].row == column; j++)
					;
				column = new_b[j].row;
			}
			else if (new_b[j].row != column) {
				//storesum(d, &totald, row, column, &sum);
				i = row_begin;
				column = new_b[j].row;
			}
		}
	}
	
}

void fast_transpose(term a[], term b[]) {
	int row_terms[MAX_TERMS], starting_pos[MAX_TERMS];
	int i, j, num_cols = a[0].col, num_terms = a[0].value;
	b[0].row = num_cols; b[0].col = a[0].row;
	b[0].value = num_terms;
	if (num_terms > 0) {
		for (i = 0; i < num_cols; i++) row_terms[i] = 0;
		for (i = 1; i <= num_terms; i++) row_terms[a[i].col]++;
		starting_pos[0] = 1;
		for (i = 1; i < num_cols; i++)
			starting_pos[i] = starting_pos[i - 1] + row_terms[i - 1];
		for (i = 1; i <= num_terms; i++) {
			j = starting_pos[a[i].col]++;
			b[j].row = a[i].col; b[j].col = a[i].row;
			b[j].value = a[i].value;
		}
	}
}