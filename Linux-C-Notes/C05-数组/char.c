#include <stdio.h>
#include <stdlib.h>

// #define N 10
#define N 32

int main( )
{

    // char str[N] = {'a', 'b', 'c'};
    char str[N] = "a";

    scanf("%s", str);
    // str数组名本身就是地址，不需要&str

    printf("%s", str);

    // gets(str);
    // puts(str);

    // for (int i = 0; i < N; i++)
    // {
    //     printf("%c ", str[i]);
    // }
    printf("\n");

    exit(0);
}