#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    //每隔1秒打印1次Hello World!
    while(1)
    {
        printf("Hello World!\n");
        sleep(1);
    }
    return 0;
}
