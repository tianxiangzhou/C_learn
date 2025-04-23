#include <stdio.h>
#include <stdlib.h>

#define M 3
#define N 4

void print_douarr(int *p, int n)
{
    int i, j;

    for (i = 0; i < n; i++)
    {
        printf("%d ", *(p + i));
    }
    printf("\n");
}

// void print_douarr1(int (*p)[N], int m, int n)
void print_douarr1(int (*p)[N], int m, int n)
{
    printf("sizeof(p)=%d\n", sizeof(p));

    int i, j;

    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            // printf("%4d", *(*(p + i) + j));
            printf("%4d", p[i][j]);
        }
        printf("\n");
    }
}

float average_score(int *p, int n)
{
    float sum = 0;

    for (int i = 0; i < n; i++)
    {
        sum += *(p + i);
    }

    return sum / n;
}


#if 0
void find_num(int (*p)[N], int num)
{
    for (int i = 0; i < N; i++)
    {
        printf("%d ", *(*(p + num) + i));
    }
    printf("\n");
}
#endif

int *find_num(int (*p)[N], int num)
{
    if (num > M - 1)
        return NULL;
    return *(p + num);
}

int main( )
{
    int i, j;
    int a[M][N] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

    float ave;

    // ave = average_score(*a, M * N);
    // printf("ave = %f\n", ave);

    // find_num(a, 2);

    int *res;

    res = find_num(a, 2);
    if (NULL != res)
    {
        for (i = 0; i < N; i++)
        {
            printf("%d ", res[i]);
        }
        printf("\n");
    }
    else
    {
        printf("Can not find!\n");
    }


    // print_douarr(&a[0][0], M * N);

    // printf("sizeof(a)=%d\n", sizeof(a));
    // print_douarr1(a, M, N);

    exit(0);
}