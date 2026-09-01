#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define

void QuickSort(int *arr, int low, int high)
{
    //递归时检测，如果low下标和high已经交汇甚至越过，说明数组内只有一个或者下标在数组边界
    if(low >= high)
    {
        return;
    }

    int i = low;
    int j = high;
    int pivot = arr[low];

    //以左边为基准，右边先动找数字“填坑”，然后反之，保证数据不被覆盖后遗漏
    while(i < j)
    {
        //右找大放左
        while(i < j && arr[j] >= pivot)
        {
            j--;
        }
        arr[i] = arr[j];

        //左找小放右
        while(i < j && arr[i] <= pivot)
        {
            i++;
        }
        arr[j] = arr[i];
    }

    arr[i] = pivot;

    QuickSort(arr, low, i - 1);  //放在左边的
    QuickSort(arr, i + 1, high); //放在右边的
}

void QuickSort_SwapPointer()
{

}

void partition()
{
    
}

int main(int argc, char *argv[])
{
    int arr[10] = {-10, 0, 10, -5, 5, -3, 3, -1, 1, -7};
    QuickSort(arr, 0, 9);
    for(int i = 0;i < 10;i++)
    {
        printf("%d ", arr[i]);
    }
    
    
    return 0;
}