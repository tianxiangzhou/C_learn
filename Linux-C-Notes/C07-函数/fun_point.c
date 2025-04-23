#include <stdio.h>
#include <stdlib.h>

int add(int a, int b)
{
    return a + b;
}

int sub(int a, int b)
{
    return a - b;
}

int main( )
{
    int a = 3, b = 5;
    int ret;
    // int (*p)(int, int);
    // int (*q)(int, int);

    int (*funcp[2])(int, int);

    // p = add;
    // q = sub;

    funcp[0] = add;
    funcp[1] = sub;

    // ret = p(a, b);
    // ret = q(a, b);

    for (int i = 0; i < 2; i++)
    {
        ret = funcp[i](a, b);
        printf("ret = %d\n", ret);
    }

    exit(0);
}