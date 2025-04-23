#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    FILE *fp;
    int   count;

    if (argc < 2)
    {
        fprintf(stderr, "Usage...\n");
        exit(1);
    }

    fp = fopen(argv[1], "r");
    if (NULL == fp)
    {
        perror("fopen()");
        exit(1);
    }

    while (EOF != fgetc(fp))
    {
        count++;
    }

    printf("count = %d", count);

    fclose(fp);

    exit(0);
}