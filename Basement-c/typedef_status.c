#include <stdio.h>

typedef void (*MenuOperation)(void);

void File_Open(void)
{
    printf("打开文件\n");
}

void File_Close(void)
{
    printf("关闭文件\n");
}

void File_Delete(void)
{
    printf("删除文件\n");
}

MenuOperation menu[] = 
{
    File_Open,
    File_Close,
    File_Delete
};


int main()
{
    int menuchoice;
    printf("输入你想进行的操作\n");
    scanf("%d", &menuchoice);
    menu[menuchoice]();
    return 0;
}