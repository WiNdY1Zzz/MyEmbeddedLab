// 多进程实现文件分块拷贝
// 父进程: 拷贝源文件的前半部分
// 子进程: 拷贝源文件的后半部分
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

// 函数: 获取源文件的大小
int get_srcfile_size(const char *srcfile)
{
    // 以只读的方式打开源文件
    int fd = open(srcfile, O_RDONLY);
    if (fd == -1)
    {
        perror("打开源文件失败");
        return -1;
    }
    printf("打开源文件成功\n");
    // 获取源文件的大小 lseek
    off_t s = lseek(fd, 0, SEEK_END);
    if (s == -1)
    {
        perror("获取源文件大小失败");
        return -1;
    }
    printf("获取源文件大小成功, s = %ld\n", s);
    // 关闭文件
    close(fd);
    // 将源文件的大小进行返回
    return s;
}

//函数: 父子进程进行文件拷贝
/*参数说明: 
  srcfile: 源文件的路径
  destfile: 目标文件的路径
  offset: 拷贝的起始位置
  size: 拷贝的大小
*/
int file_copy(const char *srcfile, const char *destfile, off_t offset, off_t size)
{
    //1.读的方式打开源文件
    int src_fd = open(src_fd, O_RDONLY);
    if(src_fd == -1)
    {
        perror("打开源文件失败");
        return -1;
    }
    printf("打开源文件成功, src_fd = %d\n", src_fd);
    //2.以只写的方式打开目标文件
    //如果目标文件不存在则创建新的文件
    //如果目标文件存在则将原有的内容进行清空
    int des_fd = open(des_fd, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if(des_fd == -1)
    {
        perror("打开目标文件失败");
        return -1;
    }
    printf("打开目标文件成功, des_fd = %d\n", des_fd);
    //3.修改光标的位置(父子进程拷贝的源文件中的内容是不同的)
    off_t father_s = lseek(src_fd, offset, SEEK_SET);  //父进程
    off_t child_s  = lseek(des_fd, offset, SEEK_SET);  //子进程
    //4.循环拷贝工作
    char buf_read[BUFSIZ] = {0};
    ssize_t read_size = 0;  //读取到的字节数
    ssize_t size = 0;  //统计总字节数
    while((read_size = read(src_fd, buf_read, sizeof(buf_read))) > 0)
    {
        //统计读取到的总字节数
        size += read_size;
        //写入到目标文件中
        write(des_fd, buf_read, read_size);
    }
    //循环从源文件中读取数据, 写入到目标文件中
    //注意: 拷贝读取到的内容要比需要拷贝的内容的字节数要多
    //这个时候就需要进行特殊的处理
    //5.关闭文件
}

int main(int argc, char const *argv[])
{
    // 1.对输入参数的参数个数进行判断
    if (argc != 3)
    {
        printf("输入的参数个数有误\n");
        printf("usage: ./a.out srcfile destfile \n");
        return -1;
    }
    // 2.获取源文件的大小  -- 函数
    int srcfile_size = get_srcfile_size(argv[1]);
    // printf("源文件的大小为: %d\n", srcfile_size);
    if (srcfile_size < 0)
    {
        perror("获取源文件大小失败");
        return -1;
    }
    // 3.父子进程拷贝源文件  -- 函数
    // 3.1 使用fork函数创建子进程
    pid_t pid = fork();
    if (pid > 0)
    {
        // 父进程
        // 父进程拷贝源文件的前半部分
        file_copy(argv[1], argv[2], 0, srcfile_size/2);
    }
    else if (pid == 0)
    {
        // 子进程
        // 子进程拷贝源文件的后半部分
        file_copy(argv[1], argv[2], srcfile_size/2, srcfile_size - srcfile_size/2);
    }
    // 3.2 父子进程拷贝文件
    // 父进程拷贝源文件的前半部分
    // 子进程拷贝源文件的后半部分
    return 0;
}
