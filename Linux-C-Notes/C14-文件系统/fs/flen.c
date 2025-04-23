#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

// !!! 不是int
static off_t flen(char *fname)
{
    struct stat statres;

    if (stat(fname, &statres) < 0)
    {
        perror("stat()");
        exit(1);
    }

    return statres.st_size;
}

/**
 * @brief    获取文件大小
 * @details
 *           Usage: ./flen filename
 *
 * @param    argc
 * @param    argv
 * @return  int
 */
int main(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage:...\n");
        exit(1);
    }

    // !!! 通过makefile指定off_t 64位
    printf("%lld\n", flen(argv[1]));

    exit(0);
}