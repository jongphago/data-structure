#include <stdio.h>
#include <string.h>
int nfind(char* string, char* pat);

int main(void) {
	char string1[] = "aababcabcdabcdeabcdefabcdefg", * string = string1;
	char pat1[] = "abcdefg", * pat = pat1;
	//printf("%p", strstr(string, pat)); // strstr함수를 이용하면 쉽게 구현 가능

	printf("%d", nfind(string1, pat1));
}

int nfind(char* string, char* pat) {
	int i, j = 0, start = 0;
	int lasts = strlen(string) - 1; // 문자열 string의 마지막 문자
	int lastp = strlen(pat) - 1; // 문자열 apt의 마지막 문자
	int endmatch = lastp;
	for (i = 0; endmatch <= lasts; endmatch++, start++) {
		if (string[endmatch] == pat[lastp])
			for (j = 0, i = start; j < lastp && string[i] == pat[j]; i++, j++)
				;
		if (j == lastp) return start;
	}
	return -1;
}