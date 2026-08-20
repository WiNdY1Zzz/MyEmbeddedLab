#include <stdio.h>

typedef void (*Callback)(int);

void process_data(int value, Callback cb)
{
    printf("处理数据:%d\n", value);
    cb(value);
}

void on_success(int result)
{
    printf("数据处理成功！结果为:%d\n", result);
}

int main()
{
    process_data(42, on_success);
    return 0;
}
