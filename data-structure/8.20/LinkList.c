#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 1
#define ERROR 0

typedef struct LNode
{
    int data;
    struct LNode *next;
}*LinkList,LNode;

int CreateList_L(LinkList *L, int n)
{
    *L = (LinkList)malloc(sizeof(LNode));
    if(*L == NULL)
    {
        printf("为链表指针申请内存失败\n");
        return ERROR;
    }

    (*L)->next = NULL;

    int count = 0;
    for(int i = 0;i < n;i++)
    {
        count++;
        LNode *p = (LNode *)malloc(sizeof(LNode));
        
        if (!p)
        {
            printf("第%d次节点内存申请失败\n", count);
            return ERROR;
        }

        scanf("%d", &p->data);
        p->next = (*L)->next;
        (*L)->next = p;
    }

    return OK;
}

int TraverseList(LinkList L)
{
    LinkList p = L->next;
    if(!p)
    {
        printf("该链表还没有节点\n");
        return ERROR;
    }
    while(p != NULL)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");

    return OK;
}

int ListInsert_L(LinkList *L, int pos, int e)
{
    LinkList p = *L;   //用指针p指向头节点
    int i = 0;

    while(p && i < pos - 1) //遍历寻找到第pos - 1个节点
    {
        p = p->next;
        ++i;
    }

    if(!p || i > pos - 1)
    {
        printf("插入位置不合法\n");
        return ERROR;
    }

    LinkList s = (LinkList)malloc(sizeof(LNode));
    if(!s)
    {
        printf("为新节点申请内存失败\n");
        return ERROR;
    }
    s->data = e;
    s->next = p->next;
    p->next = s;

    return OK;
}




int main(int argc, char *argv[])
{
    LinkList L;
    int n;
    printf("请输入创建的链表的节点数\n");
    scanf("%d", &n);
    CreateList_L(&L, n);
    LNode *p = L->next;
    TraverseList(L);

    ListInsert_L(&L, 2, 10);
    TraverseList(L);


    return 0;
}