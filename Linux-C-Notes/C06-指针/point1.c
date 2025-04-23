#include <stdio.h>
#include <stdlib.h>

int main( )
{
    int *p;

    *p = 1;

    printf("%p --> %d\n", p, *p);
    // 有的编译器报段错误，有的编译器能输出
    // 0x7feb1910dad0 -- > 420327424

    exit(0);
}