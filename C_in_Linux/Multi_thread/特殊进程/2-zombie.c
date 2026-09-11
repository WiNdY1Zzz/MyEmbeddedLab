//僵尸进程示例代码
//僵尸进程在进程终止之后, 父进程没有调用系统调用(wait/waitpid)来回收子进程的资源
//所以子进程的资源就会一直被占用, 那么这个时候子进程就会变成僵尸进程
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    // fork函数创建子进程
    pid_t pid = fork();
    if(pid == -1)
    {
        perror("创建子进程失败");
        return -1;
    }
    else if(pid == 0)
    {
        //子进程
        printf("我是子进程, 我的pid是%d\n", getpid());
        printf("子进程结束...\n");
    }
    else if(pid > 0)
    {
        //父进程
        //子进程终止之后, 父进程还在运行中
        //所以父进程不会回收子进程的资源, 父进程中也没有调用wait/waitpid来回收子进程的资源
        //那么当父进程结束之后, 子进程虽然前面已经结束, 但是子进程的资源不会被结束的父进程进行回收
        //而是由1号进行回收
        //僵尸进程会依赖于1号进程的"收养机制"
        //如何避免僵尸进程?
        //父进程调用wait/waitpid来回收子进程的资源
        // wait(NULL);
        // waitpid(-1, NULL, 0);
        printf("我是父进程, 我的pid是%d\n", getpid());
        sleep(40);
        printf("父进程结束...\n");
    }
    return 0;
}
