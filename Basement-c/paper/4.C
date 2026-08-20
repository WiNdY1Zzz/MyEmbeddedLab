#include <stdio.h>
#define MIN(x, y) ((x) < (y) ? (x) : (y))

int add(int a, int b)
{
    return a + b;
}

int sub(int a, int b)
{
    return a - b;
}

int main()
{
    int (*fp1)(int, int) = add;
    int (*fp2)(int, int) = sub;
    int x, y;
    printf("请输入两个正数:\n");
    scanf("%d %d", &x, &y);
    
    printf("两数相加为:%d, 两数相减为:%d, 其中的最小值为:%d。", fp1(x, y), fp2(x, y), MIN(x, y));

    return 0;
}