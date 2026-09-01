#include <stdio.h>

int main(int argc,const char *argv[])
{
    //1.对输入的参数个数进行检查
    if(argc != 3)
    {
        printf("参数输入错误\n");
        printf("usage:./a.out src dst\n");
        return -1;
    }
    //2.用fopen函数对源文件和目标文件进行打开操作
    //用fopen函数打开源文件
    FILE *fp_src = fopen(argv[1], "r");
    if(!fp_src)
    {
        perror("源文件打开失败");
    }
    printf("源文件打开成功\n");
    //用fopen函数打开目标文件
    FILE *fp_dst = fopen(argv[2], "w");
    if(!fp_dst)
    {
        perror("目标文件打开失败");
    }
    printf("目标文件打开成功\n");
    //3.用fgetc函数从源文件中读取字符
    int ch = 0;
    while((ch = fgetc(fp_src)) != EOF)
    {
        //往目标文件中写入字符
        fputc(ch, fp_dst);
    }
    //  用fputc函数将读取到的字符写入目标文件
    //4.关闭文件
    fclose(fp_src);
    fclose(fp_dst);
    return 0;
}