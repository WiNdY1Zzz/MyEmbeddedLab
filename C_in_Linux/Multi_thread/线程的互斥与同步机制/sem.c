//使用无名信号量
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

sem_t sem1, sem2;  //全局无名信号量
pthread_t tid1, tid2;  //全局线程ID
int count = 0;  //统计生产数据的次数的全局变量

//线程1: 生产者线程
void* thread1(void *arg)
{
    while(1)
    {
    /*
        生产者线程流程: 循环执行
        1.申请资源(申请信号量2)
        2.生产数据(修改共享资源)
        3.释放资源(释放信号量1)(告知消费者数据已经生产完成)
    */
        //1.申请资源
        int ret_sem_wait = 0;
        if(-1 == (ret_sem_wait = sem_wait(&sem2)))
        {
            perror("生产者线程申请信号量2资源失败");
            return NULL;
        }
        printf("生产者线程申请信号量2资源成功\n");
        //2.生产数据(修改共享资源)
        printf("生产者线程正在生产数据, 3秒之后生产完成...\n");
        sleep(3);
        count++;
        printf("生产者线程生产数据完成, 当前资源的数量:%d\n", count);
        //3.释放资源(释放信号量1)(告知消费者线程数据已经生产完成)
        int ret_sem_post = 0;
        if(-1 == (ret_sem_post = sem_post(&sem1)))
        {
            perror("生产者线程释放信号量1资源失败");
            return NULL;
        }
        printf("生产者线程释放信号量1资源成功\n");
    }
    return NULL;
}

//线程2: 消费者线程
void* thread2(void *arg)
{
    while(1)
    {
    /*
        消费者线程的流程: 循环执行
        1.申请资源(申请信号量1)
        2.消费数据
        3.释放资源(释放信号量2)(告知生产者线程数据已经被消费)
    */
        //1.申请资源
        int ret_sem_wait = 0;
        if(-1 == (ret_sem_wait = sem_wait(&sem1)))
        {
            perror("消费者线程申请信号量1失败");
            return NULL;
        }
        printf("消费者线程申请信号量1成功\n");
        //2.消费数据
        printf("消费者线程正在消费数据, 3秒之后消费完成...\n");
        sleep(3);
        count--;
        printf("消费者线程消费完成, 当前资源的数量:%d\n", count);
        //3.释放资源
        int ret_sem_post = 0;
        if(-1 == (ret_sem_post = sem_post(&sem2)))
        {
            perror("消费者线程释放信号量2资源失败");
            return NULL;
        }
        printf("消费者线程释放信号量2资源成功\n");
    }
    return NULL;
}

int main(int argc, char const *argv[])
{
    //初始化无名信号量1
    //针对于此初始化的无名信号量, 是用于进程内线程间的同步
    //设置的无名信号量的初始值为0, 说明目前没有可用资源
    int ret_init1 = 0;
    if(-1 == (ret_init1 = sem_init(&sem1, 0, 0)))
    {
        perror("初始化无名信号量1失败");
        return -1;
    }
    printf("初始化无名信号量1成功\n");
    //初始化无名信号量2
    //针对于此初始化无名信号量2, 是用于进程内线程间同步
    //信号量的初计数是1, 说明有1个可用资源
    int ret_init2 = 0;
    if(-1 == (ret_init2 = sem_init(&sem2, 0, 1)))
    {
        perror("初始化无名信号量2失败");
        return -1;
    }
    printf("初始化无名信号量2成功\n");
    //创建线程1
    int ret_pthread_create1 = 0;
    if(0 != (ret_pthread_create1 = pthread_create(&tid1, NULL, thread1, NULL)))
    {
        fprintf(stderr, "创建线程1失败, 错误信息: %s\n", strerror(ret_pthread_create1));
        return -1;
    }
    printf("创建线程1成功\n");
    //创建线程2
    int ret_pthread_create2 = 0;
    if(0 != (ret_pthread_create2 = pthread_create(&tid2, NULL, thread2, NULL)))
    {
        fprintf(stderr, "创建线程2失败, 错误信息: %s\n", strerror(ret_pthread_create2));
        return -1;
    }
    printf("创建线程2成功\n");
    //等待线程1和线程2的结束
    int ret_pthread_join1 = 0;
    if(0 != (ret_pthread_join1 = pthread_join(tid1, NULL)))
    {
        fprintf(stderr, "线程1等待失败, 错误信息: %s\n", strerror(ret_pthread_join1));
        return -1;
    }
    printf("等待线程1, 并成功回收线程1的资源\n");
    int ret_pthread_join2 = 0;
    if(0 != (ret_pthread_join2 = pthread_join(tid2, NULL)))
    {
        fprintf(stderr, "线程2等待失败, 错误信息: %s\n", strerror(ret_pthread_join2));
        return -1;
    }
    printf("等待线程2, 并成功回收线程2的资源\n");
    //销毁无名信号量
    int ret_sem_destroy1 = 0;
    if(-1 == (ret_sem_destroy1 = sem_destroy(&sem1)))
    {
        perror("销毁无名信号量1失败");
        return -1;
    }
    printf("销毁无名信号量1成功\n");
    int ret_sem_destroy2 = 0;
    if(-1 == (ret_sem_destroy2 = sem_destroy(&sem2)))
    {
        perror("销毁无名信号量2失败");
        return -1;
    }
    printf("销毁无名信号量2成功\n");
    return 0;
}
