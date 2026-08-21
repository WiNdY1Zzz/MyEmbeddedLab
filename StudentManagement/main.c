#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR 0

typedef struct Student
{
    int ID;
    char Name[32];
    int score[3][1];
    struct Student *prev, *next;
}*StudentList, Student;

StudentList CreateSys_DuL()
{
    StudentList L = (StudentList)malloc(sizeof(Student));
    if(!L)
    {
        printf("创建时申请内存失败\n");
        return ERROR;
    }

    L->prev = NULL;
    L->next = NULL;

    return L;
}

StudentList GetStu_DuL(StudentList *L, int pos)
{
    
}

int InsertStuList_DuL(StudentList *L, int pos)
{
    ;
}

int main(int argc, char *argv[])
{
    
    
    return 0;
}