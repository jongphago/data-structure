#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int data;
	struct Node* next;
} Node;
typedef struct {
	Node* top;
} Stack;

//void push(Stack* stack, int data) {
//	Node temp;
//	temp.data = data;
//	temp.next = stack->top;
//	stack->top = &temp;
//}
void push(Stack* stack, int data) {
	Node* temp = (Node*)malloc(sizeof(Node));
	if (temp == NULL) { printf("malloc error"); exit(-1); }
	temp->data = data;
	temp->next = stack->top;
	stack->top = temp;
}
int pop(Stack* stack) {
	if (stack->top == NULL) { printf("stack underflow\n"); return -99999999; }
	//Node* temp = malloc(sizeof(Node));
	Node* temp = stack->top;
	int data = temp->data;
	stack->top = temp->next;
	free(temp);
	return data;
}
void show(Stack* stack) {
	Node* cur = stack->top;
	printf("===Top of Stack===\n");
	while (cur != NULL) {
		printf("%d\n", cur->data);
		cur = cur->next;
	}
	printf("===End of Stack===\n");
}

void main(void) {
	int stackCount = 10;

	Stack** stackArray = malloc(sizeof(Stack*) * stackCount);

	if (stackArray == NULL) 
	{
		printf("Memory allocation Error.");
		exit(-1);
	}

	for (int i = 0; i < stackCount; i++) 
	{
		stackArray[i] = malloc(sizeof(Stack));
		if (stackArray[i] == NULL) 
		{ 
			printf("Memory allocation Error.");
			exit(-1);
		}
		(stackArray[i])->top = NULL;
	}

	for (int i = 0; i < stackCount; i++) 
	{
		push(stackArray[i], i*10+1);
		push(stackArray[i], i*10+2);
		push(stackArray[i], i*10+3);
		push(stackArray[i], i*10+4);
		push(stackArray[i], i*10+5);
	}

	for (int i = 0; i < stackCount; i++) 
	{
		show(stackArray[i]);
	}

	for (int i = 0; i < stackCount; i++) 
	{
		while (stackArray[i]->top != NULL) 
		{
			pop(stackArray[i]);
		}
	}
	
	for (int i = 0; i < stackCount; i++) 
	{
		show(stackArray[i]);
	}

	return;
}