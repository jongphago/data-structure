#include <stdio.h>
#include "linked.h"


int main(void)
{
	struct _b c;

	First(&c);

	AddtoHead(&c, 3);
	AddtoTail(&c, 1);
	AddtoHead(&c, 4);
	AddtoHead(&c, 5);
	AddtoHead(&c, 6);
	AddtoHead(&c, 7);
	DeltoHead(&c);
	AddtoTail(&c, 2);
	AddtoTail(&c, 8);
	AddtoTail(&c, 9);
	AddtoTail(&c, 10);
	insert(&c, 2, 7);
	DeltoTail(&c);
	DeltoTail(&c);
	DeltoTail(&c);
	DeltoTail(&c);
	DeltoTail(&c);
	Delete(&c, 3); 
	printList(&c);

	return 0;
}