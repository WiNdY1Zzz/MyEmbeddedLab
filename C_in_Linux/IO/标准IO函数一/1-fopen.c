#include <stdio.h>

int main()
{
    //1.以只读方式打开文件,如果文件不存在则报错
    // FILE* fp = fopen("/home/windyi/study/IO/test.c","r");
    //2.如果不提供路径，那么仅在当前路径下寻找
    //3.如果以a，即追加的方式打开文件，那么文件不存在时则创建文件
    //文件存在，也不会清空原文件内容
    FILE* fp = fopen("test.c","r");
    if(!fp)
    {
        printf("文件打开失败\n");
        return -1;
    }
    printf("文件打开成功\n");

    return 0;
}