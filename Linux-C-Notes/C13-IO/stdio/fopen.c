#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( )
{
    FILE *fp;

    fp = fopen("tmp", "r");
    if (NULL == fp)
    {
        // fprintf(stderr, "fopen() failed!   errno = %d\n", errno);
        // out: fopen() failed!   errno = 2
        /* errno:定义路径 /usr/include/asm-generic/errno-base.h */

        // perror("fopen()");
        // out: fopen(): No such file or directory

        fprintf(stderr, "fopen(): %s\n", strerror(errno));
        // out: fopen(): No such file or directory

        exit(1);
    }

    puts("OK!");

    fclose(fp);

    exit(0);
}