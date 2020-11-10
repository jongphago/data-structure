#include <stdio.h>
#include <stdlib.h>

int compare(int x, int y) {
	if (x < y) return -1;
	else if (x == y) return 0;
	else return 1;
}

int binsearch(int list[], int searchnum, int left, int right) {
	int middle;
	while (left <= right) {
		middle = (left + right) / 2;
		switch (compare(list[middle], searchnum)) {
			case -1: left = middle + 1; 
				break;
			case 0: return middle;
			case 1: right = middle - 1;
		}
	}
	return -1;
}

int rec_bin(int list[], int searchnum, int left, int right) {
	int middle;
	if (left <= right) {
		middle = (left + right) / 2;
		switch (compare(list[middle], searchnum)) {
		case -1: 
			rec_bin(list, searchnum, middle + 1, right);
			break;
		case 0:
			return middle;
		case 1: 
			rec_bin(list, searchnum, left, middle - 1);
		}
	}
}

void main(void) {
	int list[] = { 2, 4, 6, 7, 9, 11, 15, 17, 29, 100, 111, 121, 1000, 1111 };
	int left = 0;
	int right = sizeof(list) / sizeof(int) - 1;
	int searchnum = 1000;

	int index = rec_bin(list, searchnum, left, right);

	printf("%d", list[index]);
}