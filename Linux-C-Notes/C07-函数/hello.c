#include <stdio.h>
#include <stdlib.h>

void print_hello(void);

// 主调函数
int main( )
{
    print_hello( );

    exit(0);
}

// 被调函数
void print_hello(void)
{
    printf("Hello world!\n");

    return;
}