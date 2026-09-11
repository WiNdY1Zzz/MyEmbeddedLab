// 这个进程用于往管道文件中写操作
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    // 1.对输入参数的参数个数进行检查
    if (argc != 2)
    {
        printf("输入的参数个数有误\n");
        printf("usage: ./a.out pathname\n");
        return -1;
    }
    //创建管道文件 mkfifo函数  也可以使用mkfifo命令进行创建管道文件
    //针对于创建管道文件是写在读端还是写在写端, 要根据实际情况来定
    int ret_mkfifo = mkfifo(argv[1], 0664);
    if(ret_mkfifo == -1)
    {
        perror("写端: 创建管道文件失败");
        return -1;
    }
    printf("写端: 创建管道文件成功\n");
    // 2.打开管道文件(以只写的方式打开文件)
    //不能使用/*|O_CREAT, 0664*/创建管道文件(创建的不是管道文件, 是一个普通文件)
    int fd = open(argv[1], O_WRONLY/* | O_CREAT, 0666 */);
    if(fd == -1)
    {
        perror("写端: 打开管道文件失败");
        return -1;
    }
    printf("写端: 打开管道文件成功\n");
    // 3.向管道文件中写数据
    char buf[] = "123456789";
    ssize_t ret_write = 0;
    if(-1 == (write(fd, buf, sizeof(buf))))
    {
        perror("写端: 向管道文件中写数据失败");
        return -1;
    }
    printf("写端: 向管道文件中写数据成功\n");
    // 4.关闭管道文件
    if(-1 == close(fd))
    {
        perror("写端: 关闭管道文件失败");
        return -1;
    }
    printf("写端: 关闭管道文件成功\n");
    // 5.使用unlink函数删除管道文件(在写操作中不进行删除管道文件)
    // 一般同一个管道文件只删除一次
    // 一般是在读操作中进行删除管道文件, 因为读操作是最后从管道文件中进行读取数据
    // 再次进行关闭管道文件
        return 0;
}
