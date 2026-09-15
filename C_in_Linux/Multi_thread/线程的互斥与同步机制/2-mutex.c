// 示例代码验证没有使用互斥锁来解决多线程的竞态条件问题
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

// 全局变量
int money = 1000;
pthread_mutex_t mutex;

// 线程1的入口函数
void *thread1(void *arg)
{
    int ret_unlock = 0;  //解锁操作的返回值
    while(1)
    {
        //获取互斥锁(加锁)
        int ret_lock = 0;
        if(0 != (ret_lock = pthread_mutex_lock(&mutex)))
        {
            fprintf(stderr, "获取线程1互斥锁失败, 错误信息: %s\n", strerror(ret_lock));
            //return -1;  //因为针对于线程的入口函数的返回值是void *类型
            return NULL;
        }
        printf("线程1获取互斥锁成功\n");
        if(money >= 100)
        {
            money -= 100;
            printf("线程1将money减为: %d\n", money);
        }
        else
        {
            printf("线程1发现money已经小于100, 不继续减了\n");
            //解锁操作
            if(0 != (ret_unlock = pthread_mutex_unlock(&mutex)))
            {
                fprintf(stderr, "1-线程1解锁互斥锁失败, 错误信息: %s\n", strerror(ret_unlock));
                return NULL;
            }
            printf("1-线程1解锁互斥锁成功\n");
            break;
        }
        //解锁操作
        if(0 != (ret_unlock = pthread_mutex_unlock(&mutex)))
            {
                fprintf(stderr, "2-线程1解锁互斥锁失败, 错误信息: %s\n", strerror(ret_unlock));
                return NULL;
            }
            printf("2-线程1解锁互斥锁成功\n");
        sleep(1); // 目的: 线程1和线程2进行交替执行
    }
    // 退出线程1
    pthread_exit(NULL);
    return NULL;
}

// 线程2的入口函数
void *thread2(void *arg)
{
    int ret_unlock = 0;
    while(1)
    {
        #if 1
        //获取互斥锁(加锁)
        //针对于互斥锁, 同一时刻只有一个线程可以获取到互斥锁(加锁)
        //如果此线程不能释放互斥锁, 那么其他的线程就需要进行阻塞等待
        //直到此线程释放了互斥锁, 那么其他的线程才可以获取并使用互斥锁
        int ret_lock = 0;
        if(0 != (ret_lock = pthread_mutex_lock(&mutex)))
        {
            fprintf(stderr, "获取线程2互斥锁失败, 错误信息: %s\n", strerror(ret_lock));
            //return -1;  //因为针对于线程的入口函数的返回值是void *类型
            return NULL;
        }
        printf("线程2获取互斥锁成功\n");
        #else
        //使用非阻塞方式进行获取互斥锁
        int ret_trylock = 0;
        if(0 != (ret_trylock = pthread_mutex_trylock(&mutex)))
        {
            fprintf(stderr, "使用非阻塞方式获取互斥锁失败, 错误信息: %s\n", strerror(ret_trylock));
            return NULL;
        }
        printf("线程2使用非阻塞方式获取互斥锁成功\n");
        #endif
        if(money >= 50)
        {
            money -= 50;
            printf("线程2将money减为: %d\n", money);
        }
        else
        {
            printf("线程2发现money已经小于50, 不继续减了\n");
            //解锁操作
            if(0 != (ret_unlock = pthread_mutex_unlock(&mutex)))
            {
                fprintf(stderr, "1-线程2解锁互斥锁失败, 错误信息: %s\n", strerror(ret_unlock));
                return NULL;
            }
            printf("1-线程2解锁互斥锁成功\n");
            break;
        }
        //解锁操作
        if(0 != (ret_unlock = pthread_mutex_unlock(&mutex)))
            {
                fprintf(stderr, "2-线程2解锁互斥锁失败, 错误信息: %s\n", strerror(ret_unlock));
                return NULL;
            }
            printf("2-线程2解锁互斥锁成功\n");
        sleep(1); // 目的: 线程1和线程2进行交替执行
    }
    // 退出线程2
    pthread_exit(NULL);
    return NULL;
}

int main(int argc, char const *argv[])
{
    #if 1
    //动态初始化互斥锁
    //动态初始化互斥锁会进行检查错误, 如果初始化失败, 会返回错误码
    //一般在实际使用的情况下, 我们使用动态初始化互斥锁的情况居多
    int ret_init = 0;
    if(0 != (ret_init = pthread_mutex_init(&mutex, NULL)))
    {
        fprintf(stderr, "动态初始化互斥锁失败, 错误信息: %s\n", strerror(ret_init));
        return -1;
    }
    printf("动态初始化互斥锁成功\n");
    #else
    //静态初始化互斥锁
    //静态初始化互斥锁不需要调用pthread_mutex_init函数
    //因为静态初始化互斥锁不会进行错误检查, 所以不需要检查返回值
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    #endif
    // 创建新线程1
    pthread_t tid1 = 0;
    int ret_create1 = 0;
    if (0 != (ret_create1 = pthread_create(&tid1, NULL, thread1, NULL)))
    {
        fprintf(stderr, "线程1创建失败, 错误信息: %s\n", strerror(ret_create1));
        return -1;
    }
    printf("线程1创建成功, 线程1的ID: %ld\n", tid1);
    // 创建新线程2
    pthread_t tid2 = 0;
    int ret_create2 = 0;
    if (0 != (ret_create2 = pthread_create(&tid2, NULL, thread2, NULL)))
    {
        fprintf(stderr, "线程2创建失败, 错误信息: %s\n", strerror(ret_create2));
        return -1;
    }
    printf("线程2创建成功, 线程2的ID: %ld\n", tid2);
    //等待线程1退出
    int ret_join1 = 0;
    if(0 != (ret_join1 = (pthread_join(tid1, NULL))))
    {
        fprintf(stderr, "线程1回收失败, 错误信息: %s\n", strerror(ret_join1));
        return -1;
    }
    printf("线程1回收成功\n");
    //等待线程2退出
    int ret_join2 = 0;
    if(0 != (ret_join2 = (pthread_join(tid2, NULL))))
    {
        fprintf(stderr, "线程2回收失败, 错误信息: %s\n", strerror(ret_join2));
        return -1;
    }
    printf("线程2回收成功\n");
    //销毁互斥锁
    int ret_destroy = 0;
    if(0 != (ret_destroy = pthread_mutex_destroy(&mutex)))
    {
        fprintf(stderr, "互斥锁销毁失败, 错误信息: %s\n", strerror(ret_destroy));
        return -1;
    }
    printf("互斥锁销毁成功\n");
    return 0;
}
