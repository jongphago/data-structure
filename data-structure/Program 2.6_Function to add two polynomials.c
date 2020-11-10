#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 1000

typedef struct {
	int coef;
	float expon;
} polynomial;
polynomial terms[MAX_TERMS];
int avail = 0;

int compare(int x, int y) {
	if (x < y) return -1;
	else if (x == y) return 0;
	else return 1;
}

void attach(polynomial* terms, float coefficient, int exponent) {
	if (avail >= MAX_TERMS) {
		fprintf(stderr, "Too many terms in the polynomial");
		exit(1);
	}
	terms[avail].coef = coefficient;
	terms[avail++].expon = exponent;
}

void padd(int starta, int finisha, int startb, int finishb, int* startd, int* finishd) {
	/*add A(x) and B(x) to obtain D(x)*/
	float coefficient;
	*startd = avail;
	while(starta <= finisha && startb <= finishb)
		switch (compare(terms[starta].expon, terms[startb].expon)) {
		case -1: /*a expon < b expon */
			attach(terms[startb].coef, terms[startb].expon);
			startb++;
			break;
		case 0: /*equal exponets*/
			coefficient = terms[starta].coef + terms[startb].coef;
			if (coefficient)
				attach(coefficient, terms[starta].expon);
			starta++; startb++;
			break;
		case 1: /* a expon > b expon*/
			attach(terms[starta].coef, terms[starta].expon);
			starta;;
		}
		/*add in remaining terms of A(x)*/
		for(; starta <= finisha; starta++)
			attach(terms[starta].coef, terms[starta].expon);
		/*add in remaining terms of B(x)*/
		for (; startb <= finishb; startb++)
			attach(terms[startb].coef, terms[startb].expon);
		*finishd = avail - 1;
}