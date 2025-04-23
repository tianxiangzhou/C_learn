#include <stdio.h>
#include <stdlib.h>

// void func(int **p, int n)
// {
//     *p = malloc(n);

//     if (NULL == *p)
//         exit(1);

//     return;
// }

void *func(int *p, int n)
{
    p = malloc(n);

    if (NULL == p)
        exit(1);

    return p;
}

int main( )
{
    int  num = 100;
    int *p   = NULL;

    // func(&p, num);

    p = func(p, num);

    free(p);

    exit(0);
}