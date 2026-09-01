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
    //针对于当前代码是为了测试opendir函数，所以不能关闭目录
    //但是针对于整个程序, 应该是打开目录, 使用目录, 关闭目录
    return 0;
}
