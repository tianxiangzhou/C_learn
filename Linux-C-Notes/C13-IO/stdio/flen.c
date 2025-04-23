#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    FILE *fp;

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

    fseek(fp, 0, SEEK_END);

    printf("%d\n", ftell(fp));

    fclose(fp);

    exit(0);
}