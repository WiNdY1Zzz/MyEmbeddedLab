#include <stdio.h>
#include <stdlib.h>

#define LISTINCREMENT 5

typedef struct
{
    int *elem;
    int lenth;
    int listsize;
}SqList;

int initSqList(SqList *L)
{
    L->lenth = 0;
    L->listsize = 0;
    L->elem = (int *)malloc(5 * sizeof(int));
    if(L->elem == NULL)
    {
        printf("内存申请失败\n");
        exit(0);
    }
    L->listsize += 5;

    return 0;
}

int mergeSqList(SqList *L)
{
    int *newbase;
    newbase = (int *)realloc(L->elem, LISTINCREMENT * sizeof(int));
    if(newbase == NULL)
    {
        printf("顺序表扩容失败\n");
        exit(0);
    }

    L->listsize += LISTINCREMENT;
    return 1;
}

int main(int argc, char *argv[])
{
    int Arr_a[7] = {7, 23, 34, 42, 56, 89, 91};
    int Arr_b[12] = {3, 5, 11, 15, 29, 38, 44, 50, 63, 68, 77, 81};
    SqList La, Lb, Lc;
    initSqList(&La);
    initSqList(&Lb);
    initSqList(&Lc);
    int lenth_a = sizeof(Arr_a) / sizeof(int);
    int lenth_b = sizeof(Arr_b) / sizeof(int);
    
    while(La.listsize < lenth_a)
    {
        mergeSqList(&La);
    }
    while(Lb.listsize < lenth_b)
    {
        mergeSqList(&Lb);
    }
    while(Lc.listsize < lenth_a + lenth_b)
    {
        mergeSqList(&Lc);
    }

    // printf("%d %d %d", La.listsize, Lb.listsize, Lc.listsize);

    for(int i = 0;i < lenth_a;i++)
    {
        La.elem[i] = Arr_a[i];
        La.lenth++;
    }
    for(int i = 0;i < lenth_b;i++)
    {
        Lb.elem[i] = Arr_b[i];
        Lb.lenth++;
    }

    printf("%d %d\n", La.lenth, Lb.lenth);

    int *p = La.elem;
    int *q = Lb.elem;
    int *pc = Lc.elem;
    int *x = La.elem + La.lenth - 1;
    int *y = Lb.elem + Lb.lenth - 1;

    printf("%d %d\n", *x, *y);


    while(p <= x && q <= y)
    {
        if(*p <= *q)
        {
            *pc++ = *p++; 
            Lc.lenth++;
        }
        else
        {
            *pc++ = *q++;
            Lc.lenth++;
        }
    }

    while(p <= x)
    {
        *pc++ = *p++;
        Lc.lenth++;
    }
    while(q <= y)
    {
        *pc++ = *q++;
        Lc.lenth++;
    }
    // printf("\n%d\n666", Lc.lenth);
    
    for(int i = 0;i < Lc.lenth;i++)
    {
        printf("%d ", Lc.elem[i]);
    }
    
    return 0;
}