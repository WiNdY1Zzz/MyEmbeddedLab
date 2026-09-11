// 测试无名管道中是无法使用lseek函数的, 如果使用则调用失败, 返回-1
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char const *argv[])
{
    // 1.创建无名管道
    //针对于单进程也可以创建无名管道
    //但是针对于这样的操作, 是没有任何意义的
    int fd[2] = {0};
    int pipe_ret = pipe(fd);
    if (pipe_ret == -1)
    {
        perror("创建无名管道失败");
        return -1;
    }
    printf("创建无名管道成功");
    // 2.关闭读端
    int close_ret = close(fd[0]);
    if (close_ret == -1)
    {
        perror("关闭读端失败");
        return -1;
    }
    printf("关闭读端成功\n");
    // 3.使用lseek函数
    //第一个参数: 文件描述符
    //第二个参数: 偏移量(0: 不偏移, >0: 向后偏移, <0: 向前偏移)
    //第三个参数: 从哪里开始偏移  SEEK_SET: 从文件开始进行偏移
    //SEEK_CUR: 从当前位置开始偏移
    //SEEK_END: 从文件末尾开始偏移
    //lseek(fd[1], 0, SEEK_SET): 从文件开始位置偏移0个字节
    //返回值: 成功: 偏移后的文件位置  失败: -1
    //说明: 在无名管道中使用lseek函数会报错
    //错误信息为: 使用lseek函数失败: Illegal seek(非法查找)
    //无名管道必须遵循先进先出的原则
    off_t lseek_ret = lseek(fd[1], 0, SEEK_SET);
    if(lseek_ret == -1)
    {
        perror("使用lseek函数失败");
        return -1;
    }
    printf("使用lseek函数成功\n");
    //4.关闭写端
    int close_ret_1 = close(fd[1]);
    {
        perror("关闭写端失败");
        return -1;
    }
    printf("关闭写端成功\n");
    return 0;
}
