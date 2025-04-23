#include <stdio.h>
#include <stdlib.h>

int main( )
{
    // 以"\033"开头
    printf("\033[2J\033[1;1H\033[31;4mhello\n\033[0m");

    exit(0);
}