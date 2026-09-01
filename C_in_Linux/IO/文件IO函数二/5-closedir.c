#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

int main(int argc, char const *argv[])
{
    //对输入参数的参数个数进行判断
    if(argc != 2)
    {
        printf("输入的参数个数有误\n");
        printf("usage: ./a.out 目录名\n");
        return -1;
    }
    // 打开目录 如果打开文件，则会进行报错
    DIR *opendir_dir = opendir(argv[1]);
    if(!opendir_dir)
    {
        perror("打开目录失败");
        return -1;
    }
    printf("打开目录成功\n");
    //关闭目录
    int closedir_dir = closedir(opendir_dir);
    if(closedir_dir == -1)
    {
        perror("关闭目录失败");
        return -1;
    }
    printf("关闭目录成功\n");
    return 0;
}
