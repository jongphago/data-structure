#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int dataRow = 0, dataCol = 0;
int maxClass = 0;
int testRow = 0;
int K = 7;

void dataToArray(FILE** fpIn, float*** dataArray, int** labelArray);
void print2DArray(float** dataArray, int dataRow, int dataCol);
void printLabelArray(int* labelArray, int dataRow);
void testToArray(FILE** fpIn, float*** testArray);
void distanceCalculation(float*** distanceArray, float**dataArray, float** testArray);
void makeIndexArray(int*** sortedLabelArray);
void swapIntPointer(int* x, int* y);
void swapFloatPointer(float* x, float* y);
void print2DIntArray(int** sortedLableArray, int testRow, int dataRow);
void distanceSort(float** distanceArray, int*** sortedLabelArray);
void countClass(int*** classCountArray, int* labelArray, int** sortedLabelArray);
void print1DIntArray(int* outputArray, int testRow);
void getMaxClass(int** outputArray, int** classCountArray, int* labelArray, int** sortedLabelArray);

void main(void) {
	FILE* fpIn, * fpOut;
	float** dataArray;
	int* labelArray;
	float** testArray;
	float** distanceArray;
	int** sortedLabelArray;
	int** classCountArray;
	int* outputArray;

	dataToArray(&fpIn, &dataArray, &labelArray);
	//printf("%d", maxClass);
	//print2DArray(dataArray, dataRow, dataCol);
	//printLabelArray(labelArray, dataRow);
	testToArray(&fpIn, &testArray);
	//print2DArray(testArray, testRow, dataCol);
	distanceCalculation(&distanceArray, dataArray, testArray);
	makeIndexArray(&sortedLabelArray);
	//print2DArray(distanceArray, testRow, dataRow);
	//print2DIntArray(sortedLabelArray, testRow, dataRow);
	distanceSort(distanceArray, &sortedLabelArray);
	//print2DArray(distanceArray, testRow, dataRow);
	//print2DIntArray(sortedLabelArray, testRow, dataRow);
	countClass(&classCountArray, labelArray, sortedLabelArray);
	//print2DIntArray(classCountArray, testRow, maxClass);
	getMaxClass(&outputArray, classCountArray, labelArray, sortedLabelArray);
	print1DIntArray(outputArray, testRow);
	
	/*fpOut = (FILE*)fopen("output.txt", "w");
	for (int i = 0; i < testRow; i++) {
		fprintf(fpOut, "%d\n", outputArray[i]);
	}
	fclose(fpOut);*/
	return;
}

