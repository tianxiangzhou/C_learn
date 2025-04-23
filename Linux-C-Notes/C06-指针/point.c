#include <stdio.h>
#include <stdlib.h>



int main( )
{
    int i = 1;

    int *p = &i;
    // 相当于
    // int *p;
    // p = &i;

    int **q = &p;

    printf("i = %d\n", i);
    printf("&i = %d\n", &i);

    printf("p = %d\n", p);
    printf("&p = %d\n", &p);
    printf("*p = %d\n", *p);

    printf("q = %d\n", q);
    printf("*q = %d\n", *q);
    printf("**q = %d\n", **q);
    // i = 1
    // &i = 1175115956
    // p = 1175115956
    // &p = 1175115944
    // *p = 1
    // q = 1175115944
    // *q = 1175115956
    // **q = 1

#if 0
    float  *q;
    double *d;
    char   *c;

    printf("%d\n", sizeof(i));
    printf("%d\n", sizeof(p));
    printf("%d\n", sizeof(q));
    printf("%d\n", sizeof(d));
    printf("%d\n", sizeof(c));
    // out:
    // 4
    // 8
    // 8
    // 8
    // 8
    /* 指针在某一个平台所占的大小是一样的 */
    /* 其指向的类型的空间的大小，由指针的类型决定 */

#endif

#if 0
    printf("i = %d\n", i);
    printf("&i = %d\n", &i);
    printf("p = %d\n", p);
    printf("&p = %d\n", &p);
    printf("*p = %d\n", *p);
    // out:
    // i = 1
    // &i = 1343894748
    // p = 1343894748
    // &p = 1343894736
    // *p = 1
#endif

    exit(0);
}