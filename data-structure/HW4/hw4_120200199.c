#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_EXPR_SIZE 100

char expr[MAX_EXPR_SIZE];
int isp[] = { 0, 19, 12, 12, 13, 13, 13, 13, 0 };
int icp[] = { 20, 19, 12, 12, 13, 13, 13, 13, 0 };

typedef enum {
	lparen, rparen, plus, minus, times, divide, mod, space, eos, operand
} precedence;
typedef struct Node* Pointer;
typedef struct Node {
	precedence data;
	Pointer next;
}Node;

Pointer top;

void rExpr(FILE* fp, char* expr);
void push(Pointer* top, precedence data);
precedence pop(Pointer* top);
precedence getToken(char* symbol, int* n);
void printToken(precedence token);
void postfix();

void main(void) {
	FILE* fp = NULL;
	rExpr(fp, expr);
	postfix();
	return;
}

void rExpr(FILE* fp, char* expr) {
	fp = fopen("expr.txt", "r");
	if (fp == NULL) {
		printf("파일 열기를 실패하였습니다.");
		exit(-1);
	}
	fgets(expr, MAX_EXPR_SIZE, fp);
	fclose(fp);
}

void push(Pointer* top, precedence data) {
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->data = data;
	temp->next = *top;
	*top = temp;
}

precedence pop(Pointer* top) {
	if ((*top)->next == NULL) {
		//printf("Stack Underflow\n");
		exit(EXIT_FAILURE);
	}
	precedence data;
	Pointer pointer;
	
	pointer = *top;
	data = pointer->data;

	*top = pointer->next;
	free(pointer);

	return data;
}

precedence getToken(char* symbol, int* n) {
	/*get the next token,
		symbol is the character representation, which is returned,
		the token is represented by its enumerated value, which returned in the function name*/
	*symbol = expr[(*n)++];
	switch (*symbol) {
	case '(': return lparen;
	case ')': return rparen;
	case '+':return plus;
	case '-': return minus;
	case '/': return divide;
	case '*': return times;
	case '%': return mod;
	case ' ': return space;
	case '\0': return eos;
	default: return operand; /* no error checking, default is operand*/
	}
}

void printToken(precedence token) {
	switch (token) {
	case lparen: printf("( ");	break;
	case rparen: printf(") ");	break;
	case plus: printf("+ ");		break;
	case minus: printf("- ");	break;
	case divide: printf("/ ");	break;
	case times: printf("* ");		break;
	case mod: printf("% ");		break;
	case space: break;
	case eos: break;
	default: printf("\n ");
	}
}

void postfix() {
	/*output the postfix of the expression. The expression string, stack, and the top are global*/
	char symbol;
	int n = 0;

	precedence token;

	top = (Pointer)malloc(sizeof(Node));
	top->data = eos;
	top->next = NULL;

	for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n)) {
		if (token == operand) {
			printf("%c ", symbol);
		}
		else if (token == rparen) {
			while (top->data != lparen) {
				printToken(pop(&top));
			}
			pop(&top);
		}
		else if (token == space) continue;
		else {
			/* remove and print symbols whose isp is greater than or equal...
				...to the current token's icp */
			while (isp[top->data] >= icp[token]) {
				printToken(pop(&top));
			}
			push(&top, token);
		}
	}
	while ((token = pop(&top)) != eos)
		printToken(token);
	printf("\n");
}