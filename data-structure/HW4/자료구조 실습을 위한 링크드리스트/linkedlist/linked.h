#include <stdio.h>
#include <stdlib.h>

typedef struct _a {	
	int key;
	struct _a *link;
}Node;	//Node 구조체 선언

int count=0;	//노드 개수를 위한 카운터 전역변수 선언

typedef struct _b {
	Node *Head;			//Head이름의 4바이트 주소 포인터 선언
	Node *Tail;			//Tail이름의 4바이트 주소 포인터 선언
}Linked_List;			//Node 전체 리스트 구조체 선언

typedef Node *list_ptr;			//Node에 대한 포인터 타입 선언
//typedef Linked_List *list;

void First(Linked_List *list)		// Head부와 Tail부 초기화
{
	list->Head = list->Tail = NULL;
}
void AddtoHead(Linked_List *list, int num)		//Head부 추가 함수
{
	Node *New, *Temp;
	if(list->Head==NULL)							//초기화 상태시
	{
		New = (list_ptr)malloc(sizeof(Node));		//New 공간 할당
		New->key=num;								//New에 key값 추가
		New->link=NULL;								//New link에 NULL 삽입
		list->Head=list->Tail=New;					// Tail부와 Head부 New를 가리키도록 설정
	}
	else
	{
		Temp = (list_ptr)malloc(sizeof(Node));		//Temp 공간 할당
		Temp->link=list->Head;						//Temp link를 Head부가 가리키는 것으로 설정
		Temp->key=num;								//Temp에 key값 추가
		list->Head=Temp;							//Head부와 Temp를 연결시킴
	}	
	count++;										//추가므로 카운터 1증가
}

void AddtoTail(Linked_List *list, int num)		//Tail부 추가 함수
{
	
	Node *New, *Temp;
	if(list->Tail==NULL)							//초기화 상태시
	{
		New = (list_ptr)malloc(sizeof(Node));
		
		New->key=num;
		New->link=NULL;								
		list->Tail = list->Head = New;				//Tail부와 Head부를 New와 일치
	}
	else
	{
		Temp = (list_ptr)malloc(sizeof(Node));
		Temp->key=num;								
		Temp->link=NULL;							
		list->Tail->link=Temp;						//Tail의 link와 Temp를 연결
		list->Tail=Temp;							//Tail과 Temp를 연결
	}
	count++;
}							//Tail의 link와 Temp를 먼저 연결하는 이유 : list->Tail=Temp를 먼저하면 연결이 끊어져 찾을수가 없음
							/*													
							if (list->Tail==NULL){
							list->Tail = malloc(sizeof(Node));
							list->Tail->key = num;
							list->Tail->link = NULL;
							list->Head = list->Tail;
							}
							
							  else{
							  
								list->Tail->link = malloc(sizeof(Node));
								list->Tail->link ->key = num;
								list ->Tail->link->link = NULL;
								list ->Tail = list->Tail->link;
								}
								
								  }
*/
void DeltoHead(Linked_List *list)			//헤드부 앞에서부터 삭제
{
	Node *Temp;								//구조체에 대한 포인터 변수Temp선언
	Temp=list->Head;						//Temp와 Head는 같음
	list->Head=list->Head->link;			//헤드부를 헤드의 링크와 연결된 부분과 연결
	free(Temp);								//Temp를 버림
	count--;								//삭제이므로 카운터 1 감소
}

void DeltoTail(Linked_List *list)					//Tail부 삭제
{
	int i = 0;										//노드 위치와의 비교를 위한 변수 i선언
	Node *Temp;
	//	Temp = (list_ptr)malloc(sizeof(Node));
	Temp=list->Head;								//Temp의 초기화 선언
    while(1)										//참일때까지
	{
		if(i==count-1)								//노드가 한개 있을 시
		{
			DeltoHead(list);
			count--;
			break;
		}
		else if(i== count-2)						//노드 끝부분에 왔을 때
		{
			Temp->link= NULL;						//Temp의 링크는 널값
			free(Temp->link);						//Temp와 연결된 마지막 노드 버림
			count--;
			break;
		}
		Temp = Temp->link;							//조건에 맞을때까지 Temp의 링크는 계속 이동
		i++;										//조건에 맞을 때까지 i값 증가
	}
	
}

void insert(Linked_List *list, int where, int num)		//임의 추가 함수 
{
	int i = 1;											//i값 초기화
	Node *Temp;											
	Node *New;
	New=list->Head;
	Temp = (list_ptr)malloc(sizeof(Node));
	if(count==0)										//노드가 비었을 시
	{
		AddtoHead(list, num);
		count++;
		return ;
	}
	else if(count==where)								//노드가 꽉 찼을 시
	{
		AddtoTail(list, num);
		count++;
		return ;
	}
	else
		while(i=where-2)								//추가 할 노드의 위치가 중간에 있을 시
		{
			New=New->link;
			i++;
		}
		Temp->key=num;
		Temp->link=New->link;
		New->link=Temp;
		count++;
}
void Delete(Linked_List *list, int where)			//임의 삭제 함수
{
	int i = 1;
	Node *Temp; 
	Temp=list->Head;
	if(count==1)									//노드가 한개 있을 시
	{
		DeltoHead(list);
		count--; 
		return ;
	}
	else if(count==where)							//노드가 꽉 찼을 시
	{
		DeltoTail(list);
		count--;
		return ;
	}
	else{ 
		while(i=where-1){							//삭제할 노드의 위치가 중간에 있을 시
			Temp= Temp->link;
			i++;
			break ;
		}
		Temp->link->link=Temp->link->link->link;
		count--;
	}
	
}



void printList(Linked_List *list)				//출력 함수 부분
{
	Node *Tmp;									//Node포인터 타입 Tmp 선언
	Tmp = (list_ptr)malloc(sizeof(Node));		//공간할당
	Tmp = list->Head;							//Tmp를 Head부로 대입
	
	while(Tmp!=NULL)							//Tmp가 NULL이 되기 전까지
	{
		printf("%d -> ", Tmp->key);				//Tmp의 각 키 값을 출력
		Tmp = Tmp->link;						//계속적으로 Tmp의 link로 연결
	}
	printf("\n");
}