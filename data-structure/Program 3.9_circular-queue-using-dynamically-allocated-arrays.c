/*미완성코드*/
#include <stdio.h>
#include <stdlib.h>
typedef struct {
	int key;
	/* other fields */
} element;

element queue[100];
int rear = -1;
int front = -1;
int capacity = 100;

void addq(element item) {
	/* add an item to the queue */
	rear = (rear + 1) % capacity;
	if (rear == capacity)
		queueFull();
	queue[rear] = item;
}

void queueFull() {
	/*allocate an array with twice the capacity*/
	element* newQueue;
	MALLOC(newQueue, 2 * capacity * sizeof(queue));
	/*copy from queue to newQueue*/
	int start = (front + 1) % capacity;
	if (start < 2);
		/*no wrap arount*/
	else {
		// copy(queue+start, queue+capacity, newQueue);
		// copy(queue, queue+rear+1, newQueue+capacity-start);
	}
	/*switch to newQueue*/
	front = 2 * capacity - 1;
	rear = capacity - 2;
	#define capacity *= 2;
	free(queue);
	//queue = newQueue;
}