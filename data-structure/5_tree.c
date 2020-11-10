#include <stdio.h>

// 5.2 BINARY TREES
typedef struct Node* treePointer;
typedef struct Node
{
	int data;
	treePointer leftChild;
	treePointer rightChild;
}Node;

treePointer createBinTree()
{
	treePointer node = malloc(sizeof(Node));
	node->data = NULL;
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
treePointer getLeftChild(treePointer tree);
treePointer getRightChild(treePointer tree);
int getElement(treePointer tree);

// 5.3 BINARY TREE TRAVERSALS
void inorder(treePointer ptr);
void preorder(treePointer ptr);
void postorder(treePointer ptr);
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
	return;
}