#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, const char *argv[])
{
    //第一个参数：如果不写路径默认是当前路径下的文件
    //第二个参数：打开文件的方式
    //以只读的方式打开文件，如果文件不存在，则创建新文件
    //一旦创建新文件，需要使用open函数的第三个参数，默认权限0666
    //如果文件不存在则创建文件，如果文件存在则报错
    int fd = 0; //文件描述符，从3开始
    if((fd = open("test.c", O_RDONLY | O_CREAT | O_EXCL, 0666)) == -1)
    {
        //如果文件打开失败，则错误码会被重新的设置 errno
        if(errno == EEXIST)
        {
            printf("文件已存在\n");
        }
        perror("文件打开失败");
        return -1;
    }
    printf("打开文件成功\n");
    printf("文件描述符为:%d\n", fd);
    //后续在使用open函数的时候要关闭文件(关闭文件描述符)
    //关闭文件close
    //如果关闭文件成功，那么返回值为0
    //如果关闭文件失败，那么返回值为-1
    int ret = 0;
    if((ret = close(fd)) == -1)
    {
        perror("关闭文件失败");
        return -1;
    }
    printf("关闭文件成功, ret = %d\n", ret);
    return 0;
}