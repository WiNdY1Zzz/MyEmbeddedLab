#include <stdio.h>

int main()
{
    char buffer[32];
    fgets(buffer, 32, stdin);
    // while(getchar() != '\n');
    printf("你刚刚输入的字符串是:\n%s\n", buffer);

    int upper = 0;
    int lower = 0;
    int digit = 0;

    for(int i = 0;buffer[i] != '\0';i++)
    {
        if(buffer[i] >= 65 && buffer[i] <= 90)
        {
            upper++;
        }
        else if(buffer[i] >= 97 && buffer[i] <= 122)
        {
            lower++;
        }
        else if(buffer[i] >= 48 && buffer[i] <= 57)
        {
            digit++;
        }
    }

    printf("字符串中大写字母有%d个,小写字母有%d个,数字有%d个。\n", upper, lower, digit);

    return 0;
}