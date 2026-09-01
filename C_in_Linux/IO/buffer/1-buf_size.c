#include <stdio.h>

int main(int argc, char const *argv[])
{
    //行缓冲区默认用于终端设备
    //求行缓存区的大小
    //注意事项:程序一开始运行，并没有将数据写入到缓冲区中
    //所以没有给行缓冲区分配实际的内存空间
    //所以一开始行缓冲区的大小为0
    printf("行缓冲区的大小:%ld\n", 
    stdout->_IO_buf_end - stdout->_IO_buf_base);
    printf("Hello\n");
    //注意事项:当程序运行到printf("Hello\n");时
    //会将数据写入到行缓冲区中
    //所以行缓冲区的大小为1024
    printf("行缓冲区的大小:%ld\n", 
    stdout->_IO_buf_end - stdout->_IO_buf_base); //1024
    //全缓冲是默认用于文件设备
    //求全缓冲区的大小
    FILE *fp = fopen("1.txt", "r");
    if(!fp)
    {
        perror("文件打开失败");
        return -1;
    }
    printf("文件打开成功\n");
    //从文件中读取一个字符
    int ch = 0;
    ch = fgetc(fp);
    printf("ch:%c\n", ch);
    //求全缓冲区的大小
    printf("全缓冲区的大小:%ld\n", 
    fp->_IO_buf_end - fp->_IO_buf_base); //0
    //关闭文件
    fclose(fp);
    //求无缓冲区的大小
    printf("无缓冲区的大小：%ld\n", 
    stderr->_IO_buf_end - stderr->_IO_buf_base);
    return 0;
}
