#include <stdio.h>

int main(int argc,const char *argv[])
{
    //打开文件
    //"w"模式下，如果文件存在则会将文件进行清空
    //如果文件不存在则会创建文件
    FILE* fp = fopen("test_1.txt","w");
    if(!fp)
    {
        perror("文件打开失败");
    }
    printf("文件打开成功\n");
    //往文件中写入字符
    int ch = 0;
    // if((ch = fputc('w', fp)) == EOF)
    // {
    //     perror("文件写入失败");
    // }
    //往文件中写入多个字符
    for(int i = 0;i < 6;i++)
    {
        ch = fputc('a' + i, fp);
        printf("文件写入成功，写入的字符为:%c\n", ch);
    }
    //关闭文件
    if(fclose(fp) == EOF)
    {
        perror("文件关闭失败");
    }
    return 0;
}