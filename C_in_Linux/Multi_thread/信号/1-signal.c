// 使用signal函数建立信号与处理方式的关联
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

//信号处理方式的函数
void my_func(int sig)
{
    printf("捕捉到SIGINT信号\n");
}

int main(int argc, char const *argv[])
{
    // 第一个参数是用来指定信号的编号
    // 第二个参数是用来指定信号的处理方式  忽略
    // if (SIG_ERR == signal(SIGINT, SIG_IGN))
    // {
    //     perror("建立信号与处理方式关联失败");
    //     return -1;
    // }
    // printf("建立信号与处理方式关联成功\n");
    //指定信号的处理方式为默认处理方式
    // if(SIG_ERR == signal(SIGINT, SIG_DFL))
    // {
    //     perror("建立信号与处理方式关联失败");
    //     return -1;
    // }
    // printf("建立信号与处理方式关联成功\n");
    if(SIG_ERR == signal(SIGINT, my_func))
    {
        perror("建立信号与处理方式关联失败");
        return -1;
    }
    printf("建立信号与处理方式关联成功\n");
    while (1)
    {
        // 每隔一秒打印一次Hello World!
        printf("Hello World!\n");
        sleep(1);
    }
    return 0;
}
