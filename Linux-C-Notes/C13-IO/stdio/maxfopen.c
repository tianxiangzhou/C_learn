#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( )
{
    FILE *fp    = NULL;
    int   count = 0;


    while (1)
    {

        fp = fopen("tmp", "w");
        if (NULL == fp)
        {
            perror("fopen()");
            break;
        }

        count++;
    }

    printf("count = %d\n", count);
    // out: 4089
    /* 可以通过下面这个命令限制 */
    /* ulimit -n */
    /* 4096 */

    exit(0);
}