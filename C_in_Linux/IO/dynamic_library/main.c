#include <stdio.h>
#include "sub.h"

int main(int argc, char const *argv[])
{
    //减法函数的调用
    int ret = 0;
    ret = sub_int(10, 20);
    printf("ret = %d\n", ret);
    return 0;
}
