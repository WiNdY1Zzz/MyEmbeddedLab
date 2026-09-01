#include <stdio.h>

int main(int argc, char const *argv[])
{
    //求stdin、stdout、stderr的文件描述符
    //_fileno是FILE对象中记录文件描述符的成员
    printf("stdin的文件描述符为%d\n", stdin->_fileno);  //0
    printf("stdout的文件描述符为%d\n", stdout->_fileno);  //1
    printf("stderr的文件描述符为%d\n", stderr->_fileno);  //2
    return 0;
}
