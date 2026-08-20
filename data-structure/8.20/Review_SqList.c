#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT_LIST_SIZE 5
#define LISTINCREMENT 5

typedef struct
{
    int *elem;
    int lenth;
    int listsize;
}SqList;

void initSqList(SqList *L)
{
    L->elem = (int *)malloc(INIT_LIST_SIZE * sizeof(int));
    if(L->elem == NULL)
    {
        printf("顺序表初始化内存申请失败\n");
    }

    // L->elem = {0};
    memset(L->elem, 0, INIT_LIST_SIZE * sizeof(int));
    L->lenth = 0;
    L->listsize = INIT_LIST_SIZE;
    return;
}

void insertSqList(SqList *L, int pos, int e)
{
    if(pos < 1 || pos > L->lenth + 1)
    {
        printf("位置非法，顺序表需要连续存储\n");
        return;
    }
    int index = pos - 1;
    int *newbase = NULL;
    if(L->lenth + 1 > L->listsize)
    {
        newbase = (int *)realloc(L->elem, (L->listsize + LISTINCREMENT) * sizeof(int));
        if(newbase == NULL)
        {
            printf("插入数据时扩容内存申请失败\n");
            return;
        }
        L->elem = newbase;
        L->listsize += LISTINCREMENT;
    }

    for(int i = L->lenth;i > index;i--)
    {
        L->elem[i] = L->elem[i - 1];
    }
    L->elem[index] = e;
    L->lenth += 1;

    return;
}

void deleteSqList(SqList *L, int pos, int *e)
{
    if(pos < 1 || pos > L->lenth)
    {
        printf("指定删除的位置不合法\n");
        return;
    }
    int index = pos - 1;
    *e = L->elem[index];
    for(int i = index;i < L->lenth - 1;i++)
    {
        L->elem[i] = L->elem[i + 1];
    }
    L->lenth -= 1;

    return;    
}

void mergeSqList(SqList *La, SqList *Lb, SqList *Lc)
{
    int *pa = La->elem;
    int *pb = Lb->elem;
    int *pa_last = &La->elem[La->lenth - 1];
    int *pb_last = &Lb->elem[Lb->lenth - 1];
    int *newbase;
    int count = 0;
    while(Lc->listsize < (La->lenth + Lb->lenth))
    {
        newbase = (int *)realloc(Lc->elem, (Lc->listsize + LISTINCREMENT) * sizeof(int));
        count++;
        if(newbase == NULL)
        {
            printf("顺序表C在第%d次扩容时失败\n", count);
            printf("当前表C的最大容量为%d\n", Lc->listsize);
            return;
        }
        Lc->elem = newbase;
        Lc->listsize += LISTINCREMENT;
    }

    int *pc = Lc->elem;

    while(pa <= pa_last && pb <= pb_last)
    {
        if(*pa < *pb)
        {
            *pc++ = *pa++;
            Lc->lenth++;
        }
        else
        {
            *pc++ = *pb++;
            Lc->lenth++;
        }
    }
    while(pa <= pa_last)
    {
        *pc++ = *pa++;
        Lc->lenth++;
    }
    while(pb <= pb_last)
    {
        *pc++ = *pb++;
        Lc->lenth++;
    }
    
    return;
}

int main(int argc, char *argv[])
{
    SqList La;
    initSqList(&La);
    int Arr_a[5] = {2, 4, 1, -3, 5};

    printf("%d\n", La.listsize);
    printf("%d\n", La.elem[0]);

    for(int i = 0;i < La.listsize;i++)
    {
        La.elem[i] = Arr_a[i];
        La.lenth++;
    }

    printf("%d\n", La.lenth);

    for(int i = 0;i < La.lenth;i++)
    {
        printf("%d ", La.elem[i]);
    }
  

    return 0;
}