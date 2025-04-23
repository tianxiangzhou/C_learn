#include <stdio.h>
#include <stdlib.h>

void c(void)
{
    printf("[%s]begin!\n", __FUNCTION__);
    printf("[%s]end!\n", __FUNCTION__);
}

void b(void)
{
    printf("[%s]begin!\n", __FUNCTION__);
    printf("[%s]call c()!\n", __FUNCTION__);
    c( );
    printf("[%s]c() returned!\n", __FUNCTION__);
    printf("[%s]end!\n", __FUNCTION__);
}

void a(void)
{
    printf("[%s]begin!\n", __FUNCTION__);
    printf("[%s]call b()!\n", __FUNCTION__);
    b( );
    printf("[%s]b() returned!\n", __FUNCTION__);
    printf("[%s]end!\n", __FUNCTION__);
}

int main( )
{
    printf("[%s]begin!\n", __FUNCTION__);
    printf("[%s]call a()!\n", __FUNCTION__);
    a( );
    printf("[%s]a() returned!\n", __FUNCTION__);
    printf("[%s]end!\n", __FUNCTION__);
    // out:
    // [main]begin!
    // [main]call a()!
    // [a]begin!
    // [a]call b()!
    // [b]begin!
    // [b]call c()!
    // [c]begin!
    // [c]end!
    // [b]c() returned!
    // [b]end!
    // [a]b() returned!
    // [a]end!
    // [main]a() returned!
    // [main]end!

    exit(0);
}