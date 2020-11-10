#include <stdio.h>
#include <stdlib.h>

// 5.2 BINARY TREES
typedef struct Node* treePointer;
typedef struct Node
{
	int data;
	treePointer leftChild;
	treePointer rightChild;
}Node;

treePointer initBinTree(int item)
{
	treePointer node = malloc(sizeof(Node));
	node->data = item;
	node->leftChild = NULL;
	node->rightChild = NULL;
	return node;
}
int IsBinTreeEmpty(treePointer tree);
treePointer makeBinTree(int item,  treePointer leftTree, treePointer rightTree)
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
int getElement(treePointer tree)
{
	int item = tree->data;
	return item;
}

// 5.3 BINARY TREE TRAVERSALS
void inorder(treePointer ptr)
{
	//while (ptr != NULL)
	if (ptr)
	{
		inorder(ptr->leftChild);
		printf("%d ", getElement(ptr));
		inorder(ptr->rightChild);
	}
}
void preorder(treePointer ptr)
{
	if (ptr)
	{
		printf("%d ", getElement(ptr));
		inorder(ptr->leftChild);
		inorder(ptr->rightChild);
	}
}
void postorder(treePointer ptr)
{
	if (ptr)
	{
		inorder(ptr->leftChild);
		inorder(ptr->rightChild);
		printf("%d ", getElement(ptr));
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
	short int value;
	satiPointer satiLeft;
	satiPointer satiRight;
};

void postOrderEval(satiPointer node);

void main()
{
	treePointer node2 = initBinTree(2);
	treePointer node3 = initBinTree(3);
	treePointer node1 = makeBinTree(1, node2, node3);

	treePointer tree1 = getRightChild(node1);
	treePointer tree2 = getLeftChild(node1);
	int item = getElement(node1);
	printf("%d\n", tree1->data);
	printf("%d\n", tree2->data);
	printf("%d\n", item);

	inorder(node1);
	printf("\n");
	preorder(node1);
	printf("\n");
	postorder(node1);
	printf("\n");

	return;
}