#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

    printf("argc = %d\n", argc);
    // 输出传入参数的个数

    // for (int i = 0; i < argc; i++) puts(argv[i]);

    for (int i = 0; argv[i] != NULL; i++)
        puts(argv[i]);

    // printf("Hello!\n");

    exit(0);
}