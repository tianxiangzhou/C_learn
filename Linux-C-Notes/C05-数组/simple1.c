#include <stdio.h>
#include <stdlib.h>

#define M 3

int main( )
{
    // int arr[M] = {1};
    // static int arr[M];
    int arr[] = {1, 2, 3, 4, 5, 6};

    printf("%d\n", sizeof(arr) / sizeof(arr[0]));

    printf("%d\n", sizeof(arr));
    // out: 12

    printf("arr = %p\n", arr);

    // arr = {4, 5, 6};
    // arr常量，不可赋值

    // for (int i = 0; i < M; i++)
    // {
    //     scanf("%d", &arr[i]);
    // }

    arr[3] = 10;
    printf("arr[3] = %d\n", arr[3]);
    // out: arr[3] = 10
    // 正常输出，起始越界了

    for (int i = 0; i < M; i++)
    {
        printf("%p --> %d\n", &arr[i], arr[i]);
    }

    exit(0);
}