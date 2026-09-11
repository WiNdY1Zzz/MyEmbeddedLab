//此示例代码要给线程入口函数进行传递参数
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

//线程入口函数
void* pthread_start(void *arg)
{
    printf("我是子线程\n");
    #if 0
    //接收传递过来的参数--栈区
    int *val = (int *)arg;
    printf("传递过来的参数为: %d\n", *val);
    #else
    //接收传递过来的参数--堆区
    int *val = (int *)arg;
    printf("传递过来的参数为: %d\n", *val);
    //释放堆区空间
    free(val);
    #endif
    return NULL;
}

int main(int argc, char const *argv[])
{
    //创建新线程
    pthread_t tid = 0;  //线程ID
    #if 0
    //第一种方式: 栈区给入口函数传递参数
    //弊端: 如果主线程在子线程之前进行结束, 那么value变量就会被销毁
    //所以当子线程访问此变量, 就会出现访问的是一个无效的地址
    //针对于栈区给入口函数传递参数是不安全的, 此时考虑使用堆区进行传递参数
    int value = 100;
    #else
    //第二种方式: 堆区给入口函数传递参数
    //堆区开辟空间
    //弊端: 需要手动管理, 如果忘记释放, 就会导致内存泄漏
    int *value = (int *)malloc(sizeof(int));
    if(!value)
    {
        printf("堆区开辟空间失败\n");
        return -1;
    }
    printf("堆区开辟空间成功\n");
    *value = 123;
    #endif
    #if 0
    int ret = 0;
    if(0 != (ret = pthread_create(&tid, NULL, pthread_start, (void *)&value)))
    {
        fprintf(stderr, "线程创建失败, 错误信息:%s\n", strerror(ret));
        return -1;
    }
    printf("线程创建成功, 线程ID: %ld\n", tid);
    #else
    int ret = 0;
    if(0 != (ret = pthread_create(&tid, NULL, pthread_start, (void *)value)))
    {
        fprintf(stderr, "线程创建失败, 错误信息:%s\n", strerror(ret));
        return -1;
    }
    printf("线程创建成功, 线程ID: %ld\n", tid);
    #endif
    sleep(3);
    return 0;
}
