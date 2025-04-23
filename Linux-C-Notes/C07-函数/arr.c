#include <stdio.h>
#include <stdlib.h>

void print_arr(int *p, int size)
{
    int i;
    printf("%s:%d\n", __FUNCTION__, sizeof(p));
    // out: 8 指针

    for (i = 0; i < size; i++)
        printf("%d ", *(p + i));
    printf("\n");
}


void func(int *p, int size)
{
    int *tmp;

    for (int i = 0; i < size / 2; i++)
    {
        *tmp                = *(p + i);
        *(p + i)            = *(p + size - 1 - i);
        *(p + size - 1 - i) = *tmp;
    }
}

int main( )
{
    int a[] = {1, 3, 5, 7, 9};

    // printf("%s:%d\n", __FUNCTION__, sizeof(a));
    // out: 20 5*4

    // print_arr(a, sizeof(a) / sizeof(*a));


    for (int i = 0; i < sizeof(a) / sizeof(*a); i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");

    func(a, sizeof(a) / sizeof(*a));

    for (int i = 0; i < sizeof(a) / sizeof(*a); i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");

    exit(0);
}