// 关注父子进程调用顺序
//父子进程是没有调用顺序的, 它们是根据时间片轮转来进行的上下文切换
//CPU轮到哪个进程, 就哪个进程先执行
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    pid_t pid = fork();
    if (pid > 0)
    {
        while (1)
        {
            printf("我是父进程\n");
            sleep(1);
        }
    }
    else if (pid == 0)
    {
        while (1)
        {
            printf("我是子进程\n");
            sleep(1);
        }
    }
    else if (pid == -1)
    {
        perror("创建子进程失败");
        return -1;
    }
    return 0;
}
