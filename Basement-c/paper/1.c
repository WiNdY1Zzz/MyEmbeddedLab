#include <stdio.h>

int main()
{
    int arr[6] = {5, 7, 9, 2, 11, 13};
    int *p = arr;

    for(int i = 0;i < 6;i++)
    {
        printf("%d ", *(p + i));
    }
    
    return 0;
}