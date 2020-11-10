#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void swap(int* x, int* y);
void sort(int list[], int n);

int main(void) {
	/*data.txt 파일을 읽은 다음 2차원 Array 형식의 변수 data_list에 저장한다*/
	int data_num=0, feature_num=0; 
	FILE* fp_data;
	fp_data = (FILE*)fopen("data.txt", "r");
	if (fp_data == NULL) {
		printf("파일 불러오기를 실패하였습니다.");
		return -1;
	}
	fscanf(fp_data, "%d %d", &data_num, &feature_num);
	printf("%d %d	", data_num, feature_num);

	float** data_list = malloc(data_num * sizeof(float*));
	if (data_list == NULL) {
		printf("File open Error!");
		exit(-1);
	}
	for (int i = 0; i < data_num; i++) {
		data_list[i] = malloc((feature_num + 1) * sizeof(float));
		int j = 0;
		for (j = 0; j < feature_num; j++)
			fscanf(fp_data, "%f", &data_list[i][j]);
		fscanf(fp_data, "%f", &data_list[i][++j]);
	}
	for (int i = 0; i < data_num; i++) {
		int j = 0;
		for (j = 0; j < feature_num; j++)
			printf("%.1f ", data_list[i][j]);
		printf("%d\n", (int)data_list[i][++j]);
	}

	/*test.txt 파일을 읽은 다음 2차원 Array 형식의 변수 test_list에 저장한다*/
	FILE* fp_test;
	int test_num = 0;
	fp_test = (FILE*)fopen("test.txt", "r");
	if (fp_test == NULL) {
		printf("파일 불러오기를 실패하였습니다.");
		return -1;
	}
	fscanf(fp_test, "%d", &test_num);
	printf("%d\n", test_num);

	float** test_list = malloc(test_num * sizeof(float*));
	if (test_list == NULL) {
		printf("File open Error!");
		exit(-1);
	}
	for (int i = 0; i < test_num; i++) {
		test_list[i] = malloc(feature_num * sizeof(float));
		int j = 0;
		for (j = 0; j < feature_num; j++)
			fscanf(fp_test, "%f", &test_list[i][j]);
	}
	for (int i = 0; i < test_num; i++) {
		int j = 0;
		for (j = 0; j < feature_num; j++)
			printf("%f ", test_list[i][j]);
		printf("\n");
	}
	printf("\n\n");

	/*L2 distance를 담는 2차원 배열*/
	float** length_list = malloc(sizeof(float*) * test_num);
	for (int i = 0; i < test_num; i++) {
		length_list[i] = malloc(sizeof(float) * data_num);
		float sum = 0, squared_error = 0;
		for (int j = 0; j < data_num; j++) {
			for (int k = 0; k < feature_num; k++) {
				squared_error = pow(test_list[i][k] - data_list[j][k], 2);
				sum += squared_error;
			}
			length_list[i][j] = sqrt(sum);
		}
	}

	for (int j = 0; j < test_num; j++) {
		for (int k = 0; k < data_num; k++) {
			printf("%f  ", length_list[j][k]);
		}
		printf("###############정렬전#################\n\n");
	}
	/*배열을 정렬한다*/
	for (int i = 0; i < test_num; i++) {
		sort(length_list[i], data_num);
	}

	for (int j = 0; j <test_num; j++) {
		for (int k = 0; k < data_num; k++) {
			printf("%f  ", length_list[j][k]);
		}
		printf("===============정렬끝=================\n\n");
	}
}

void swap(int* x, int* y) {		// Call -- swap(&a, &b)
	int temp = *x;
	*x = *y;
	*y = temp;
}

void sort(float list[], int n) {
	int i, j, min, temp=0;
	for (i = 0; i < n; i++) {
		min = i;
		for (j = i + 1; j < n; j++) {
			if (list[j] < list[min]) {
				min = j;
			}
		}
		swap(&list[j], &list[min]);
	}
}

