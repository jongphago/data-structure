/*
작성자: 김종현
학번: 120200199
전공: 석사과정 인공지능전공
입력값: 원소의 개수와 원소로 이뤄진 하나의 리스트
출력값: 1) input: 입력값과
			   2) Sorted: 입력갑을 오름차순으로 정렬한 리스트를 출력하고
			   3) N, repetitions, duration: (입력값의 원소의 개수에 따라) 원소의 수를 달리하여
															  원소의 수, 원소의 수에 따른 정렬 소요 시간 및 반복횟수를 출력한다.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
/*swap 함수: x와 y의 주소를 받아 값을 교환합니다.*/
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))
void sort(int list[], int n);

void main(void) {
	/*변수를 선언하고 초기화 합니다.*/
	int MAX_N, N, * pL;
	FILE* fp_in, * fp_out;
	char inFile[80] = "lab1.data";													//입력할 파일의 파일명을 지정합니다.
	char outFile[80] = "DS_HW1_120200199_output.txt";			//출력할 파일의 파일명을 지정합니다.
	/*입력 파일과 출력 파일을 불러옵니다.*/
	fp_in = (FILE*)fopen(inFile, "r");
	fp_out = (FILE*)fopen(outFile, "w");
	if (fp_in == NULL || fp_out == NULL) {
		printf("File open Error!");
		exit(-1);
	}
	/*정렬할 원소의 총 개수와 데이터를 저장하고 출력합니다.*/
	fscanf(fp_in, "%d", &MAX_N);
	fprintf(fp_out, "input: %d, ", MAX_N);
	pL = (int*)malloc(MAX_N * sizeof(int));
	if (pL == NULL) {
		printf("File open Error!");
		exit(-1);
	}
	for (int i = 0; i < MAX_N; i++) {
		fscanf(fp_in, "%d", &pL[i]);
		fprintf(fp_out, "%d, ", pL[i]);
	}
	fprintf(fp_out, "\n\n");
	/*정렬 후 Sorted 값을 출력합니다.*/
	printf("데이터를 정렬하고 있습니다.");
	sort(pL, MAX_N);
	fprintf(fp_out, "Sorted: ");
	for (int i = 0; i < MAX_N; i++) {
		fprintf(fp_out, "%d, ", pL[i]);
	}
	fprintf(fp_out, "\n\n");
	/*Worst-Case로 초기화 합니다.*/
	int temp=0;
	for (int i = 0; i < MAX_N; i++)
		pL[i] = MAX_N - i;
	/*테스트 원소의 수 N을 생성합니다.
		N = 10, 20, 30, ..., 100, 200, ... ...*/
	fprintf(fp_out, "   N  repetitions   duration\n");
	for (int j = 1; j < 10; j++) {
		for (int k = 1; k < 10; k++) {
			(int)N = pow(10, (double)j) * (double)k;
			if (N < MAX_N) {
				long repetitions = 0;
				/*Selection Sort에 걸리는 시간을 측정합니다.*/
				clock_t start = clock();
				do {
					repetitions++;
					sort(pL, N);
				} while (clock() - start < 1000);
				double duration = ((double)clock() - start) / CLOCKS_PER_SEC;
				duration /= repetitions;
				/*사용자 인터페이스를 출력합니다.*/
				system("cls");
				printf("잠시만 기다려주세요. 정렬하는 원소의 수: %3d / %d\n", N, ((MAX_N / 100) - 1) * 100);
				fprintf(fp_out, "%6d %9d %f\n", N, repetitions, duration);
			}
			else
				break;
		}
	}
	system("pause");
	return;
}

/*sort 함수: 원소 리스트와 원소의 개수를 받아서 selection sort 방식으로 정렬합니다.*/
void sort(int list[], int n) {
	int i, j, min, temp;
	for (i = 0; i < n; i++) {
		min = i;
		for (j = i + 1; j < n; j++) {
			if (list[j] < list[min]) {
				min = j;
			}
		}
		//swap(&list[j], &list[min]);
		SWAP(list[i], list[min], temp);
	}
}