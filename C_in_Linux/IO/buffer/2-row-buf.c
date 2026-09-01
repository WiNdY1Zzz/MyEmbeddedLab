#include <stdio.h>

int main(int argc, char const *argv[])
{
    //1.当遇到换行符会刷新缓冲区
    // printf("Hello World\n");
    // while(1);
    //2.当程序正常结束时会刷新缓冲区
    // printf("Hello World");
    //3.当文件关闭时会刷新缓冲区
    // FILE *fp = fopen("./1.txt", "w");
    // if(!fp)
    // {
    //     perror("文件打开失败");
    //     return -1;
    // }
    // printf("文件打开成功\n");
    // //往文件中写入字符
    // fputc('a', fp);
    // fputc('b', fp);
    // fputc('c', fp);
    // fputc('d', fp);
    // //关闭文件
    // fclose(fp);
    // while(1);
    //4.当输入和输出进行切换的时候会刷新缓冲区
    // printf("Hello");
    // int value = 0;
    // scanf("%d", &value);
    // printf("你输入的整数为:%d", value);
    // while(1);
    //5.当缓冲区写满的时候会刷新缓冲区(可能未到换行符)
    // for(int i = 0;i < 3;i++)
    // {
    //     printf("Hello World!");
    // }
    // while(1);
    //6.当主动调用fflush函数
    printf("123456");
    fflush(stdout);
    while(1);

    return 0;
}
