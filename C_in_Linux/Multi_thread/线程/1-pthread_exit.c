#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

// 线程的入口函数
void *thread_1(void *arg)
{
    printf("我是子线程\n");
    printf("我是子线程, 我要退出了...\n");
    pthread_exit(NULL); // 终止当前线程  子线程
    //在pthread_exit函数之后, 线程的代码就不会再执行了
    return NULL;
}

int main(int argc, char const *argv[])
{
    // 创建新线程
    pthread_t tid = 0;
    int ret = 0;
    if (0 != (ret = pthread_create(&tid, NULL, thread_1, NULL)))
    {
        fprintf(stderr, "创建线程失败, 失败信息: %s\n", strerror(ret));
        return -1;
    }
    printf("创建线程成功, 线程ID: %ld\n", tid);
    printf("我是主线程\n");
    sleep(3); // 等待子线程的执行结束

    return 0;
}
