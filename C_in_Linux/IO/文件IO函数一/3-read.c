#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, const char *argv[])
{
    // 打开文件
    //以只读的方式打开文件，如果文件不存在则会进行报错
    int fd = open("test.c", O_RDONLY);
    if(fd == -1)
    {
        perror("文件打开失败");
        return -1;
    }
    printf("文件打开成功，文件描述符是%d\n", fd);
    // 从文件中读取数据
    char buf[1024] = {0};
    // char buf[3] = {0};
    ssize_t ret_read = read(fd, buf, sizeof(buf));
    if(ret_read == -1)
    {
        perror("文件读取失败");
        return -1;
    }
    //读取文件中的数据成功，则返回读取到的数据的个数
    //如果read函数返回的是0，那么就说明读取到文件的结尾
    printf("文件读取成功, ret_read = %ld\n", ret_read);
    printf("读取到的数据是:%s\n", buf);
    // 关闭文件
    close(fd);
    return 0;
}
