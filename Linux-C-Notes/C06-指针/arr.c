#include <stdio.h>
#include <stdlib.h>

// TYPE NAME = VALUE;

// a[i]value: a[i] = *(a+i) = *(p+i) = p[i]
// &a[i]: &a[i] = a+i = p+i = &p[i]

int main( )
{

    int  a[] = {5, 1, 7, 2, 8, 3};
    int  y;
    int *p = &a[1];

    y = (*--p)++;

    printf("y = %d\n", y);         // out: y = 5
    printf("a[0] = %d\n", a[0]);   // out: a[0] = 6

#if 0
    int *p = (int[3]){1, 2, 3};
    // 只是不要数组名了

    for (int i = 0; i < 3; i++)
    {
        printf("%p --> %d\n", &p[i], p[i]);
    }
    // 0x7ffd12681964 --> 1
    // 0x7ffd12681968 --> 2
    // 0x7ffd1268196c --> 3
#endif

#if 0
    int  a[3];
    int *p = a;
    int  i;

    for (i = 0; i < sizeof(a) / sizeof(*a); i++)
    {
        printf("%p --> %d\n", &a[i], a[i]);
    }

    for (i = 0; i < sizeof(a) / sizeof(*a); i++)
    {
        scanf("%d", p++);
    }

    p = a;
    for (i = 0; i < sizeof(a) / sizeof(*a); i++, p++)
    {
        // printf("%d\n", *p++);
        printf("%p --> %d\n", p, *p);
    }

    // out:
    //
    // 0x7ffdad36c478 --> -563487456
    // 0x7ffdad36c47c --> 32710
    // 0x7ffdad36c480 --> 0
    // 1
    // 2
    // 3
    // 0x7ffdad36c478 --> 1
    // 0x7ffdad36c47c --> 2
    // 0x7ffdad36c480 --> 3
#endif

#if 0
    int a[3] = {1, 2, 3};
    int i;

    int *p = a;

    p++;   // p从a[0]挪到a[1]
    printf("%p,%p\n", p, p + 1);

    // *a相当于*(a+0)相当于a[0]
    // for (i = 0; i < sizeof(a) / sizeof(a[0]); i++)
    for (i = 0; i < sizeof(a) / sizeof(*a); i++)
    {
        // printf("%p--> %d\n", &a[i], a[i]);
        // printf("%p--> %d\n", a + i, a[i]);
        printf("%p--> %d\n", p + i, *(p + i));
    }
    printf("\n");
#endif

    exit(0);
}