//测试主线程和子线程的执行顺序
/*
    关于主线程和子线程它们的执行没有先后顺序
    也是CPU进行时间片轮转策略, 谁先抢到时间片, 谁就先执行
*/
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

//线程入口函数
void* pthread_start(void *arg)
{
    while(1)
    {
        printf("我是子线程\n");
        sleep(1);
    }
    return NULL;
}

int main(int argc, char const *argv[])
{
    //创建新线程
    pthread_t tid = 0;
    int ret = 0;
    if(0 != (ret =pthread_create(&tid, NULL, pthread_start, NULL)))
    {
        fprintf(stderr, "线程创建失败, 错误信息: %s\n", strerror(ret));
        return -1;
    }
    printf("线程创建成功, 线程ID: %ld\n", tid);
    while(1)
    {
        printf("我是主线程\n");
        sleep(1);
    }
    return 0;
}
