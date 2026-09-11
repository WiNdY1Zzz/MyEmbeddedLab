#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    // 创建子进程
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("创建子进程失败");
        return -1;
    }
    else if (pid == 0)
    {
        // 子进程
        while (1)
        {
            printf("我是子进程\n");
            sleep(1);
            exit(EXIT_SUCCESS); // 子进程正常退出
            // exit(1000);  //1000 & 0377
        }
    }
    else if (pid > 0)
    {
        // 父进程
        while (1)
        {
            printf("我是父进程\n");
            sleep(1);
            // 等待子进程拖出
            // 第一个参数用于指定要等待的子进程
            // 第二个参数用于指定子进程的退出状态值的存放空间
            // NULL代表不关注子进程的退出状态值
            // 第三个参数用于指定等待的方式 0: 表示是阻塞等待方式
            //  pid_t waitpid_ret = waitpid(-1, NULL, 0);
            // 关注子进程的退出状态值
            int st = 0; // 保存子进程的状态值
            pid_t waitpid_ret = waitpid(-1, &st, 0);
            if (waitpid_ret == -1)
            {
                perror("调用进程中没有子进程或者是调用出错\n");
                return -1;
            }
            else if (waitpid_ret == pid)
            {
                printf("父进程成功等待到了子进程的退出\n");
                // 获取子进程的退出状态值
                if (WIFEXITED(st)) // 正常退出
                {
                    printf("子进程的退出状态值为%d\n", WEXITSTATUS(st));
                }
                else if (WIFSIGNALED(st)) // 信号导致退出
                {
                    printf("子进程的退出状态值为%d\n", WTERMSIG(st));
                }
            }
        }
    }
    return 0;
}
