#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define

int Check_left(int arr[], int *cur);
int Check_right(int arr[], int *cur);

int Areana_Max(int *arr)
{   
    if(!arr)
    {
        printf("该数组为空数组，非法操作");
    }
    int *cur = &arr[0];
    int max_now = arr[0];
    int area, left, right;


    while(cur + 1 <= &arr[4])
    {
        left = Check_left(arr, cur);
        right = Check_right(arr, cur);
        area = *cur + left * (*cur) + right * (*cur);
        if(area >= max_now)
        max_now = area;
        cur = cur + 1;
    }

    return max_now;
}

int Check_left(int arr[], int *cur)
{
    int *p = cur;
    int Max_L = arr[0];
    int count_left = 0;
    if (cur == &arr[0])
    {
        return 0;
    }

    
    while(*cur <= *(cur - 1) && cur - 1 != &arr[0])
    {
        cur = cur - 1;
        count_left++;
    }
    if(*p <= Max_L && cur - 1 == &arr[0])
    {
        count_left++;
    }
    return count_left;
}

int Check_right(int arr[], int *cur)
{
    int *p = cur;
    int Max_r = arr[4];
    int count_right = 0;
    if (cur == &arr[4])
    {
        return 0;
    }

    
    while(*cur <= *(cur + 1) && cur + 1 != &arr[4])
    {
        cur = cur + 1;
        count_right++;
    }
    if(*p <= Max_r && cur + 1 == &arr[4])
    {
        count_right++;
    }
    return count_right;
}




int main(int argc, char *argv[])
{
    int arr[5] = {2, 1, 5, 6, 3};    
    
    printf("数组内最大的矩形面积为:%d\n", Areana_Max(arr));

    return 0;
}