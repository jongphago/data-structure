#include <stdio.h>
#include <stdlib.h>

// 팩토리얼
int factorial(int n) {
	if (n > 1) return n * factorial(n - 1);
	else return n;
}

// 피보나치
// 종현이 코드
int fibo(int n) {
	if (n == 0) return 0;
	else if (n == 1) return 1;
	else if (n > 1) {
		return fibo(n - 1) + fibo(n - 2);
	}
	else
		printf("양의 정수를 입력하세요.");
		return -1;
}

//교재 코드
int rfibo(int n) {
	if (n > 1)	return fibo(n - 1) + fibo(n - 2);
	else return n;			// 짝짝짝
}

void main(void) {
	printf("%d", rfibo(35));
	printf("\n");
	printf("%d", factorial(7));
}