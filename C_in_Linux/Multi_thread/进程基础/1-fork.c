#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    // 不关注fork函数的返回值
    // fork();  //创建子进程
    // fork();  //创建子进程
    // fork();  //创建子进程
    //等价于上面三次单独的调用fork函数
    //fork函数的特点: 一次调用，两次返回
    for(int i = 0;i < 3;i++)
    {
        fork();
    }
    sleep(100);
    return 0;
}
