#include <stdio.h>
#include <stdlib.h>



int main( )
{
    int  a[2][3] = {1, 2, 3, 4, 5, 6};
    int  i, j;
    int *p     = *a;
    int(*q)[3] = a;


#if 0
    //(W) int *p = a;
    // 报错，不兼容
    // 因为a是行指针，不是int类型指针

    // int *p = *a;
    *p = &a[0][0];

    // for (i = 0; i < 6; i++, p++)
    for (i = 0; i < 6; i++)
    {
        // printf("%d ", *p);
        printf("%d ", p[i]);
    }
    printf("\n");

#endif

#if 1
    printf("%p %p\n", a, a + 1);
    printf("%p %p\n\n", q, q + 1);

    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 3; j++)
        {
            // printf("%p --> %d ", &a[i][j], a[i][j]);
            // printf("%p --> %d ", *(a + i) + j, *(*(a + i) + j));
            printf("%p --> %d ", *(q + i) + j, *(*(q + i) + j));
        }

        printf("\n");
    }
#endif

    exit(0);
}