#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    // 1.对输入参数的参数个数进行检查
    if (argc != 2)
    {
        printf("输入参数的参数个数有误!\n");
        printf("usage: ./a.out pathname\n");
        return -1;
    }
    // 2.创建管道文件
    // if (-1 == mkfifo(argv[1], 0664))
    // {
    //     perror("写端: 创建管道文件失败");
    //     return -1;
    // }
    // printf("写端: 创建管道文件成功\n");
    // 3.打开管道文件
    // 以只写的方式打开文件(如果后面进行非阻塞测试, 需要给一个非阻塞的标志, O_NONBLOCK)
    int fd = 0;
    if (-1 == (fd = open(argv[1], O_WRONLY | O_NONBLOCK)))
    {
        perror("写端: 打开管道文件失败");
        return -1;
    }
    printf("写端: 打开管道文件成功\n");
    // 4.向管道文件中进行写入数据
    // 从终端上获取到的数据写入到管道文件中
    char buf[1024] = {0};
    ssize_t ret = 0;
    while (1)
    {
        printf("请输入要写入管道文件中的数据:\n");
        scanf("%s", buf);
        if (-1 == (ret = write(fd, buf, sizeof(buf))))
        {
            perror("写端: 写入管道文件失败");
            close(fd);
            return -1;
        }
        printf("写入的数据:%s\n", buf);
    }
    // 5.关闭管道文件
    if (-1 == close(fd))
    {
        perror("写端: 关闭管道文件失败");
        return -1;
    }
    printf("写端: 关闭管道文件成功");
    // 说明: 在写端不进行删除管道文件, 等读端读完文件中的内容之后
    // 由读端进行删除管道文件
    return 0;
}
