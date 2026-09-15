#include <stdio.h>
#include <pthread.h>
#include <string.h>

void* thread1 (void *arg)
{
    printf("我是子线程, 子线程的ID为: %ld\n", pthread_self());
    return NULL;
}

int main(int argc, char const *argv[])
{
    //创建新线程
    pthread_t tid = 0;
    int ret = 0;
    if(0 != (ret = pthread_create(&tid, NULL, thread1, NULL)))
    {
        fprintf(stderr, "错误信息为: %s\n", strerror(ret));
        return -1;
    }
    printf("创建线程成功, 线程ID为: %ld\n", tid);
    //等待子线程退出
    //目前不关注子线程的退出状态值
    int join_ret = 0;
    if(0 != (join_ret = pthread_join(tid, NULL)))
    {
        fprintf(stderr, "等待子线程退出失败: %s\n", strerror(join_ret));
        return -1;
    }
    printf("子线程退出成功, 并成功回收其资源\n");
    return 0;
}
