#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    // 1.创建无名管道
    //无名管道是单向的, 支持半双工通信方式
    //一段用于读(pipefd[0]), 一段用于写(pipefd[1])
    int fd[2] = {0};
    int pipe_ret = pipe(fd);
    if (pipe_ret == -1)
    {
        perror("创建无名管道失败");
        return -1;
    }
    // 注意  1.pipe的文件描述符跟open函数的文件描述符使用的是同一组
    // 注意  2.fd[0]表示的是读端, fd[1]表示的是写端
    printf("创建无名管道成功, fd[0] = %d, fd[1] = %d\n", fd[0], fd[1]);
    // 2.创建子进程
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("创建子进程失败");
        return -1;
    }
    else if (pid == 0)
    {
        // 子进程
        // 子进程接收父进程的数据  读数据
        // 关闭子进程的写端
        if ((close(fd[1])) == -1)
        {
            perror("关闭子进程写端失败");
            return -1;
        }
        printf("关闭子进程写端成功\n");
        // 从无名管道中读取数据
        char buf_str[BUFSIZ] = {0};
        ssize_t read_ret = read(fd[0], buf_str, sizeof(buf_str));
        if (read_ret == -1)
        {
            perror("从无名管道中读取数据失败");
            return -1;
        }
        printf("从无名管道中读取数据成功, 读取到的数据为:\n");
        printf("%s", buf_str);
        // 关闭子进程的读端
        if ((close(fd[0])) == -1)
        {
            perror("关闭子进程读端失败");
            return -1;
        }
        printf("关闭子进程读端成功\n");
        // 子进程退出
        exit(EXIT_SUCCESS);
    }
    else if (pid > 0)
    {
        // 父进程
        // 父进程给子进程发送数据  写数据
        // 关闭父进程的读端
        int close_ret = close(fd[0]);
        if (close_ret == -1)
        {
            perror("关闭父进程读端失败");
            return -1;
        }
        printf("关闭父进程读端成功\n");
        // 往无名管道中写数据
        char *str = "Hello World!\n";
        ssize_t write_ret = write(fd[1], str, strlen(str));
        if (write_ret == -1)
        {
            perror("往无名管道中写数据失败");
            return -1;
        }
        printf("往无名管道中写数据成功\n");
        // 关闭父进程的写端
        if ((close(fd[1])) == -1)
        {
            perror("关闭父进程写端失败");
            return -1;
        }
        printf("关闭父进程写端成功, 已将数据写入无名管道中\n");
        // 等待子进程退出
        wait(NULL); // 不关注的子进程的退出状态
    }
    return 0;
}
