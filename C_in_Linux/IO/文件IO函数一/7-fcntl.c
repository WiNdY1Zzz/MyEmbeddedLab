#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    // 打开文件
    // 以读写的方式打开文件，如果文件不存在的话，则要创建新的文件
    // 如果文件存在的话，则要将文件中原有的内容进行清空操作
    int fd = open("hello.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (fd == -1)
    {
        perror("文件打开失败");
        return -1;
    }
    printf("文件打开成功\n");
    // 给文件进行加锁
    // 定义一个锁的结构体
    struct flock lock;
    lock.l_type = F_WRLCK;    // 写锁
    lock.l_whence = SEEK_SET; // 从文件的开头文字进行加锁
    lock.l_start = 0;         // 从文件的开头进行加锁
    lock.l_len = 0;           // 加锁长度为0, 直接加锁到文件的末尾
    int ret_fcntl = fcntl(fd, F_SETLK, &lock);
    if (ret_fcntl == -1)
    {
        perror("加锁失败");
        return -1;
    }
    printf("加锁成功\n");
    // 加锁时针对于其他进程而言的，是其他进程不能往文件中写入内容
    // 但是对于自身进程而言，是可以往文件中进行写内容的
    // 因为fcntl函数是建议性的，不是强制性的
    // 给文件中写入内容
    char *str = "hello world";
    ssize_t ret_write = write(fd, str, strlen(str));
    if (ret_write == -1)
    {
        perror("写入失败");
        return -1;
    }
    printf("写入成功\n");
    // 给文件解锁
    lock.l_type = F_UNLCK;
    ret_fcntl = fcntl(fd, F_UNLCK, &lock);
    if (ret_fcntl == -1)
    {
        perror("解锁失败");
        return -1;
    }
    printf("解锁成功\n");
    // 关闭文件
    close(fd);
    return 0;
}
