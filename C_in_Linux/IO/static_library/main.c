#include <stdio.h>
#include "add.h"

int main(int argc, char const *argv[])
{
    //加法函数的调用
    int add_ret = add_int(1, 2);
    printf("add_ret = %d\n", add_ret);
    return 0;
}
