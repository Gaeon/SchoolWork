//더미 노드 기반 단순 연결 리스트

#include "LinkedList.h"

void    ListInit(List *plist)
{
    plist->head = (Node *)malloc(sizeof(Node));
    plist->head->next = NULL;
    plist->comp = NULL;
    plist->numOfData = 0;
}

void    LInsert(List *plist, LData data)
{
    if(plist->comp == NULL)
        FInsert(plist, data);
    else
        SInsert(plist, data);
}

void    FInsert(List *plist, LData data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;

    newNode->next = plist->head->next;
    plist->head->next = newNode->next;

    (plist->numOfData)++;
}

void    SInsert(List *plist, LData data)
{
    Node    *newNode = (Node *)malloc(sizeof(Node));
    Node    *prev;

    newNode->data = data;
    prev = plist->head;

    while(prev->next != NULL && plist->comp(data, prev->next->data) != 0)
    {
        prev = prev->next;
    }

    newNode->next = prev->next;
    prev->next = newNode;

    (plist->numOfData)++;
}

int     LFirst(List *plist, LData *pdata)
{
    if(plist->head->next == NULL)   //Dummy node가 NULL을 가리키는 경우
        return (FALSE);
    
    plist->before= plist->head;     //before이 Dummy node를 가리킴
    plist->cur = plist->head->next; //cur이 첫번째 노드를 가리킴
    
    *pdata = plist->cur->data;      //첫번째 노드의 데이터 전달
    return (TRUE);
}

int     LNext(List *plist, LData *pdata)
{
    if(plist->cur->next == NULL)    //cur이 NULL을 가리키는 경우
        return (FALSE);
    
    plist->before = plist->cur;     //before이 cur을 가리킴
    plist->cur = plist->cur->next;  //cur이 다음 노드를 가리킴

    *pdata = plist->cur->data;      //현재 노드의 데이터 전달
    return (TRUE);
}

LData   LRemove(List *plist)
{
    Node    *remove;
    LData   removeData;

    remove = plist->cur;            //remove 할 node
    removeData = plist->cur->data;  //remove 할 node의 data

    plist->before->next = plist->cur->next;
    plist->cur = plist->before;

    free(remove);                   //메모리 해제를 통한 remove
    (plist->numOfData)--;

    return(removeData);
}

int     LCount(List *plist)
{
    return (plist->numOfData);
}

void    SetSorRule(List *plist, int (*comp)(LData d1, LData d2))
{
    plist->comp = comp;
}