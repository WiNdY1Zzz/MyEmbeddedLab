#include <stdio.h>
#include <string.h>
//学生结构体
struct Student
{
    int id; //描述学生学号
    char name[20]; //描述学生姓名
    float score; //描述学生成绩
};


int main(int argc, char const *argv[])
{
    //对输入参数的参数个数进行检查
    if(argc != 2)
    {
        printf("输入参数有误\n");
        printf("usage: ./a.out filename\n");
        return -1;
    }
    //打开文件
    FILE *fp = fopen(argv[1], "wb");
    if(!fp)
    {
        perror("文件打开失败");
        return -1;
    }
    printf("文件打开成功\n");
    //往文件中写入字符
    char ch = 'a';
    size_t ret = fwrite(&ch, 1, sizeof(ch), fp);
    if(ret < sizeof(ch))
    {
        perror("写入字符失败");
        return -1;
    }
    printf("写入字符成功\n");
    //往文件中写入字符串
    ret = fwrite("Hello World!\n", 1, strlen("Hello World!\n"), fp);
    if(ret < strlen("Hello World!\n"))
    {
        perror("写入字符串失败");
        return -1;
    }
    printf("写入字符串成功\n");
    //往文件中写入结构体
    //以二进制的方式进行写入
    //如果想以文本的形式进行查看的话，后续可以使用格式化输出的方式
    //因为数据存储格式和文本编辑器解释格式不同而导致的
    struct Student stu = {1001, "张三", 97.8};
    ret = fwrite(&stu, 1, sizeof(stu), fp);
    if(ret < sizeof(stu))
    {
        //检查是否出现错误.feof函数我们在写入操作中不需要
        if(ferror(fp))
        {
        perror("写入结构体失败");
        return -1;
        }
    }
    printf("写入结构体成功\n");
    //关闭文件
    fclose(fp);
    return 0;
}