#include<stdio.h>
#include<conio.h>
#include <windows.h>

#define MAX_EXPR_SIZE 100    // 수식의 최대 크기
#define CARRIGE_RETURN 13

/* 사용될 operation */
typedef enum {
	lparen, rparen, plus, minus, times, divide, mod, eos, operand
}precedence;

/* Token(연산자)들이 저장될 stack */

typedef struct precedenceStack *precedenceStack_pointer;

typedef struct precedenceStack{
	precedence item;
	precedenceStack_pointer link;
};

precedenceStack_pointer precedenceStack_top;

/*	evaluation을 위한 stack */

typedef struct stack *stack_pointer;

struct stack{
	int item;
	stack_pointer link;
};

stack_pointer stack_top;


/* precedence 지정 */
int InStackPrecedence[8] = {0,19,12,12,13,13,13,0};
int InComingPrecedence[8] = {20,19,12,12,13,13,13,0};


void getInfix(char []);
void changePostfix(char [], char []);
precedence getToken(char*, int* , char []);
char printToken(precedence);
void printPostfix(char []); 
void tokenPush(precedenceStack_pointer *top, precedence item);
precedence tokenPop(precedenceStack_pointer *top);
void stackPush(stack_pointer *top, int item);
int stackPop(stack_pointer *top);
int exprEvaluation(char []);


void main()
{
	char inputExpr[MAX_EXPR_SIZE];		// 입력 문자열 
	char postfixExpr[MAX_EXPR_SIZE];	// postfix 배열  
	getInfix(inputExpr);
	changePostfix(inputExpr, postfixExpr);
	printPostfix(postfixExpr);
	//printf("Evaluation : %d\n", exprEvaluation(inputExpr));
}


void getInfix( char input_Expr[] )
{
	int i = 0, ch;

	printf("Enter Infix Expression : ");

	fflush(stdin);			// 버퍼의 값으로 인해 잘못된 값이 입력 될 경우 예방 해준다.

	ch = _getch();	

	while( ch != CARRIGE_RETURN )
	{
		input_Expr[i] = (char)ch;

		printf("%c", input_Expr[i] );
		
		i++;

		fflush(stdin);		// 버퍼의 값으로 인해 잘못된 값이 입력 될 경우 예방 해준다.

		ch = _getch();
	}

	input_Expr[i] = '\0';	// 엔터가 입력 되어서 입력을 끝낸 후 문자열의 마지막을 알려주기 위해
							// NULL 문자를 입력한다.
	printf("\n");

}


void changePostfix( char infix_expr[], char postfix_expr[] )
{
	int i = 0;
	int n = 0;
	char symbol;
	precedence token;

	/* 포인터이기 때문에 메모리 할당과 함께 끝을 알려주는 eos를 할당해 준다 */

	precedenceStack_top = (precedenceStack_pointer)malloc(sizeof(struct precedenceStack));

	precedenceStack_top->item = eos;
	precedenceStack_top->link = NULL;


	for ( (token = getToken( &symbol, &n, infix_expr )); token != eos ; (token = getToken( &symbol, &n, infix_expr )) )
	{
		// 숫자일 경우
		if ( token == operand )
		{
			postfix_expr[i] = symbol;
			i++;
		}
		
		// 입력값이 ) 일 경우 ( 나올 때까지 pop 해준다.
		else if ( token == rparen )
		{
			while ( precedenceStack_top->item != lparen )
			{
				symbol = printToken( tokenPop( &precedenceStack_top ) );
				postfix_expr[i] = symbol;
				i++;
			}

			tokenPop( &precedenceStack_top );		// while문을 끝내면 스택에 ( 가 남아 있으므로 한번 더 
		}											// pop 시켜준다. precedenseStack_top 값을 바꾸므로 주소연산자를 사용

		// 현재 스택에 다른 operator가 있을 경우 InStackPrecedence 의해 처리한다.
		else
		{
			while ( InStackPrecedence[precedenceStack_top->item] >= InComingPrecedence[token] )
			{
				postfix_expr[i] = printToken( tokenPop( &precedenceStack_top ) );	//주소연산자 사용에 주의
				i++;
			}
			tokenPush( &precedenceStack_top, token );
		}
	}

	// 문자열을 다 읽은 뒤 아직 나오지 않은 operator를 pop 시켜준다.
	while ( precedenceStack_top -> link )
	{
		postfix_expr[i] = printToken( tokenPop( &precedenceStack_top ) );
		
		i++;
	}
	
	// 배열의 긑을 알려주는 선언
	postfix_expr[i] = '\0';
}

