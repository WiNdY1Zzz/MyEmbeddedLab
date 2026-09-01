#ifndef STUDENT_H
#define STUDENT_H

#define MAX_SIZE 40
#define OK 1

typedef struct student
{
    int ID;
    char name[32];
    int score[3][1];
}student;

#endif