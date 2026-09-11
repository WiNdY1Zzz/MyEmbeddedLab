/*
    有名管道在使用的时候必须要保证读端和写端都被打开, open操作才会返回
    有名管道一般不用于亲缘关系进程之间的通信
    有名管道一般用于非亲缘关系进程之间的通信
    有名管道中我们必须要调用unlink函数
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    // 1.对输入参数的参数个数进行检查
    if (argc != 2)
    {
        printf("输入参数的参数个数有误\n");
        printf("usage: ./a.out filename\n");
        return -1;
    }
    // 2.创建有名管道
    // 如果管道文件存在, 则会进行报错
    int mkfifo_ret = mkfifo(argv[1], 0664);
    if (mkfifo_ret == -1)
    {
        perror("创建有名管道失败");
        return -1;
    }
    printf("创建有名管道成功\n");
    // 3.创建子进程  fork()
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("创建子进程失败");
        return -1;
    }
    else if (pid == 0)
    {
        // 子进程
        // 打开管道文件
        // 在进程中以只写的方式打开管道文件
        // 内核管道缓冲区是在第一次open函数调用(打开管道文件)的时候才会进行分配
        int fd = open(argv[1], O_WRONLY);
        if (fd == -1)
        {
            perror("子进程打开管道文件失败");
            unlink(argv[1]);
            return -1;
        }
        printf("子进程打开管道文件成功\n");
        // 往管道文件中写入数据
        char buf[] = "Hello World!";
        ssize_t ret_write = 0;
        if((ret_write = write(fd, buf, sizeof(buf))) == -1)
        {
            perror("子进程往管道文件中写入数据失败");
            return -1;
        }
        printf("子进程往管道文件中写入数据成功\n");
        // 关闭管道文件
        int ret_close = close(fd);
        if (ret_close == -1)
        {
            perror("子进程关闭管道文件失败");
            return -1;
        }
        printf("子进程关闭管道文件成功\n");
        // 让子进程进行退出
        exit(EXIT_SUCCESS); // 正常退出
    }
    else if (pid > 0)
    {
        // 父进程
        int fd = open(argv[1], O_RDONLY);
        if (fd == -1)
        {
            perror("父进程打开管道文件失败");
            unlink(argv[1]);  //清理有名管道
            return -1;
        }
        printf("父进程打开管道文件成功\n");
        //针对于unlink函数仅仅是删除文件系统中的"文件名链接"
        //已经打开的文件描述符还可以正确的从管道文件中进行读写操作
        //可以避免误删文件名或者是提前删除文件名导致对管道文件中的数据读写操作失败
        // if(-1 == (unlink(argv[1])))
        // {
        //     perror("unlink error\n");
        //     return -1;
        // }
        // printf("unlink ok\n");
        // 等待子进程退出
        wait(NULL); // 不关注子进程的退出状态值
        // 打开管道文件
        // 从管道文件中读取数据
        char buf[BUFSIZ] = {0};
        ssize_t ret_read = 0;
        if ((ret_read = read(fd, buf, sizeof(buf))) == -1)
        {
            perror("父进程从管道文件中读取数据失败");
            return -1;
        }
        printf("父进程从管道文件中读取数据成功\n");
        printf("读取到的数据为:%s\n", buf);
        //  关闭管道文件
        if (-1 == close(fd))
        {
            perror("父进程关闭管道文件失败");
            return -1;
        }
        printf("父进程关闭管道文件成功\n");
        //自动清理有名管道
        if(-1 == (unlink(argv[1])))
        {
            perror("自动清理有名管道失败");
            return -1;
        }
        printf("自动清理有名管道成功\n");
        //不要重复使用unlink函数
    }
    return 0;
}