// 문자열로부터 하나씩 값을 가져온 뒤, 그 값에 맞게 enum 형 변수를 return 시켜준다
// symbol 은 만약 현재 값이 operand 일 경우 정수 값을 저장해야하므로 symbol에 저장시켜준다
precedence getToken( char* symbol, int* n, char expr[] )
{
	*symbol = expr[(*n)++];
	//*n += 1; // *symbol = expr[*n];

	switch( *symbol )
	{
		case '('	:	return lparen;
		case ')'	:	return rparen;
		case '+'	:	return plus;
		case '-'	:	return minus;
		case '*'	:	return times;
		case '/'	:	return divide;
		case '%'	:	return mod;
		case '\0'	:	return eos;
		
		default		:	return operand;
	}
}

// 이 함수는 precedenseStack 에 저장해 놓은 값들에 맞는 operator를 반환 시켜준다.
// postfix[] 에 저장하기 위함
char printToken(precedence in_token)
{
	switch( in_token ) 
	{		
		case lparen	:	return '(';
		case rparen	:	return ')';
		case plus	:	return '+';
		case minus	:	return '-';
		case times	:	return '*';
		case divide :	return '/';
		case mod	:	return '%';
		case eos	:	return '\0';
		
		default		:	return in_token;
	}
}

// 완성된 postfix를 출력해주는 함수
void printPostfix(char postfix_expr[])
{
	int i = 0;

	printf("Postfix Expression : ");
	
	while ( postfix_expr[i] != '\0' )
	{
		printf("%c", postfix_expr[i] );
		i++;
	}

	printf("\n");
}

// precedenseStack 에 operator를 저장해주는 함수
void tokenPush( precedenceStack_pointer *top, precedence token )
{
	precedenceStack_pointer temp = (precedenceStack_pointer)malloc( sizeof( struct precedenceStack ) );

	temp->item = token; // (*temp).item = token; 포인터를 이용한 구조체 멤버 접근
	temp->link = *top;
	*top = temp;	
}

// precedenseStack 에 operator를 빼주는 함수
precedence tokenPop( precedenceStack_pointer *top )
{
	precedence tmp_token;
	precedenceStack_pointer temp_ptr;

	temp_ptr = *top;
	tmp_token = temp_ptr->item;

	*top = temp_ptr->link;
	free( temp_ptr );

	return tmp_token;
		
}

// 이 것은 evaluation 에서 값을 저장하기 위해 쓰인다.
void stackPush( stack_pointer *top, int item )
{
	stack_pointer temp = (stack_pointer)malloc(sizeof(struct stack) );
	temp -> item = item;
	temp->link = *top;
	*top = temp;	
}

// evaluation 에서 저장된 값을 빼오는 함수
int stackPop(stack_pointer *top)
{
	int item;
	stack_pointer temp;

	temp = *top;

	item = temp->item;

	*top = temp->link;

	free(temp);

	return item;	
}

// postfix에 의한 문자열 대로 값을 구해주는 함수
int exprEvaluation(char expr[])
{
	int i = 0;
	int oper1, oper2;

	char postfix_for_eval[MAX_EXPR_SIZE];

	stack_top = (stack_pointer)malloc(sizeof(struct stack));
	stack_top->link = NULL;


	changePostfix( expr, postfix_for_eval );		// 우선 infix를 postfix 해준다.

	// 끝 문자열이 NULL 이므로 다음과 같이 loop문을 작성한다.
	while ( postfix_for_eval[i] )
	{
		if ( postfix_for_eval[i] >= '1' && postfix_for_eval[i] <= '9' )
		{
			stackPush( &stack_top, (postfix_for_eval[i] - '0') );
		}

		else
		{
			oper2 = stackPop( &stack_top );
			oper1 = stackPop( &stack_top );

			switch( postfix_for_eval[i] )
			{
				case '+' :
					stackPush( &stack_top, (oper1 + oper2) );
					break;
				
				case '-' :
					stackPush( &stack_top, (oper1 - oper2) );
					break;

				case '*' :
					stackPush( &stack_top, (oper1 * oper2) );
					break;

				case '/' :
					stackPush( &stack_top, (oper1 / oper2) );
					break;

				case '%' :
					stackPush( &stack_top, (oper1 % oper2) );
					break;
			}
		}

		i++;
	}

	return stackPop( &stack_top );			// 완성된 결과 값을 return 시켜준다.

	
}