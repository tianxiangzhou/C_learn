#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 1024

/**
 * @brief
 * @details
 *          usage: ./mycpy <src> <dst>
 *
 * @return  int
 */

int main(int argc, char **argv)
{
    FILE *fps, *fpd;
    char  buf[BUFSIZE];

    if (argc < 3)
    {
        fprintf(stderr, "Usage:%s <src> <dst>\n", argv[0]);
        exit(1);
    }

    fopen(argv[1], "r");
    if (NULL == fps)
    {
        perror("fopen()");
        exit(1);
    }

    fopen(argv[2], "w");
    if (NULL == fpd)
    {
        // !!!
        fclose(fps);
        perror("fopen()");
        exit(1);
    }

    while (NULL != fgets(buf, BUFSIZE, fps))
        fputs(buf, fpd);

    fclose(fpd);
    fclose(fps);

    exit(0);
}