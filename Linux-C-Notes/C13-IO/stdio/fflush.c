#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int i;

    // 这里不加\n的话，什么都不输出
    // 要么加\n，要么fflush
    printf("Before while()");
    fflush(stdout);

    while (1)
        ;

    printf("After while()");
    fflush(NULL);

    exit(0);
}