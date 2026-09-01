#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

struct Student
{
    char name[20]; // 描述学生的姓名
};

int main(int argc, char const *argv[])
{
    // 以读写的方式打开文件
    // 如果文件不存在就创建一个新文件
    // 如果文件存在则清空文件中的内容
    int fd = open("hello.c", O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (fd == -1)
    {
        perror("打开文件失败");
        return -1;
    }
    printf("打开文件成功\n");
    // 往文件中写入数据
    // 1.往文件中写入一个整数
    // int value = 100;
    // ssize_t ret_write = write(fd, &value, sizeof(value));
    // if(ret_write == -1)
    // {
    //     perror("写入一个整数失败");
    //     return -1;
    // }
    // printf("写入一个整数成功, ret_write = %ld\n", ret_write);

    // 2.往文件中写入一个字符串
    // char *str = "hello";
    // ssize_t ret_write = write(fd, str, strlen(str));
    // if(ret_write == -1)
    // {
    //     perror("写入一个字符串失败");
    //     return -1;
    // }
    // printf("写入一个字符串成功, ret_write = %ld\n", ret_write);
    // 3.往文件中写入一个结构体
    struct Student stu = {"Lisi"};
    ssize_t ret_write = write(fd, &stu, sizeof(stu));
    if(ret_write == -1)
    {
        perror("写入一个结构体失败");
        return -1;
    }
    printf("写入一个结构体成功, ret_write = %ld\n", ret_write);
    // 关闭文件
    close(fd);
    return 0;
}
