// 模拟kill命令: kill -信号编号 进程号
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>

int main(int argc, char const *argv[])
{

    // 1.对输入参数的参数个数进行检查
    // 使用方式: ./3-kill -信号编号 进程号
    if (argc != 3 || argv[1][0] != '-')
    {
        printf("输入的参数个数有误\n");
        printf("usage: ./3-kill -信号编号 进程号\n");
        return -1;
    }
    // 2.将参数转换为整数(将字符串转换为整数)  atoi函数
    int signo = atoi(argv[1] + 1);
    // 信号一共有64个, 是从1信号开始的
    if (signo < 1 || signo > 64)
    {
        printf("输入的信号编号有误\n");
        return -1;
    }
    int pid = atoi(argv[2]);
    if (pid <= 0)
    {
        printf("输入的进程号有误\n");
        return -1;
    }
    // 3.使用kill函数发送信号
    // 第一个参数: 要发送信号的目标
    // 第二个参数要发送的信号的编号
    if (-1 == kill(pid, signo))
    {
        perror("使用kill函数发送信号失败");
        return -1;
    }
    printf("使用kill函数发送信号成功\n");
    // 4.打印结果
    printf("kill -%d %d\n", signo, pid);
    return 0;
}
