#include <stdio.h>
#include <stdlib.h>

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
    int   ch;

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

    while (1)
    {
        ch = fgetc(fps);
        if (EOF == ch)
            break;
        fputc(ch, fpd);
    }

    fclose(fpd);
    fclose(fps);

    exit(0);
}