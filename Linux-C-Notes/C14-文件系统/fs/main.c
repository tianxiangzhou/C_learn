#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    printf("argc = %d\n", argc);

    // for (int i = 0; i < argc; i++)
    for (int i = 0; argv[i] != NULL; i++)
    {
        puts(argv[i]);
    }

    exit(0);
}