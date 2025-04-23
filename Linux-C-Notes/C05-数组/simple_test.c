#include <stdio.h>
#include <stdlib.h>

static void fibonacci(void)
{
    int fib[10] = {1, 1};

    for (int i = 2; i < sizeof(fib) / sizeof(fib[0]); i++)
    {
        fib[i] = fib[i - 2] + fib[i - 1];
    }
    for (int i = 0; i < sizeof(fib) / sizeof(fib[0]); i++)
    {
        printf("fib[%d] = %d\n", i, fib[i]);
    }

    printf("\n");

    int i = 0;
    int j = sizeof(fib) / sizeof(fib[0]) - 1;
    int tmp;

    while (i < j)
    {
        tmp    = fib[i];
        fib[i] = fib[j];
        fib[j] = tmp;

        i++;
        j--;
    }

    for (int i = 0; i < sizeof(fib) / sizeof(fib[0]); i++)
    {
        printf("fib[%d] = %d\n", i, fib[i]);
    }
}

#define N 10
static void sort1(void)
{
    int a[N] = {12, 8, 45, 30, 98, 67, 2, 7, 68, 11};
    int tmp;

    for (int i = 0; i < N; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");

    for (int i = 0; i < (N - 1); i++)
    {
        for (int j = 0; j < N - 1 - i; j++)
        {
            if (a[j] > a[j + 1])
            {
                tmp      = a[j];
                a[j]     = a[j + 1];
                a[j + 1] = tmp;
            }
        }
    }

    for (int i = 0; i < N; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}

static void sort2(void)
{
    int a[N] = {23, 45, 90, 76, 13, 55, 76, 45, 3, 8};
    int i, j, k, tmp;

    for (int i = 0; i < N; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");

    for (i = 0; i < N - 1; i++)
    {
        k = i;
        for (j = i + 1; j < N; j++)
        {
            if (a[j] < a[k])
                k = j;
        }
        if (i != k)
        {
            tmp  = a[i];
            a[i] = a[k];
            a[k] = tmp;
        }
    }

    for (int i = 0; i < N; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}

static void base_convert(void)
{
    int num, base;
    int n[128];
    int i = 0;

    printf("Please enter the converted num:\n");
    scanf("%d", &num);
    printf("Please enter the base:\n");
    scanf("%d", &base);

    do
    {
        n[i] = num % base;
        num  = num / base;
        i++;
    } while (num != 0);

    for (i--; i >= 0; i--)
    {
        if (n[i] >= 10)
            printf("%c", n[i] - 10 + 'A');
        else
            printf("%d", n[i]);
    }
    printf("\n");
}

static void primer(void)
{
    char primer[1001] = {0};
    int  i, j;

    for (i = 2; i < 1001; i++)
    {
        for (j = i * 2; j < 1001; j += i)
            primer[j] = -1;
    }

    for (i = 2; i < 1001; i++)
    {
        if (primer[i] == 0)
            printf("%d is a primer.\n", i);
    }
}

int main( )
{
    // fibonacci();

    // sort1();

    // sort2();

    // base_convert();

    primer( );

    exit(0);
}