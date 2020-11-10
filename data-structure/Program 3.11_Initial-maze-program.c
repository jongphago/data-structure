/*
*	ProjectName	: DSB Proj.1 Maze Finder (Stack)
*	Corder 		: Yu Yongwoo (YoWu)
*	Organiz.	: Catholic Univ. of Korea
*	Major		: Computer Science (Minor : Infomation System Eng)
*	StudentNum	: 201021395
*	DateTime	: 2015.4.1(Mon) 13:34
*	Contact		: uyu423@gmail.com (http://luckyyowu.tistory.com)
*	Develop OS	: CentOS Linux 6.6 x86 (kernel 2.6.32-504)
*	PorgramLang	: C (Library Model : POSIX)
*	TextEditor	: VIM - Vi IMproved 7.2
*	Encording	: UTF-8 (Linux Basic)
*	Compiler	: GCC 4.4.7
*/


#include <stdio.h>
#include <stdlib.h>
#define FILENAME "miro.txt"
#define SIZE 60
typedef enum { N, NE, E, SE, S, SW, W, NW } direction;
typedef enum { false, true } bool;

/* need Struction define */
typedef struct __mazeSize {
	int width;
	int height;
} mazeSize;
typedef struct __offset {
	int vert;
	int horiz;
} offset;
typedef struct __stackElement {
	int row;
	int col;
	int dir;
} element;
typedef struct __stackManager {
	element* stack;
	int size;
	int top;
} stackManager;

/* Define Basic Functions */
int readFile(FILE** fp);
mazeSize inputMaze(char(*maze)[SIZE], FILE** fp, mazeSize* size);
mazeSize setGoal(mazeSize* size, mazeSize* goal);
void fillWall(char(*maze)[SIZE], mazeSize* size);
void setOffset(offset* move);
void pathFinder(char(*maze)[SIZE], mazeSize* goal, stackManager* stackMgr, offset* move);
void printResult(bool found, int row, int col, mazeSize* goal, stackManager* stackMgr);

/* Define Stack Function */
void stackPush(stackManager* stackMgr, element item);
void makeStack(stackManager* stackMgr);
bool stackEmpty(stackManager* stackMgr);
bool stackFull(stackManager* stackMgr);
element stackPop(stackManager* stackMgr);

/* Define Debugging Functions */
void printMazeStatus(char(*maze)[SIZE], mazeSize* size);
void printMazeSizeTable(mazeSize* size, mazeSize* goal);
void printOffset(offset* move);

/* Other C File's Function Extern */
element stackPop(stackManager* stackMgr);	//stack.c

/* Maze Path Finding Function using Stack */
/* StackMgr included Stack Structure(element *stack) */
void pathFinder(char(*maze)[SIZE], mazeSize* goal, stackManager* stackMgr, offset* move) {
	char mark[60][60];
	int i, row, col, nextRow, nextCol, dir;
	bool found = false;
	element position;
	stackMgr->stack[0].row = 1;
	stackMgr->stack[0].col = 1;
	stackMgr->stack[0].dir = 1;
	stackMgr->top++;
	mark[1][1] = '1';
	while (stackMgr->top > -1 && !found) {
		position = stackPop(stackMgr);
		row = position.row;
		col = position.col;
		dir = position.dir;
		while (dir < 8 && !found) {
			nextRow = row + move[dir].vert;
			nextCol = col + move[dir].horiz;
			if (nextRow == goal->height && nextCol == goal->width) {
				found = true;
			}
			else if (maze[nextRow][nextCol] != '1' && mark[nextRow][nextCol] != '1') {
				mark[nextRow][nextCol] = '1';
				position.row = row;
				position.col = col;
				position.dir = ++dir;
				stackPush(stackMgr, position);
				row = nextRow;
				col = nextCol;
				dir = 0;
			}
			else {
				dir++;
			}
		}
	}
	printResult(found, row, col, goal, stackMgr);
	return;
}

/* if succeed found GOAL, print path. but not found , print other Message. */
void printResult(bool found, int row, int col, mazeSize* goal, stackManager* stackMgr) {
	int i;
	if (!found) {
		printf("\n** The maze dose not have a path **\n\n");
		return;
	}
	else {
		printf("\n** The maze dose have a path **\n");
		printf("(%d, %d)", (goal->height) - 1, (goal->width) - 1);
		printf("<-(%d, %d)", row - 1, col - 1);
		for (i = stackMgr->top; i >= 0; i--) {
			printf("<-(%d, %d)", (stackMgr->stack[i].row) - 1, (stackMgr->stack[i].col) - 1);
		}
		printf("\n\n");
	}
}

