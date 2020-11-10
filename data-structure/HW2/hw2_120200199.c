#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	float coef;
	int expon;
} polynomial;

void attach(polynomial* terms, int avail, float coefficient, int exponent) {
	terms[avail].coef = coefficient;
	terms[avail++].expon = exponent;
}

void main(void){
	int startA = 0, startB = 0; // 지수를 비교항 항을 나타내는 인덱스
	int finishA = 0, finishB = 0; // 다항식의 항의 수
	int startD = 0, finishD = 0;	 // 덧셈의 결과를 담을 항을 나타내는 인덱스와 덧셈식의 항의 수
	int temp_coef = 0, temp_expo = 0;	 // 임시변수
	polynomial* pListA, * pListB, * pListD; // 다항식을 담는 [polynomial] 리스트

	FILE* fp_A, * fp_B, * fp_out;
	char inFileA[] = { "A.txt" };
	char inFileB[] = { "B.txt" };
	char outFile[] = { "DS_HW2_out.txt" };

	/*입력 파일과 출력 파일을 불러옵니다.*/
	fp_A = (FILE*)fopen(inFileA, "r");
	fp_B = (FILE*)fopen(inFileB, "r");
	fp_out = (FILE*)fopen(outFile, "w");
	if (fp_A == NULL || fp_B == NULL || fp_out == NULL) {
		printf("File open Error!");
		exit(-1);
	}

	/*다항식의 항의 개수를 셉니다.*/
	while (fscanf(fp_A, "%d %d ", &temp_coef, &temp_expo) != EOF) ++finishA;
	rewind(fp_A);
	while (fscanf(fp_B, "%d %d", &temp_coef, &temp_expo) != EOF) ++finishB;
	rewind(fp_B);
	//printf("다항식의 항의 개수는 [식A: %d개] [식B: %d개] 입니다.\n", finishA, finishB);

	/*지수와 계수를 리스트에 동적할당합니다.*/
	pListA = (polynomial*)malloc(finishA * sizeof(polynomial));
	pListB = (polynomial*)malloc(finishB * sizeof(polynomial));
	pListD = (polynomial*)malloc((finishA + finishB) * sizeof(polynomial));

	if (pListA == NULL || pListB == NULL || pListD == NULL) {
		printf("File open Error!");
		exit(-1);
	}
	//printf("다항식A: ");
	for (int i = 0; i < finishA; i++) {
		fscanf(fp_A, "%f %d", &pListA[i].coef, &pListA[i].expon);
		//printf("(%.0f, %d), ", pListA[i].coef, pListA[i].expon);					// 다항식 A의 지수리스트를 출력합니다.
	}
	//printf("\n");
	//printf("다항식B: ");
	for (int i = 0; i < finishB; i++) {
		fscanf(fp_B, "%f %d", &pListB[i].coef, &pListB[i].expon);
		//printf("(%.0f, %d), ", pListB[i].coef, pListB[i].expon);					// 다항식 B의 지수리스트를 출력합니다.
	}
	//printf("\n\n");

	while (startA < finishA || startB < finishB) {
		if (startA == finishA) {
			attach(pListD, startD++, pListB[startB].coef, pListB[startB].expon);
			startB++, finishD++;
		}
		else if (startB == finishB) {
			attach(pListD, startD++, pListA[startA].coef, pListA[startA].expon);
			startA++, finishD++;
		}
		else if (pListA[startA].expon > pListB[startB].expon) {
			attach(pListD, startD++, pListA[startA].coef, pListA[startA].expon);
			startA++, finishD++;
		}
		else if (pListA[startA].expon < pListB[startB].expon) {
			attach(pListD, startD++, pListB[startB].coef, pListB[startB].expon);
			startB++, finishD++;
		}
		else {
			if (pListA[startA].coef + pListB[startB].coef != 0)
				attach(pListD, startD++, pListA[startA].coef + pListB[startB].coef, pListB[startB].expon);
			startA++, startB++, finishD++;
		}
	}
	finishD--;
	//printf("다항식A + 다항식B: ");
		for (int i = 0; i < finishD; i++) {
			printf("(%.0f %d), ", pListD[i].coef, pListD[i].expon);
			fprintf(fp_out, "(%.0f, %d), ", pListD[i].coef, pListD[i].expon);
		}
}