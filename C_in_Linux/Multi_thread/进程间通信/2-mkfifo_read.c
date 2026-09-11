//这个进程用于从管道文件中进行读操作
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    //1.对输入参数的参数个数进行检查
    if (argc != 2)
    {
        printf("输入的参数个数有误\n");
        printf("usage: ./a.out pathname\n");
        return -1;
    }
    //2.打开管道文件(以只读的方式打开管道文件)
    int fd = open(argv[1], O_RDONLY);
    if(fd == -1)
    {
        perror("读端: 打开管道文件失败");
        return -1;
    }
    printf("读端: 打开管道文件成功\n");
    //3.向管道文件中读取数据
    char buf_data[BUFSIZ] = {0};
    ssize_t ret_read = 0;
    if(-1 == (ret_read = read(fd, buf_data, sizeof(buf_data))))
    {
        perror("读端: 从管道文件中读取数据失败");
        return -1;
    }
    printf("读端: 从管道文件中读取数据成功\n");
    printf("读端: 从管道文件中读取的数据是: %s\n", buf_data);
    //4.关闭管道文件
    if(-1 == close(fd))
    {
        perror("读端: 关闭管道文件失败");
        return -1;
    }
    printf("读端: 关闭管道文件成功\n");
    //5.使用unlink函数删除管道文件
    //针对于同一管道文件, 只需要使用一次unlink函数即可
    if(-1 == unlink(argv[1]))
    {
        perror("读端: 删除管道文件失败");
        return -1;
    }
    printf("读端: 删除管道文件成功\n");
    return 0;
}