#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

//线程入口函数
void* thread1(void *arg)
{
    printf("我是子线程...\n");
    return NULL;
}

int main(int argc, char const *argv[])
{
    //1.创建新线程
    pthread_t tid = 0;
    int ret_create = 0;
    if(0 != (ret_create = pthread_create(&tid, NULL, thread1, NULL)))
    {
        fprintf(stderr, "创建线程失败, 错误信息: %s\n", strerror(ret_create));
        return -1;
    }
    printf("创建线程成功, 线程ID为: %ld\n", tid);
    printf("我是主线程...\n");
    //2.将线程标记为分离态
    int ret_detach = 0;
    if(0 != (ret_detach = pthread_detach(tid)))
    {
        fprintf(stderr, "分离线程失败, 错误信息: %s\n", strerror(ret_detach));
        return -1;
    }
    printf("将线程标记为分离态成功\n");
    printf("主线程在5秒之后进行退出...\n");
    sleep(5);  //防止主线程提前退出
    printf("主线程退出成功\n");
    return 0;
}
