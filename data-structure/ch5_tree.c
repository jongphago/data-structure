#include <stdio.h>
#include <stdlib.h>


// 5.2 BINARY TREES
typedef struct Node* treePointer;
typedef struct Node
{
	char data;
	treePointer leftChild;
	treePointer rightChild;
}Node;

treePointer* stack;

treePointer initBinTree(char item)
{
	treePointer node = malloc(sizeof(Node));
	node->data = item;
	node->leftChild = NULL;
	node->rightChild = NULL;
	return node;
}
int IsBinTreeEmpty(treePointer tree);
treePointer makeBinTree(char item,  treePointer leftTree, treePointer rightTree)
{
	treePointer node = malloc(sizeof(Node));
	node->data = item;
	node->leftChild = leftTree;
	node->rightChild = rightTree;
	return node;
}
treePointer getLeftChild(treePointer tree)
{
	treePointer tempTree = tree->leftChild;
	return tempTree;
}
treePointer getRightChild(treePointer tree)
{
	treePointer tempTree = tree->rightChild;
	return tempTree;
}
char getElement(treePointer tree)
{
	char item = tree->data;
	return item;
}

// 5.3 BINARY TREE TRAVERSALS
void inOrder(treePointer ptr)
{
	//while (ptr != NULL)
	if (ptr)
	{
		inOrder(ptr->leftChild);
		printf("%c ", getElement(ptr));
		inOrder(ptr->rightChild);
	}
}
void preOrder(treePointer ptr)
{
	if (ptr)
	{
		printf("%c ", getElement(ptr));
		preOrder(ptr->leftChild);
		preOrder(ptr->rightChild);
	}
}
void postOrder(treePointer ptr)
{
	if (ptr)
	{
		postOrder(ptr->leftChild);
		postOrder(ptr->rightChild);
		printf("%c ", getElement(ptr));
	}
}

void add(int* topPointer, treePointer node)
{
	stack[++(*topPointer)] = node;
}
treePointer delete(int* topPointer)
{
	if (*topPointer == -1)
	{
		return NULL;
	}
	treePointer node = stack[*topPointer];
	stack[(*topPointer)--] = NULL;
	return node;
}

void addq(int front, int* rear, treePointer ptr)
{

}

treePointer deleteq(int* front, int rear)
{
	if (1)
	{
		return;						/* empty Queue */
	}


	return;							/* return treePointer */
}

void iter_inorder(treePointer node)
{
	int top = -1;												/* initialize stack */
	for (; ; )
	{
		for (; node; node = node->leftChild)
		{
			add(&top, node);								/* add to stack */
		}
		node = delete(&top);							/* delete from stack */
		if (!node)												/* empty stack */
		{
			break;
		}
		printf("%c ", node->data);
		node = node->rightChild;
	}
}

void level_order(treePointer ptr)
{
	int front = 0;
	int rear = 0;
	treePointer queue[999];
	if (!ptr)
	{
		return;														/* empty tree */
	}
	addq(front, &rear, ptr);
	for (; ; )
	{
		ptr = deleteq(&front, rear);					/* empty list returns NULL */
		if (ptr)
		{
			if (ptr->leftChild)
			{
				addq(front, &rear, ptr->leftChild);
			}
			if (ptr->rightChild)
			{
				addq(front, &rear, ptr->rightChild);
			}
		}
		else
		{
			break;
		}
	}
}

// 5.4 ADDITIONAL BINARY TREE OPERATIONS
//treePointer copyTree(treePointer originalTree);
//int isTreeEqual(treePointer firstTree, treePointer secondTree);

typedef enum{not, and, or, true, false}logical;
typedef struct satiNode* satiPointer;
typedef struct satiNode
{
	logical data;
	char value;
	satiPointer satiLeft;
	satiPointer satiRight;
};

void postOrderEval(satiPointer node);



void main()
{
	stack = malloc(999 * sizeof(treePointer));

	treePointer node1 = initBinTree('A');
	treePointer node2 = initBinTree('B');
	treePointer node3 = initBinTree('C');
	treePointer node4 = initBinTree('D');
	treePointer node5 = initBinTree('E');

	treePointer node6 = makeBinTree('/', node1, node2);
	treePointer node7 = makeBinTree('*', node6, node3);
	treePointer node8 = makeBinTree('*', node7, node4);
	treePointer node9 = makeBinTree('+', node8, node5);

	/*inOrder(node9);
	printf("\n");
	preOrder(node9);
	printf("\n");
	postOrder(node9);
	printf("\n");*/

	iter_inorder(node9);

	return;
}