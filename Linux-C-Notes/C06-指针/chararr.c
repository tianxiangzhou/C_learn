#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( )
{

    char *str = "hello";

    printf("%d %d\n", sizeof(str), strlen(str));
    // out: 8 5

    //(F) strcpy(str, "world");
    // 这里企图把 "world" 覆盖 "hello"这个串常量

    str = "world";

    puts(str);

    // char str[] = "hello";

    // printf("%d %d\n", sizeof(str), strlen(str));
    // out :6 5



#if 0
    char str[] = "hello";
    // str[6]

    //(F) str = "world";
    strcpy(str, "world");

    puts(str);

#endif



#if 0
    char str[] = "I love china!";

    char *p = str + 7;

    puts(str);
    puts(p);
    // I love china!
    // china!
#endif



    exit(0);
}