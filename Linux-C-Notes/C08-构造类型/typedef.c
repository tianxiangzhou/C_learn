#include <stdio.h>
#include <stdlib.h>

// #define INT int;

typedef int INT;

/**
 * #define IP int *;
 * IP p,q;  ->  int *p, q;
 *
 * typedef int *IP;
 * IP p,q;  ->  int *p, *q;
 *
 */

/**
 * typedef int ARR[6];   -->   int [6] -> ARR
 *
 * ARR a;  ->  int a[6];
 *
 */

#if 0
typedef struct node_st
{
    int   i;
    float p;
} NODE, *NODEP;

NODE  a;   // struct node_st a;
NODE *p;

NODEP p;   // struct node_st *p;
#endif


/**
 * typedef int FUNC(int);  -->  int(int) FUNC;
 * FUNC f;  -->  int f(int);
 *
 * typedef int *FUNCP(int);
 * FUNCP p; -->  int *p(int);
 *
 * typedef int *(*FUNCP)(int);
 * FUNCP p; --> int *(*p)(int);
 *
 */

int main( )
{
    INT i = 100;   // int i;

    printf("%d\n", i);

    exit(0);
}