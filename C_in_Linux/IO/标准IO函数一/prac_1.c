#include <stdio.h>

int main(int argc, const char *argv[])
{
    //1.对输入参数的个数进行检查argc参数
    if(argc != 2)
    {
        printf("参数输入错误\n");
        printf("usage:./a.out filename\n");
        return -1;
    }

    //2.使用fopen函数以只读方式进行打开文件 argv[1]
    FILE *fp = fopen(argv[1],"r");
    if(!fp)
    {
        perror("文件打开失败");
    }

    //3.使用fgetc函数进行循环读取文件中的内容
    int ch = 0;
    int line = 0;
    int last_char;
    while((ch = fgetc(fp)) != EOF)
    {
        if(ch == '\n')
        {
            //行数+1
            line++;
        }
        last_char = ch;
    }
    //对于最后一个字符进行判断
    if(last_char != '\n' && last_char != '\0')
    {
        line++; //行数+1
    }
    //4.输出结果并且关闭文件 fclose函数
    //输出结果 wc -l命令 输出结果：总行数
    printf("%d %s\n", line, argv[1]);
    //关闭文件
    int status = fclose(fp);
    if(status == EOF)
    {
        perror("文件关闭失败");
    }
    return 0;
}