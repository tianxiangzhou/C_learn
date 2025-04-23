#include <stdio.h>
#include <stdlib.h>

int main( )
{
    int *p = NULL;

    p = malloc(sizeof(int));
    if (NULL == p)
    {
        printf("malloc() error!\n");
        exit(1);
    }

    *p = 10;

    printf("%p-->%d\n", *p);

    free(p);
    p = NULL;   // !important

    printf("%p-->%d\n", *p);
    // 0x5a677368 -- > 1516729192

    *p = 123;
    printf("%p-->%d\n", *p);
    // 0x7b -- > 0

    exit(0);
}