#include <stdio.h>
#include "student.h"

int Menu()
{
    int init = 1;
    while(init)
    {
        printf("请输入你需要进行的操作:0.退出系统\n1.添加学生\n2.显示所有学生信息\n3.按学号查询学生\n4.查看每个学生的三门的平均分和总分\n");
        scanf("%d", &init);
    }
    
    return OK;
}