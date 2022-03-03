#include "ArrayList.h"

void    ListInit(List *plist)
{
    (plist->numOfData) = 0;
    (plist->curPosition) = -1;
}

void    LInsert(List *plist, LData data)
{
    if((plist->numOfData) >= LIST_LEN)
    {
        printf ("List is Full");
        return ;
    }
    plist->arr[plist->numOfData] = data;
    (plist->numOfData)++;
}

int     LFirst(List *plist, LData *pdata)
{
    if((plist->numOfData) == 0)
        return (FALSE);
    
    (plist->curPosition) = 0;
    *pdata = (plist->arr[0]);
    return (TRUE);
}

int     LNext(List *plist, LData *pdata)
{
    if((plist->curPosition) >= (plist->numOfData) - 1)
    {
        printf("End of List");
        return (FALSE);
    }
    (plist->curPosition)++;
    *pdata = (plist->arr[plist->curPosition]);
    return (TRUE);
}

LData   LRemove(List *plist)
{
    int     pos;
    LData   ret;

    pos = (plist->curPosition);
    ret = (plist->arr[pos]);
    while (pos < (plist->numOfData) - 1)
    {
        (plist->arr[pos]) = (plist->arr[pos + 1]);
        pos++;
    }
    (plist->curPosition)--;
    (plist->numOfData)--;
    return (ret);
}

int     LCount(List *plist)
{
    return (plist->numOfData);
}