#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void handler(int sig)
{
    //SIGCHLD信号捕捉之后的操作
    if(sig == SIGCHLD)
    {
        printf("子进程退出, 捕捉到了SIGCHLD信号\n");
        //父进程回收子进程的资源
        wait(NULL);  //不关注子进程的退出状态值
    }
    
}

int main(int argc, char const *argv[])
{
    // 1.建立信号与信号处理方式的关联  SIGCHLD
    if (SIG_ERR == signal(SIGCHLD, handler))
    {
        perror("建立信号与信号处理方式关联失败");
        return -1;
    }
    printf("建立信号与信号处理方式关联成功\n");
    // SIGCHLD: 是当子进程退出的时候, 内核会向父进程发送该信号
    // 2.创建子进程
    pid_t pid = fork();
    if(pid == -1)
    {
        perror("创建子进程失败");
    }
    else if(pid == 0)
    {
        //子进程
        printf("我是子进程, 我的pid是%d\n", getpid());
        printf("子进程延时5秒之后退出\n");
        sleep(5);
        exit(EXIT_SUCCESS);  //子进程正常退出
    }
    else if(pid > 0)
    {
        //父进程
        printf("我是父进程, 我的pid是%d\n", getpid());
        printf("父进程延时8秒之后退出\n");
        sleep(8);
        //父进程向自身发送指定的信号
        //SIGKILL: 杀死进程, 不能被捕捉和忽略
        if(0 != raise(SIGKILL))
        {
            printf("父进程向自身发送指定的信号失败\n");
        }
        //printf("父进程向自身发送指定的信号成功\n");
    }
    return 0;
}
