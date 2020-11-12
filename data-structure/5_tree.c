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
void iter_inorder(treePointer node);
void level_order(treePointer ptr);

// 5.4 ADDITIONAL BINARY TREE OPERATIONS
treePointer copyTree(treePointer originalTree);
int isTreeEqual(treePointer firstTree, treePointer secondTree);

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
	treePointer node1 = initBinTree('A');
	treePointer node2 = initBinTree('B');
	treePointer node3 = initBinTree('C');
	treePointer node4 = initBinTree('D');
	treePointer node5 = initBinTree('E');

	treePointer node6 = makeBinTree('/', node1, node2);
	treePointer node7 = makeBinTree('*', node6, node3);
	treePointer node8 = makeBinTree('*', node7, node4);
	treePointer node9 = makeBinTree('+', node8, node5);

	inOrder(node9);
	printf("\n");
	preOrder(node9);
	printf("\n");
	postOrder(node9);
	printf("\n");

	return;
}