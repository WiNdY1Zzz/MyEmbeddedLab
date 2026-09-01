#include <stdio.h>

int main(int argc, char const *argv[])
{
    //对输入参数的参数个数进行检查
    if(argc != 3)
    {
        printf("输入的参数个数有误\n");
        printf("usage: ./a.out filename1 filename2\n");
        return -1;
    }
    //打开文件 以只读的方式打开源文件
    FILE *fp_src = fopen(argv[1], "rb");
    if(!fp_src)
    {
        perror("打开源文件失败");
        return -1;
    }
    printf("源文件打开成功\n");
    //打开文件 以只写的方式打开目标文件
    FILE *fp_dst = fopen(argv[2], "wb");
    if(!fp_dst)
    {
        perror("打开目标文件失败");
        return -1;
    }
    printf("目标文件打开成功\n");
    //从源文件中读取数据，将读取到的数据写到目标文件中
    //没有读取文件的末尾和没有发生错误则循环从文件中读取数据
    char buf[BUFSIZ] = {0};
    size_t fread_ret = 0;
    while(!(feof(fp_src) || ferror(fp_src)))
    {
        //从源文件中读取数据
        fread_ret =  fread(buf, 1, sizeof(buf), fp_src);
        //将读取的数据写入到目标文件中
        fwrite(buf, 1, fread_ret, fp_dst);
    }
    //关闭文件
    fclose(fp_src);
    fclose(fp_dst);
    return 0;
}
