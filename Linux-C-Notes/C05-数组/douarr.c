#include <stdio.h>
#include <stdlib.h>

#define M 2
#define N 3

int main( )
{

    // int a[M][N] = {{1, 2, 3}, {4, 5, 6}};
    int a[M][N] = {1, 2, 3, 4, 5};
    int i, j;

    printf("a = %p\n", a);
    printf("a+1 = %p\n", a + 1);

    for (i = 0; i < M; i++)
    {
        for (j = 0; j < N; j++)
        {
            printf("%p --> %d\n", &a[i][j], a[i][j]);
        }
        printf("\n");
    }

    exit(0);
}