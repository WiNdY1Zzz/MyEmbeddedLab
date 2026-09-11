#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    //1.对输入参数的参数个数进行检查
    if (argc != 2)
    {
        printf("输入参数的参数个数有误!\n");
        printf("usage: ./a.out pathname\n");
        return -1;
    }
    // 2.创建管道文件
    if (-1 == mkfifo(argv[1], 0664))
    {
        perror("读端: 创建管道文件失败");
        return -1;
    }
    printf("读端: 创建管道文件成功\n");
    //3.打开管道文件
    int fd = 0;
    if(-1 == (fd = open(argv[1], O_RDONLY | O_NONBLOCK)))
    {
        perror("读端: 打开管道文件失败");
        return -1;
    }
    printf("读端: 打开管道文件成功");
    //4.从管道文件中读取数据
    char buf[10] = {0};
    ssize_t ret = 0;
    while(1)
    {
        if(-1 == (ret = read(fd, buf, sizeof(buf) - 1)))
        {
            perror("读端: 从管道文件中读取数据失败");
            return -1;
        }
        printf("从管道文件中读取到的数据为:%s\n", buf);
        //手动填充字符串结束符\0
        buf[ret] = '\0';
        //如果管道中没有数据了, 则退出循环
        if(ret == 0)
        {
            break;
        }
    }
    //5.关闭管道文件
    if(-1 == close(fd))
    {
        perror("读端: 关闭管道文件失败");
        return -1;
    }
    printf("读端: 关闭管道文件成功\n");
    //6.删除管道文件
    if(-1 == unlink(argv[1]))
    {
        perror("读端: 删除管道文件失败");
        return -1;
    }
    printf("读端: 删除管道文件成功\n");
    return 0;
}
