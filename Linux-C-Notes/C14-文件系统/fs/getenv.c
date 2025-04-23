#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{

    puts(getenv("PATH"));

    getchar( );
    /**
     *  ./getenv
     *  ps axf | grep getenv
     *  pmap 4938
     */

    exit(0);
}