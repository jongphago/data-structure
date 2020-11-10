#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define  MAX_SIZE  100
void strnins(char* s, char* t, int i);

int main() {
    char s[20] = { "amobile" };                                                             // **문자열 s 의 크기를 t 크기만큼 추가로 확보 할 것
    char t[] = { "uto" };
    strnins(s, t, 3);
    printf("%s\n", s);
    return 0;
}

/*
  이 코드에서 시간과 공간이 낭비되므로 실용성이 없다.
  스트링 temp가 필요하지 않도록 개선해보자.
*/

void strnins(char* s, char* t, int i) {
    /*
      스트링 s의 i번째 위치에 스트링 t를 삽입
    */
    char string[MAX_SIZE] = "", *temp = string;                                // **배열을 초기화 해줄 것
    //int j, k, len_s, len_t; // len_s : s의 길이, len_t : t의 길이
    if (i < 0 && i > strlen(s)) {
        printf("Postion is out of bounds\n");
        exit(EXIT_FAILURE);
    }
    if (!strlen(s)) {
        strcpy(s, t);
    }
    else if (strlen(t)) {
        strncpy(temp,s,i);
        strcat(temp,t);
        strcat(temp,(s+i));
        strcpy(s,temp);
        
        //len_s = strlen(s);
        //len_t = strlen(t);
        ///*
        //  새로 들어올 t의 문자열 길이만큼 i부터 len_s까지 뒤로 민다.
        //*/
        //for (j = len_s; j >= i; j--) {
        //    s[j + len_t] = s[j];
        //}
        ///*
        //  i번째에 원하는 문자열 삽입
        //*/
        //k = 0;
        //for (j = i; k < len_t; j++) {
        //    s[j] = t[k++];
        //}
    }
}

/*
  char *strcpy(char *dest, char *src) : src 스트링을 dest로 복사; dest 스트링으로 결과 반환
  char *strncpy(char *dest, char *src, int i) : src 스트링 중 n 개의 문자를 dest 스트링으로 복사, dest 스트링으로 결과 반환
  char *strcat(char *dst, char *src) : dest 스트링과 src 스트링 연결; dest 스트링으로 결과 반환
*/
