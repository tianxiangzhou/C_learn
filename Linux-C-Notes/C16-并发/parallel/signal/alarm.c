#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    alarm(10);
    alarm(1);
    alarm(5);

    // alarm(10);
    // alarm(5);
    // alarm(1);

    // 效果不一样

    for (;;)
        pause( );

    exit(0);
}