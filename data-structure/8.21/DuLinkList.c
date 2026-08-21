#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 1
#define ERROR 0

typedef struct DuLNode
{
    int data;
    struct DuLNode *prior, *next;
}DuLNode, *DuLinkList;

DuLinkList CreateList_DuL()
{
    DuLinkList L = (DuLinkList)malloc(sizeof(DuLNode));
    if(L == NULL)
    {
        printf("为双向链表申请内存失败\n");
        return NULL;
    }
    L->prior = NULL;
    L->next = NULL;
    return L;
}

DuLinkList GetElem_DulL(DuLinkList *L, int pos)
{
    DuLinkList p = (*L)->next;
    if(!p)
    {
        printf("该双向链表为空链表");
        return NULL;
    }
    for(int i = 0;i < pos - 1;i++)
    {
        p = p->next;
        if(!p) //防止pos超出链表长度
        {
            return NULL;
        }
    }

    return p;
}

int InsertList_DuL(DuLinkList *L, int pos, int e)
{
    DuLinkList p = GetElem_DulL(L, pos - 1);
    if(!p)
    {
        printf("插入位置不合法\n");
        return ERROR;
    }

    DuLinkList s = (DuLinkList)malloc(sizeof(DuLNode));
    if(!s)
    {
        printf("新节点内存申请失败\n");
        return ERROR;
    }
    s->data = e;

    s->prior = p;
    s->next = p->next;
    if(p->next)
    {
        p->next->prior = s;
    }
    p->next = s;

    return OK;
}

int DeleteList_DuL(DuLinkList *L, int pos, int *e)
{
    DuLinkList p = GetElem_DulL(L, pos);
    if(!p)
    {
        printf("删除位置不合法\n");
        return ERROR;
    }

    *e = p->data;

    p->prior->next = p->next;

    if(p->next)
    {
        p->next->prior = p->prior;
    }

    free(p);
    return OK;
}

int TraverList_DuL(DuLinkList L)
{
    DuLinkList p = L->next;
    if(!p)
    {
        printf("该链表为空\n");
        return ERROR;
    }

    while(p)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    putchar('\n');

    return OK;
}



int main(int argc, char *argv[])
{

    
    
    return 0;
}