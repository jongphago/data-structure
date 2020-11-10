#include <stdio.h>
#include <stdlib.h>
#define IS_EMPTY(ptr) !(ptr))
#define IS_FULL(ptr) (!(ptr))
#define MALLOC(p, s) if(!((p) = malloc(s))){fprintf(stderr, "Insufficient memory"); exit(EXIT_FAILURE);}

/* Necessary declarations are */
typedef struct list_node* list_pointer;
typedef struct list_node {
	char data[4];
	list_pointer link;
} list_node;
list_pointer ptr = NULL;

list_pointer create2();
void insert(list_pointer* ptr, list_pointer node);
void delete(list_pointer* ptr, list_pointer trail, list_pointer node);
void print_list(list_pointer ptr);

void main(void) {

	ptr = (list_pointer)malloc(sizeof(list_node));
	list_pointer first = create2();
	ptr->link = first;
	insert(&ptr, first);
	//delete(&ptr, NULL, first);
	//printf("%s", ptr->link->data);
	print_list(ptr);
	return;
}

/* Program 4.2 create 2 nodes 2*/
list_pointer create2() {
	list_pointer first, second;
	first = (list_pointer)malloc(sizeof(list_node));
	second = (list_pointer)malloc(sizeof(list_node));
	second->link = NULL;
	strcpy(second->data, "20");
	strcpy(first->data, "10");
	first->link = second;
	return first;
}

/* Program 4.3 insert */
void insert(list_pointer* ptr, list_pointer node) {
	/* insert a new node with data = 50 into the list ptr after node */
	list_pointer temp;
	temp = (list_pointer)malloc(sizeof(list_node));
	if (IS_FULL(temp)) { fprintf(stderr, "The memory is full"); exit(1);};
	strcpy(temp->data, "50");
	if (*ptr) {
		temp->link = node->link;
		node->link = temp;
	}
	else {
		temp->link = NULL;
		*ptr = temp;
	}
}

/* Program 4.4 delete */
void delete(list_pointer* ptr, list_pointer trail, list_pointer node) {
	if (trail)
		trail->link = node->link;
	else
		*ptr = node->link;
	free(node);
}

/* Program 4.5 Printing out a list */
void print_list(list_pointer ptr) {
	while (ptr->link->data != NULL) {
		printf("%s ", ptr->link->data);
		ptr = ptr->link;
	}
}