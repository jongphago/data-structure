#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 100 /*maximum queue size*/
typedef struct {
	int key;
	/* other fields */
} element;

element queue[MAX_QUEUE_SIZE];
int rear = -1;
int front = -1;

void addq(element item) {
	/* add an item to the queue */
	if (rear == MAX_QUEUE_SIZE) {
		printf("queue is full");
		exit(-1);
	}
	queue[++rear] = item;
}

element deleteq() {
	/* remove element at the front of the queue */
	if (front == rear) {
		printf("queue is empty");
		exit(-1);
	}
	return queue[++front];
}