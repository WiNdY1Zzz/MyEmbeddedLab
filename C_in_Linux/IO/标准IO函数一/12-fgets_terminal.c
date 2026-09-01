#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    //从终端上读取一组字符串
    char buf[1024] = {0};
    fgets(buf, sizeof(buf), stdin);
    printf("从终端上读取到的字符串为：%s", buf);
    printf("从终端上读取到的字符串的大小为：%ld\n", strlen(buf));
    return 0;
}
