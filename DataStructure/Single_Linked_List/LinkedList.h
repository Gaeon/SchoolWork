//더미 노드 기반 단순 연결 리스트

#ifndef _LINKED_LIST_H_
# define _LINKED_LIST_H_

# include <stdio.h>
# include <stdlib.h>

# define TRUE 1
# define FALSE 0

typedef int LData;

typedef struct s_node
{
    int     data;
    Node    *next;
} Node;

typedef struct s_LinkedList
{
    Node    *head;
    Node    *cur;
    Node    *before;
    int     numOfData;
    int     (*comp)(LData d1, LData d2);
} LinkedList;

typedef LinkedList List;

void    ListInit(List *plist);              // List 초기화

void    LInsert(List *plist, LData data);   // List에 data 저장
void    FInsert(List *plist, LData data);
void    SInsert(List *plist, LData data);

int     LFirst(List *plist, LData *pdata);  // List의 첫번째 데이터 참조
int     LNext(List *plist, LData *pdata);   // 참조된 데이터 다음 데이터의 포인터 저장

LData   LRemove(List *plist);               // List의 데이터 삭제
int     LCount(List *plist);                // List에 저장된 데이터의 수 반환
void    SetSortRule(List *list, int (*comp)(LData d1, LData d2));

#endif
