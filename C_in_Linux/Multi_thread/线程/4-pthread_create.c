// 验证主线程和子线程是不是使用同一块内存空间
// 线程特点: 一个进程中的多线程共享进程的内存空间
//因为一个进程中的多线程共享进程的内存空间, 所以子线程和主线程访问的全局变量
//打印的地址是相同的, 但是如果访问的是局部变量, 那么打印的地址就会不同
//因为针对于局部变量, 每个线程都有自己的栈区, 所以局部变量的地址是不同的
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

int num = 100; // 全局变量

// 线程的入口函数
void *thread1(void *arg)
{
    while (1)
    {
        printf("我是子线程, num = %d, &num = %p\n", num, &num);
        sleep(1);
    }
    return NULL;
}

int main(int argc, char const *argv[])
{
    // 创建新线程
    pthread_t tid = 0;
    int ret = 0;
    if (0 != (ret = pthread_create(&tid, NULL, thread1, NULL)))
    {
        fprintf(stderr, "线程创建失败, 错误信息: %s\n", strerror(ret));
        return -1;
    }
    printf("线程创建成功, 线程ID: %ld\n", tid);
    while (1)
    {
        printf("我是主线程, num = %d, &num = %p\n", num, &num);
        sleep(1);
    }
    sleep(3);
    return 0;
}
