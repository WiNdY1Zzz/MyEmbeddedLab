#include <stdio.h>
#include <stdlib.h>

#define LIST_INIT_SIZE 5
#define LISTINCREMENT 10
#define ELEMTYPE int
#define OK 1
#define OVERFLOW 0

typedef struct
{
    ELEMTYPE *elem;
    int lenth;
    int listsize;
}SqList;

int initSqList(SqList *L) //顺序表的初始化
{
    L->lenth = 0;
    L->elem = (ELEMTYPE *)malloc((L->lenth + LIST_INIT_SIZE) * sizeof(ELEMTYPE));
    if(L->elem == NULL)
    {
        printf("申请失败。\n");
        exit(OVERFLOW);
    }
    L->lenth = 0;
    L->listsize = LIST_INIT_SIZE;
    return OK;
}

int insertSqList(SqList *L, int pos, ELEMTYPE e)
{
    int index = pos - 1;
    ELEMTYPE *p = NULL;

    if(pos < 1 || pos > L->lenth + 1)
    {
        printf("位置不合法\n");
        exit(OVERFLOW);
    }

    if(L->lenth >= L->listsize)
    {
        p =  (ELEMTYPE *)realloc(L->elem, (L->lenth + LISTINCREMENT) * sizeof(ELEMTYPE));
        if(p == NULL)
        {
            printf("顺序表扩容失败\n");
            exit(OVERFLOW);
        }
        printf("扩展成功，准备进行插入\n");
        L->elem = p;
        L->listsize += LISTINCREMENT;
    }

    printf("%d\n", L->lenth);
    for(int i = L->lenth;i > index;i--)
    {
        L->elem[i] = L->elem[i - 1];
    }
    L->elem[index] = e;
    L->lenth ++;

    return OK;
}

int deleteSqList(SqList *L, int pos, ELEMTYPE *e)
{
    int index = pos - 1;
    if(pos < 1 || pos > L->lenth)
    {
        printf("非法位置\n");
        exit(OVERFLOW);
    }

    ELEMTYPE *p = &L->elem[index];
    ELEMTYPE *q = &L->elem[L->lenth - 1];
    *e = *p;
    
    for(;p < q;p++)
    {
        *p = *(p + 1);
    }
    L->lenth--;
    return(OK);
}


int main(int argc, char *argv[])
{
    SqList List;
    initSqList(&List);
    printf("数组的数据类型大小为:%d\n", sizeof(ELEMTYPE));
    printf("数组的实际长度为:%d\n", List.lenth);
    printf("数组的最大长度为:%d\n", List.listsize);
    
    SqList *p = &List;
    int arr[5] = {1,2,3,4,5};
    for(int i = 0;i < 5;i++)
    {
        p->elem[i] = arr[i];
        p->lenth++;
        printf("%d\n", p->elem[i]);
    }

    for(int i = 0;i < 5;i++)
    {
        printf("%d ", p->elem[i]);
    }
    printf("\n");

    ELEMTYPE *newbase;
    newbase = (ELEMTYPE *)realloc(p->elem, (p->lenth + 5) * sizeof(ELEMTYPE));
    if(newbase == NULL)
    {
        printf("扩展失败\n");
        exit(OVERFLOW);
    }
    p->elem = newbase;
    p->listsize += 5;
    printf("扩展成功\n");

    for(int i = 5;i < 10;i++)
    {
        p->elem[i] = i + 1;
        p->lenth++;
    }

    for(int i = 0;i < 10;i++)
    {
        printf("%d ", p->elem[i]);
    }
    printf("\n");

    //free(p->elem);

    insertSqList(&List, 4, 11);
    // printf("%d\n", List.elem[4]);

    printf("%d\n", List.lenth);
    for(int i = 0;i < List.lenth;i++)
    {
        printf("%d ", List.elem[i]);
    }
    printf("\n\n");

    int del;
    deleteSqList(&List, 10, &del);
    printf("%d\n", del);

    for(int i = 0;i < List.lenth;i++)
    {
        printf("%d ", List.elem[i]);
    }

    free(List.elem);
    return 0;
}