void dataToArray(FILE** fpIn, float*** dataArray, int** labelArray) {
	*fpIn = fopen("data.txt", "r");
	if (*fpIn == NULL) {
		printf("파일을 여는데 실패하였습니다.");
		printf("data.txt파일을 다시 확인하여주십시오.");
		exit(-1);
	}
	fscanf(*fpIn, "%d %d", &dataRow, &dataCol);
	*dataArray = (float**)malloc(dataRow * sizeof(float*));
	*labelArray = (int*)malloc(dataCol * sizeof(int));
	if (*dataArray == NULL || *labelArray == NULL) {
		printf("메모리 동적할당에 실패하였습니다.\n ");
		printf("프로그램을 다시 실행하여주십시오. ");
		exit(-1);
	}
	for (int i = 0; i < dataRow; i++) {
		(*dataArray)[i] = (float*)malloc(dataCol * sizeof(float));
		if ((*dataArray)[i] == NULL) {
			printf("메모리 동적할당에 실패하였습니다.\n ");
			printf("프로그램을 다시 실행하여주십시오. ");
			exit(-1);
		}
		for (int j = 0; j < dataCol; j++) {
			fscanf(*fpIn, "%f", &((*dataArray)[i][j]));
		}
		fscanf(*fpIn, "%d", &((*labelArray)[i]));
		if (maxClass < (*labelArray)[i]) {
			maxClass = (*labelArray)[i];
		}
	}
	fclose(*fpIn);
}
void testToArray(FILE** fpIn, float*** testArray) {
	*fpIn = fopen("test.txt", "r");
	if (*fpIn == NULL) {
		printf("파일을 여는데 실패하였습니다.");
		printf("data.txt파일을 다시 확인하여주십시오.");
		exit(-1);
	}
	fscanf(*fpIn, "%d", &testRow);
	*testArray = (float**)malloc(testRow * sizeof(float*));
	if (*testArray == NULL) {
		printf("메모리 동적할당에 실패하였습니다.\n ");
		printf("프로그램을 다시 실행하여주십시오. ");
		exit(-1);
	}
	for (int i = 0; i < testRow; i++) {
		(*testArray)[i] = (float*)malloc(dataCol * sizeof(float));
		if ((*testArray)[i] == NULL) {
			printf("메모리 동적할당에 실패하였습니다.\n ");
			printf("프로그램을 다시 실행하여주십시오. ");
			exit(-1);
		}
		for (int j = 0; j < dataCol; j++) {
			fscanf(*fpIn, "%f", &((*testArray)[i][j]));
		}
	}
	free(*fpIn);
}
void print2DArray(float** dataArray, int dataRow, int dataCol) {
	for (int i = 0; i < dataRow; i++) {
		for (int j = 0; j < dataCol; j++) {
			printf("%.2f   ", dataArray[i][j]);
		}
		printf("\n\n");
	}
}
void print2DIntArray(int** sortedLableArray, int testRow, int dataRow) {
	for (int i = 0; i < testRow; i++) {
		for (int j = 0; j < dataRow; j++) {
			printf("%3d ", sortedLableArray[i][j]);
		}
		printf("\n\n");
	}
}
void printLabelArray(int* labelArray, int dataRow) {
	for (int i = 0; i < dataRow; i++) {
		printf("%d ", labelArray[i]);
	}
	printf("\n");
}
void distanceCalculation(float*** distanceArray, float** dataArray, float** testArray) {
	*distanceArray = (float**)malloc(testRow * sizeof(float*));
	if (*distanceArray == NULL) {
		printf("메모리 동적할당에 실패하였습니다.\n ");
		printf("프로그램을 다시 실행하여주십시오. ");
		exit(-1);
	}

	for (int i = 0; i < testRow; i++) {
		(*distanceArray)[i] = (float*)malloc(dataRow * sizeof(float));
		if ((*distanceArray)[i] == NULL) {
			printf("메모리 동적할당에 실패하였습니다.\n ");
			printf("프로그램을 다시 실행하여주십시오. ");
			exit(-1);
		}
		for (int j = 0; j < dataRow; j++) {
			float sumOfSquaredDiviation = 0;
			float tempElement;
			for (int k = 0; k < dataCol; k++) {
				tempElement = dataArray[j][k] - testArray[i][k];
				tempElement *= tempElement;
				sumOfSquaredDiviation += tempElement;
			}
			(*distanceArray)[i][j] = sqrt(sumOfSquaredDiviation);
		}
	}
}
void makeIndexArray(int*** sortedLabelArray) {
	*sortedLabelArray = (int**)malloc(testRow * sizeof(int*));
	if (*sortedLabelArray == NULL) {
		printf("메모리 동적할당에 실패하였습니다.\n ");
		printf("프로그램을 다시 실행하여주십시오. ");
		exit(-1);
	}

	for (int i = 0; i < testRow; i++) {
		(*sortedLabelArray)[i] = (int*)malloc(dataRow * sizeof(int));
		if ((*sortedLabelArray)[i] == NULL) {
			printf("메모리 동적할당에 실패하였습니다.\n ");
			printf("프로그램을 다시 실행하여주십시오. ");
			exit(-1);
		}
		for (int j = 0; j < dataRow; j++) {
			(*sortedLabelArray)[i][j] = j;
		}
	}
}
void swapIntPointer(int* x, int* y) {		
	int temp = *x;
	*x = *y;
	*y = temp;
}
void swapFloatPointer(float* x, float* y) {
	float temp = *x;
	*x = *y;
	*y = temp;
}
void distanceSort(float** distanceArray, int*** sortedLabelArray) {
	//print2DArray(distanceArray, testRow, dataRow); /**/

	for (int i = 0; i < testRow; i++) {
		for (int j = 0; j < dataRow - 1; j++) {
			int minIndex = j;
			for (int k = j + 1; k < dataRow; k++) {
				//printf("현재값: %.2f\t검사값: %.2f\t최소값: %.2f\n", distanceArray[i][j], distanceArray[i][k], distanceArray[i][minIndex]);
				if (distanceArray[i][k] < distanceArray[i][minIndex]) {
					minIndex = k;
				}
			}
			//printf("[SWAP전 값] 현재값: %.2f   최소값: %.2f\n", distanceArray[i][j], distanceArray[i][minIndex]);
			swapFloatPointer(&(distanceArray[i][j]), &(distanceArray[i][minIndex]));
			//printf("[SWAP후 값] 현재값: %.2f   최소값: %.2f\n", distanceArray[i][j], distanceArray[i][minIndex]);
			//printf("[SWAP전 인덱스값] 현재값: %3d   최소값: %3d\n", (*sortedLabelArray)[i][j], (*sortedLabelArray)[i][minIndex]);
			swapIntPointer(&((*sortedLabelArray)[i][j]), &((*sortedLabelArray)[i][minIndex]));
			//printf("[SWAP후 인덱스값] 현재값: %3d   최소값: %3d\n", (*sortedLabelArray)[i][j], (*sortedLabelArray)[i][minIndex]);
		}
	}
	//print2DArray(distanceArray, testRow, dataRow); /**/
}
void countClass(int*** classCountArray, int* labelArray, int** sortedLabelArray) {
	*classCountArray = (int**)malloc(testRow * sizeof(int*));
	if (*classCountArray == NULL) {
		printf("메모리 동적할당에 실패하였습니다.\n ");
		printf("프로그램을 다시 실행하여주십시오. ");
		exit(-1);
	}
	maxClass += 1; /*전역변수임에 주의할것*/
	for (int i = 0; i < testRow; i++) {
		(*classCountArray)[i] = (int*)calloc(maxClass, sizeof(int));
		if ((*classCountArray)[i] == NULL) {
			printf("메모리 동적할당에 실패하였습니다.\n ");
			printf("프로그램을 다시 실행하여주십시오. ");
			exit(-1);
		}
	}
	for (int i = 0; i < testRow; i++) {
		for (int j = 0; j < K; j++) {
			for (int l = 0; l < maxClass; l++) {
				if (labelArray[sortedLabelArray[i][j]] == l) {
					(*classCountArray)[i][l] ++;
					break;
				}
			}
		}
	}
}
void print1DIntArray(int* outputArray, int testRow) {
	for (int i = 0; i < testRow; i++) {
		printf("%d\n", outputArray[i]);
	}
}
void getMaxClass(int** outputArray, int** classCountArray, int* labelArray, int** sortedLabelArray) {
	*outputArray = (int*)malloc(testRow * sizeof(int));
	int tempMax;
	int tempMaxCount;
	int tempMaxIndex;
	int j;
	for (int i = 0; i < testRow; i++) {
		tempMax = 0;
		tempMaxIndex = 0;
		tempMaxCount = 0;
		for (j = 0; j < maxClass; j++) {
			//printf("%d", classCountArray[i][j]);
			if (tempMax <= classCountArray[i][j]) {
				tempMax = classCountArray[i][j];
				tempMaxIndex = j;
			}
		}
		(*outputArray)[i] = tempMaxIndex;
	}
}
