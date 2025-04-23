#include <stdio.h>
#include <stdlib.h>

#if 0
int print_value(int a, int b)
{
    printf("%d %d\n", a, b);
    return 0;
}
#endif

// void swap(int i, int j)
// {
//     int tmp;

//     tmp = i;
//     i   = j;
//     j   = tmp;
// }

void swap(int *p, int *q)
{
    int tmp;

    tmp = *p;
    *p  = *q;
    *q  = tmp;
}
int main( )
{
    int i = 3, j = 5;

    // swap(i, j);
    // 实际没有交换

    swap(&i, &j);

    printf("%d %d\n", i, j);


    // print_value(i, j);

    exit(0);
}