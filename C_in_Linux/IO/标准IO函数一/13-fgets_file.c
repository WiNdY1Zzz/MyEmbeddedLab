#include <stdio.h>

int main(int argc, char const *argv[])
{
    //打开文件
    FILE *fp = fopen(argv[1], "r");
    if(!fp)
    {
        perror("文件打开失败");
        return -1;
    }
    printf("文件打开成功\n");

    //从文件中循环读取字符串
    char buf[BUFSIZ] = {0};
    while((fgets(buf, sizeof(buf), fp) != NULL))
    {
        printf("%s\n", buf);
    }
    
    //关闭文件
    fclose(fp);
    return 0;
}
