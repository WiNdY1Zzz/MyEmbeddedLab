#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    // 以读写和追加的方式打开文件
    int fd = open("demo.c", O_RDWR | O_APPEND | O_CREAT, 0666);
    if (fd == -1)
    {
        perror("打开文件失败");
        return -1;
    }
    printf("打开文件成功, fd = %d\n", fd);
    // 进行文件的定位操作
    // >0说明向后偏移
    // SEEK_SET说明从文件开头进行偏移
    off_t offset = lseek(fd, 2, SEEK_SET);
    if (offset == -1)
    {
        perror("文件定位失败");
        return -1;
    }
    // offset：从文件开头计算出来的结果偏移量(单位：字节)
    printf("文件定位成功, off_set = %ld\n", offset);
    // 从文件中进行读取数据
    //  char buf[1024] = {0};
    //  ssize_t ret_read = read(fd, buf, sizeof(buf));
    //  if(ret_read == -1)
    //  {
    //      perror("读取数据失败");
    //      return -1;
    //  }
    //  printf("读取数据成功, buf = %s\n", buf);
    // 往文件中写入数据
    // 数据会追加到文件的末尾，虽然对光标的位置进行了重新的定位
    // 但是如果以追加的方式打开文件的话，写入数据时，会从文件的末尾开始写入数据
    char *str = "hello world";
    ssize_t ret_write = write(fd, str, strlen(str));
    if (ret_write == -1)
    {
        perror("写入数据失败");
        return -1;
    }
    printf("写入数据成功\n");
    // 关闭文件
    close(fd);
    return 0;
}
