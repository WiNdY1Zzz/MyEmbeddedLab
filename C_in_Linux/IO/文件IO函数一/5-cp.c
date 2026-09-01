#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
    // 1.对输入参数的参数个数进行检查 argc
    if (argc != 3)
    {
        printf("输入的参数个数有误\n");
        printf("uasge: ./a.out src_file dst_file\n");
        return -1;
    }
    // 2.以只读的方式打开源文件 以只写的方式打开目标文件 open
    // argv[1] 源文件的路径
    // argv[2] 目标文件的路径
    // O_RDONLY如果文件不存在则会进行报错，打开文件就会失败
    int fd_src = open(argv[1], O_RDONLY);
    if (fd_src == -1)
    {
        perror("源文件打开失败");
        return -1;
    }
    printf("源文件打开成功, fd_src = %d\n", fd_src);
    // 如果文件不存在则会进行报错，打开文件失败
    // 以只写的方式打开文件，如果文件不存在则创建新文件
    // 如果文件存在则将文件中原有的内容进行清空操作
    int fd_dst = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);

    if (fd_dst == -1)
    {
        perror("目标文件打开失败");
        return -1;
    }
    printf("目标文件打开成功, fd_dst = %d\n", fd_dst);
    // 3.循环读取和写入 read 和 write
    char buf[1024] = {0};
    ssize_t ret_read = 0;
    ssize_t ret_write = 0;
    while((ret_read = read(fd_src, buf, sizeof(buf))) > 0)
    {
        //循环写入操作
        ret_write = write(fd_dst, buf, ret_read);
        if(ret_write == -1)
        {
            perror("写入目标文件失败");
            return -1;
        }
        //检查写入的字节数与读取的字节数是否一致
        if(ret_read != ret_write)
        {
            printf("写入的字节数与读取的字节数不一致\n");
            return -1;
        }
    }
    // 4.关闭文件 close
    close(fd_src);
    close(fd_dst);
    return 0;
}
