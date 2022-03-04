//원형 연결 리스트

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
} LinkedList;