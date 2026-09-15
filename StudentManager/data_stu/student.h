#ifndef STUDENT_H
#define STUDENT_H

#include <stdio.h>
#include <string.h>


#define MAX_SIZE_STU 50  //定义最大学生数量
#define MAX_SIZE_COUR 3  //定义最多存储的课程数目
#define MAX_SIZE_TIMES 5  //定义最多存储该科目考试成绩的次数
#define MAX_SIZE_NAMES 32 //定义名字的最大长度
#define MAX_SIZE_NAMESOFCOURSE 20  //定义课程名字的最大长度

typedef struct CourseLNode
{
    char course_name[MAX_SIZE_NAMESOFCOURSE];  //课程名字
    int score[MAX_SIZE_TIMES];  //课程成绩
    struct CourseLNode *next;  //下一门课程
}CourseLNode,*CourseList;

typedef struct StuLNode
{
    int cur;  //系统中的位置
    int ID;  //学号
    char name[MAX_SIZE_NAMES]; //名字
    CourseList list;  //存储成绩
    struct StuLNode *next;  //下一个学生
}StuLNode,*StuList;

void Menu(void);



#endif