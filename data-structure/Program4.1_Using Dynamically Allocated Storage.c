#include <stdio.h>
#include <stdlib.h>
void intmalloc(int* intp, int size);

void main(void) {
	int i, * pi;
	float f, * pf;
	pi = (int*)malloc(sizeof(int));
	pf = (float*)malloc(sizeof(float));
	if (pi == NULL || pf == NULL) {
		printf("Memory Allocation Error!");
		exit(0);
	}
	*pi = 1024;
	*pf = 3.14;
	printf("%d\n%f\n", *pi, *pf);

	//pf = (float*)malloc(sizeof(float)); // 이전에 선언된 pf를 free하기 전 pf에 메모리 할당을 하게되면 이전에 잡은 메모리에 접근할수가 없다. 

	free(pi);
	free(pf);

	/*int* intp = NULL;
	int size = 10;
	intp = (int*)malloc(sizeof(int) * size);
	if (intp == NULL) { printf("Memory Allocation Error!"); exit(0); }
	for (int i = 0; i < size; i++) 
		intp[i] = i;
	for (int i = 0; i < size; i++) 
		printf("%d ", intp[i]);*/
}