/* Input file (Miro.txt) Descriptor Generator */
int readFile(FILE** fp) {
	if (!(*fp = fopen(FILENAME, "r"))) {
		perror("Maze Flie Open Error : ");
		return 1;
	}
	return 0;
}

/* Make 'Maze Array' by 'maze.txt' start index was [1, 1] */
mazeSize inputMaze(char(*maze)[SIZE], FILE** fp, mazeSize* size) {
	int trash;
	char tmpByte = '\0';
	int tmpWidth = 0;

	/* Drop Index Value */
	fscanf(*fp, "%d", &trash); //first Index value
	fgetc(*fp);	//Space value 
	fscanf(*fp, "%d", &trash); //second Index value
	fgetc(*fp);	//Enter value

	while (!feof(*fp)) {
		tmpByte = fgetc(*fp);
		if (tmpByte == ' ') {
			continue;
		}
		else if (tmpByte == 10) {
			size->height++;
			tmpWidth = size->width;
			size->width = 0;
			continue;
		}
		else {
			maze[size->height][++(size->width)] = tmpByte;
			continue;
		}
	}
	size->width = tmpWidth + 1;

	return *size;
}

/* i, j were 0 line and i, j were end line fill '1'(wall)  */
void fillWall(char(*maze)[SIZE], mazeSize* size) {
	int i;
	for (i = 0; i <= size->width; i++) {
		maze[0][i] = '1';
		maze[size->height][i] = '1';
	}
	for (i = 0; i <= size->height; i++) {
		maze[i][0] = '1';
		maze[i][size->width] = '1';
	}
}

/* set Goal Index : mazeSize size value -1 */
mazeSize setGoal(mazeSize* size, mazeSize* goal) {
	goal->height = size->height - 1;
	goal->width = size->width - 1;
	return *goal;
}

/* Offset Value Set. ref. Fundamentals of Data Structures in C 131p */
void setOffset(offset* move) {
	move[N].vert = -1;	move[N].horiz = 0;
	move[NE].vert = -1; move[NE].horiz = 1;
	move[E].vert = 0;	move[E].horiz = 1;
	move[SE].vert = 1;	move[SE].horiz = 1;
	move[S].vert = 1;	move[S].horiz = 0;
	move[SW].vert = 1;	move[SW].horiz = -1;
	move[W].vert = 0;	move[W].horiz = -1;
	move[NW].vert = -1;	move[NW].horiz = -1;
	return;
}

/* If Stack Fulled, re-allocate Stack size  */
void stackPush(stackManager* stackMgr, element item) {
	if (stackFull(stackMgr)) {
		stackMgr->stack = (element*)realloc(stackMgr->stack, (2 * (stackMgr->size) * sizeof(element)) + sizeof(element));
		stackMgr->size *= 2;
	}
	stackMgr->stack[++(stackMgr->top)] = item;
	return;
}

element stackPop(stackManager* stackMgr) {
	if (stackEmpty(stackMgr)) {
		printf("stack empty\n");
		return;
	}
	return stackMgr->stack[(stackMgr->top)--];
}

bool stackFull(stackManager* stackMgr) {
	if (stackMgr->top >= stackMgr->size) {
		return true;
	}
	return false;
}

bool stackEmpty(stackManager* stackMgr) {
	if (stackMgr->top < 0) {
		return true;
	}
	return false;
}

void makeStack(stackManager* stackMgr) {
	stackMgr->stack = (element*)malloc(2 * sizeof(element));
	stackMgr->size = 1;
	stackMgr->top = -1;
	return;
}

int main(void) {
	FILE* fp = NULL;
	char maze[SIZE][SIZE];
	offset move[8];
	stackManager stackMgr;
	mazeSize goal, size = { 0, 1 };

	if (readFile(&fp)) { return 1; }
	size = inputMaze(maze, &fp, &size);
	goal = setGoal(&size, &goal);
	fillWall(maze, &size);
	setOffset(move);
	makeStack(&stackMgr);
	//	printOffset(move);	/* print 'move' offsets for Debugging */
	//	printMazeSizeTable(&size, &goal); /* print 'goal', 'size' mazeSize offset for Debugging */
	//	printMazeStatus(maze, &size);	/* print Maze Map for Debugging */
	pathFinder(maze, &goal, &stackMgr, move);

	return 0;
}