#include <stdio.h>
#include <stdlib.h>

int main( )
{
    int *p;
    int  num = 5;

    p = malloc(sizeof(int) * num);

    for (int i = 0; i < num; i++)
    {
        scanf("%d", &p[i]);
    }
    for (int i = 0; i < num; i++)
    {
        printf("%d ", p[i]);
    }
    printf("\n");

    free(p);

    exit(0);
}