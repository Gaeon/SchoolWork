#include "ArrayList.h"

int main(void)
{
    List    list;       // List 생성
    int     data;

    ListInit(&list);    // List 초기화

    LInsert(&list, 11); // List 데이터 저장
    LInsert(&list, 22);
    LInsert(&list, 33);
    LInsert(&list, 44);
    LInsert(&list, 55);

    if (LFirst(&list, &data))
    {
        printf("%d\n", data);
        while(LNext(&list, &data))
            printf("%d\n", data);
    }
    
}