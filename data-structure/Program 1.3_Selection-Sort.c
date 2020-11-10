#include <stdio.h>
#include <stdlib.h>

/* 
	for ( i = 0; i < n; i++) {
		리스트의 i 번째 원소(list[i]) 부터 마지막 원소(list[n-1])에 대해
		값이 가장 작은 원소의 인덱스를 변수 min에 저장하고
		list[i]와 list[min]을 바꾼다

	1. 가장 작은 정수를 찾는다
	2. list[i]와 list[min]을 바꾼다
*/

void swap(int* x, int* y) {		// Call -- swap(&a, &b)
	int temp = *x;
	*x = *y;
	*y = temp;
}

#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

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

void main(void) {
	int list[] = { 5, 1, 111, 5, 1, 5, 1, 4, 3, 2, 1 };
	int n = sizeof(list) / sizeof(int);

	sort(list, n);

	for (int i = 0; i < n-1; i++) {					// loop imvariant check
		printf("%d ", list[i] <= list[i+1]);
	}
}