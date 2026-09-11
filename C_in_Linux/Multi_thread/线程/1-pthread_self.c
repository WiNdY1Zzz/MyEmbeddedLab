//获取线程标识: 获取调用线程的线程ID 使用函数pthread_self()
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

//函数: 线程的入口函数
void *thread1(void *arg)
{
    printf("我是子线程, 子线程的ID为: %ld\n", pthread_self());
    return NULL;
}

int main(int argc, char const *argv[])
{
    //创建新线程
    pthread_t tid = 0;
    int ret = 0;
    if(0 != (ret =pthread_create(&tid, NULL, thread1, NULL)))
    {
        fprintf(stderr, "错误信息为: %s\n", strerror(ret));
        return -1;
    }
    printf("创建线程成功, 线程ID为: %ld\n", tid);
    printf("我是主线程, 主线程的ID为: %ld\n", pthread_self());
    sleep(3);
    return 0;
}
