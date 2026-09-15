//示例代码验证线程为分离态线程
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//入口函数
void* thread1(void *arg)
{
    printf("我是子线程, 子线程的ID为: %ld\n", pthread_self());
    int *n = (int *)arg;
    //当子线程执行完成之后, 释放内存空间
    free(n);
    return NULL;
}

int main(int argc, char const *argv[])
{
    //1.申请内存空间
    //确保参数的生命周期要长于线程的生命周期
    //因为分离态线程执行完成之后, 线程会自动释放资源
    int *p = (int *)malloc(sizeof(int));
    if(!p)
    {
        perror("动态申请内存失败");
        return -1;
    }
    *p = 123;  //初始值
    //2.初始化线程的属性 pthread_attr_init函数
    pthread_attr_t attr;  //线程属性
    int ret_pthread_attr_init = 0;
    if(0 != (ret_pthread_attr_init = pthread_attr_init(&attr)))
    {
        fprintf(stderr, "初始化线程属性失败, 错误信息: %s\n", strerror(ret_pthread_attr_init));
        //释放内存空间
        free(p);
        return -1;
    }
    printf("线程属性初始化成功\n");
    //3.设置线程为分离态线程 函数: pthread_attr_setdetchstate
    int ret_pthread_attr_setdetachstate = 0;
    if(0 != (ret_pthread_attr_setdetachstate = 
                pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED)))
    {
        fprintf(stderr, "设置线程为分离态失败, 错误信息: %s\n", strerror(ret_pthread_attr_setdetachstate));
        //释放内存空间
        free(p);
        //销毁线程属性
        pthread_attr_destroy(&attr);
        return -1;
    }
    printf("线程属性设置为分离态成功\n");
    //4.创建新线程(状态: 分离态)
    pthread_t tid = 0;
    int ret_pthread_create = 0;
    if(0 != (ret_pthread_create = pthread_create(&tid, &attr, thread1, (void *)p)))
    {
        fprintf(stderr, "创建线程失败, 错误信息: %s\n", strerror(ret_pthread_create));
        //释放内存空间
        free(p);
        //销毁线程属性
        pthread_attr_destroy(&attr);
        return -1;
    }
    printf("创建线程成功, 线程ID为: %ld\n", tid);
    printf("我是主线程, 主线程的ID为: %ld\n", pthread_self());
    //5.销毁线程的属性(切记: 当不使用线程属性时, 要记得释放内存空间和销毁线程属性)
    //函数: pthread_attr_destroy函数
    int ret_pthread_attr_destroy = 0;
    if(0 != (ret_pthread_attr_destroy = pthread_attr_destroy(&attr)))
    {
        fprintf(stderr, "销毁线程属性失败, 错误信息: %s\n", strerror(ret_pthread_attr_destroy));
        //释放内存空间
        free(p);
        return -1;
    }
    printf("销毁线程属性成功\n");
    sleep(1);  //防止主线程提前退出
    return 0;
}
