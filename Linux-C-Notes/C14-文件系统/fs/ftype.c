#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

static int ftype(const char *fname)
{
    struct stat statres;

    if (stat(fname, &statres) < 0)
    {
        perror("stat()");
        exit(1);
    }

    if (S_ISREG(statres.st_mode))
        return '-';
    else if (S_ISDIR(statres.st_mode))
        return 'd';
    else if (S_ISSOCK(statres.st_mode))
        return 's';
    else if (S_ISFIFO(statres.st_mode))
        return 'p';
    else if (S_ISBLK(statres.st_mode))
        return 'b';
    else if (S_ISCHR(statres.st_mode))
        return 'c';
    else if (S_ISLNK(statres.st_mode))
        return 'l';
    else
        return '?';
}

/**
 * @brief    获取文件类型
 * @details
 *           Usage: ftype <filename>
 *
 * @param    argc
 * @param    argv
 *
 * @return  int
 */
int main(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage:...\n");
        exit(1);
    }

    printf("%c\n", ftype(argv[1]));

    exit(0);
}