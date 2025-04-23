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
    int   n;

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

    /* 用n接收读到的个数，因为不知道能不能正好读到BUFSIZE */
    while ((n = fread(buf, 1, BUFSIZE, fps)) > 0)
        fread(buf, 1, n, fpd);

    fclose(fpd);
    fclose(fps);

    exit(0);
}
