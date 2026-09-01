#include <stdio.h>

int main()
{
    //打开文件
    FILE* fp = fopen("/home/windyi/study/IO/test.c","r");
    if(!fp)
    {
        printf("文件打开失败\n");
        return -1;
    }
    printf("文件打开成功\n");

    int status = fclose(fp);
    if(!status)
    {
        printf("文件关闭成功\n");
        return 0;
    }
    printf("文件关闭失败\n");
    return EOF;
}