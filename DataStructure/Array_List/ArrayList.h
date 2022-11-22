#ifndef _ARRAY_LIST_H_
# define _ARRAY_LIST_H_

#include <stdio.h>

#define TRUE 1
#define FALSE 0

#define LIST_LEN 100

typedef int LData;

typedef struct  s_ArrayList
{
    LData   arr[LIST_LEN];
    int     numOfData;
    int     curPosition; 
} ArrayList;

typedef ArrayList List;

void    ListInit(List *plist);              // List 초기화
void    LInsert(List *plist, LData data);   // List에 data 저장
int     LFirst(List *plist, LData *pdata);  // List의 첫번째 데이터 참조
int     LNext(List *plist, LData *pdata);   // 참조된 데이터 다음 데이터의 포인터 저장
LData   LRemove(List *plist);               // List의 데이터 삭제
int     LCount(List *plist);                // List에 저장된 데이터의 수 반환

#endif