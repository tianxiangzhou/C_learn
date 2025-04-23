/**
 *   const int a;
 *   int const a;
 *
 *   常量指针
 *   const int *p;
 *   int const *p;
 *
 *   指针常量
 *   int *const p;
 *
 *   const int *const p;
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define PI 3.14

int main( )
{
    int i = 1;
    int j = 100;

    const int *const p = &i;

    //(F) p = &j;

    //(F) *p = 10;


#if 0
    int *const p = &i;

    //(T) *p = 10;

    //(F) p = &j;
    // [main][~/workspace/Linux-C-Notes/Chapter6]$ make const
    // cc     const.c   -o const
    // const.c: In function ‘main’:
    // const.c:29:7: error: assignment of read-only variable ‘p’
    //    29 |     p = &j;
    //       |       ^
    // make: *** [<builtin>: const] Error 1

    printf("i = %d\n", *p);

#endif

#if 0
    int i = 1;
    int j = 2;

    // 常量指针
    const int *p = &i;

    //(T) i = 2;
    // 直接用i改还是可以改成功的

    //(F) *p = 2;

    //(T) p = &j;

    printf("i = %d\n", i);

#endif


#if 0
    const float pi = 3.14;
    // const 将变量常量化，相比于宏，多了检查语法

    //(F) pi = 3.14159;

    // float *p = &pi;
    const float *p = &pi;

    // *p = 3.14159;
    // [main][~/workspace/Linux-C-Notes/Chapter6]$ make const
    // cc     const.c   -o const
    // const.c: In function ‘main’:
    // const.c:28:16: warning: initialization discards ‘const’ qualifier from
    // pointer target type [-Wdiscarded-qualifiers]
    //    28 |     float *p = &pi;
    //       |

#endif

    exit(0);
}
