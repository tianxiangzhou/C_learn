#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

static void int_hander(int s)
{
    write(1, "!", 1);
}

int main(int argc, char **argv)
{
    int i;

    //* ignore SIGINT
    // signal(SIGINT, SIG_IGN);

    signal(SIGINT, int_hander);

    for (i = 0; i < 10; i++)
    {
        write(1, "*", 1);
        sleep(1);
    }

    exit(0);
}