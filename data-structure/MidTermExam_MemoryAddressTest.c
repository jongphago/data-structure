#include <stdio.h>

void main(void) {
	int listA[20][30] = {NULL};
	int* pointer_listA = listA;

	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 30; j++) {
			listA[i][j] = (i+1) * 100 + j+1;
		}
	}

	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 30; j++) {
			printf("%4d ", listA[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	printf("%d\n", listA[6][7]);
	printf("%p\n", &(listA[6][7]));
	printf("%p\n", pointer_listA + 30 * 6 + 7);
	printf("%d\n", *(pointer_listA+30*6+7));
	//printf("%d", a+8);
}