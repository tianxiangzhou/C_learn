#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main( )
{
    char *name[5] = {"Follow me", "Basic", "Great", "Fortran", "Computer"};
    // 指针数组
    int   i, j, k;
    char *tmp;

    for (i = 0; i < 5 - 1; i++)
    {
        k = i;
        for (j = i + 1; j < 5; j++)
        {
            if (strcmp(name[k], name[j]) > 0)
                k = j;
        }
        if (k != j)
        {
            tmp     = name[i];
            name[i] = name[k];
            name[k] = tmp;
        }
    }

    for (int i = 0; i < 5; i++)
    {
        puts(name[i]);
    }

    exit(0);
}