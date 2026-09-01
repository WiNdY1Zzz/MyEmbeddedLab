#include <stdio.h>

int main(int argc, char const *argv[])
{
    //1.打开文件
    FILE *fp = fopen(argv[1], "w");
    if(!fp)
    {
        perror("文件打开失败");
        return -1;
    }
    printf("文件打开成功");
    //2.往文件中写入字符串
    // fputs("Hello World!\n", fp);
    // fputs("Hello World!\n", fp);
    // fputs("Hello World!\n", fp);
    // fputs("Hello World!\n", fp);
    for(int i = 0;i < 5;i++)
    {
        fputs("Hello World!\n", fp);
    }
    //3.关闭文件
    fclose(fp);

    return 0;
}
