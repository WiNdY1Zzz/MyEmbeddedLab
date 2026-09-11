// 测试无名管道在Linux系统中的大小  64KB
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    // 1.创建无名管道
    int pipefd[2] = {0};
    int pipe_ret = pipe(pipefd);
    if (pipe_ret == -1)
    {
        perror("创建无名管道失败");
        return -1;
    }
    printf("创建无名管道成功");
    // 2.使用fork函数创建子进程
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("创建子进程失败");
        return -1;
    }
    else if (pid == 0)
    {
        // 子进程
        // 关闭读端
        close(pipefd[0]);
        char buf[1024] = {0};
        // 往管道中进行写数据, 专注测试于无名管道的大小
        // 当把管道写满之后, 管道就进入到一个阻塞状态
        // 直到管道有地方之后, 才会继续往管道中进行写数据
        // 当管道被写满之后, 并不会直接返回错误
        ssize_t write_ret = 0;
        int count = 0; // 记录写入的字节数
        // 循环写入, 直到写满或者是写入失败
        while(1)
        {
            if((write_ret = write(pipefd[1], buf, sizeof(buf))) == -1)
            {
                perror("往管道中写数据失败");
                return -1;
            }
            printf("往管道中写数据成功\n");
            count += write_ret;
            // 65536字节 / 1024 = 64KB
            printf("累计写入数据%d字节\n", count);
        }
        // 关闭写端
        close(pipefd[1]);
    }
    else if(pid > 0)
    {
        // 父进程
        // 关闭写端
        close(pipefd[1]);
        wait(NULL);       // 等待子进程的退出
        close(pipefd[0]); // 关闭读端
    }
    return 0;
}
