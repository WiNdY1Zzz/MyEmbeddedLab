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
        i++;
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

int DeleteList_L(LinkList *L, int pos, int *e)
{
    LinkList p = *L;
    if(!p->next)
    {
        printf("链表为空\n");
        return ERROR;
    }
    int i = 0;

    while(p && i < pos - 1) //遍历寻找到第pos-1个节点
    {
        p = p->next;
        i++;
    }

    if(!p || i > pos - 1)
    {
        printf("选定的删除位置非法\n");
        return ERROR;
    }

    *e = p->next->data;
    LinkList q = p->next;
    p->next = p->next->next;
    free(q);

    return OK;
}

int ReverseList_L(LinkList *L)
{
    LinkList p = *L;
    if(!p->next || !p->next->next)
    {
        printf("链表是空的或者只有一个节点，无需逆序\n");
        return ERROR;
    }

    LinkList prev = NULL;
    LinkList cur = p->next;
    LinkList next = NULL;

    while(cur != NULL)
    {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }

    (*L)->next = prev;

    return OK;
}

int MergeList_L(LinkList *La, LinkList *Lb, LinkList *Lc)
{
    (*Lc) = (LinkList)malloc(sizeof(LNode));
    if((*Lc) == NULL)
    {
        printf("为备用链表申请指针的内存失败\n");
        return ERROR;
    }

    LinkList pa = (*La)->next;
    LinkList pb = (*Lb)->next;
    LinkList pc = *Lc;
    pc->next = NULL;

    while(pa && pb)
    {
        if(pa->data < pb->data)
        {
            pc->next = pa;
            pa = pa->next;
        }
        else
        {
            pc->next = pb;
            pb = pb->next;
        }

        pc = pc->next;
    }

    pc->next = pa ? pa : pb;

    return OK;
}

int BubbleSortList_L(LinkList *L)
{
    if(!(*L)->next || !(*L)->next->next)
    {
        printf("链表是空的或者只有一个节点\n");
        return ERROR;
    }

    LinkList p, q;
    int temp, swapped;
    int len = 0;

    p = (*L)->next;
    while(p)
    {
        len++;
        p = p->next;
    }

    for(int i = 0;i < len - 1;i++)
    {
        p = (*L)->next;
        swapped = 0;
        
        for(int j = 0;j < len - 1 - i;j++)
        {
            q = p->next;
            if(p->data > q->data)
            {
                temp = p->data;
                p->data = q->data;
                q->data = temp;
                swapped = 1;
            }

            p = p->next;
        }

        if(!swapped)
            break;
    }

    return OK;
}

int HasCycle(LinkList L)
{
    LinkList slow = L->next;
    LinkList fast = L->next;

    if(!slow || !slow->next)
    {
        printf("该链表是空的或者只有一个节点，不可能成环\n");
        return ERROR;
    }

    while(fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
        if(fast == slow)
        {
            printf("该链表成环\n");
            return OK;
        }
    }

    printf("该链表不成环\n");
    return OK;
}



int main(int argc, char *argv[])
{
    LinkList L1, L2;
    int n;
    printf("请输入创建的链表L1的节点数\n");
    scanf("%d", &n);
    CreateList_L(&L1, n);
    // ReverseList_L(&L1);
    BubbleSortList_L(&L1);
    printf("请输入创建的链表L2的节点数\n");
    scanf("%d", &n);
    CreateList_L(&L2, n);
    // ReverseList_L(&L2);
    BubbleSortList_L(&L2);

    TraverseList(L1);
    TraverseList(L2);


    // LNode *p1 = L1->next;
    // TraverseList(L);

    // ListInsert_L(&L, 2, 10);
    // TraverseList(L);

    // ReverseList_L(&L);
    // TraverseList(L);

    // LinkList L3;

    // MergeList_L(&L1, &L2, &L3);
    // TraverseList(L3);

    return 0;
}