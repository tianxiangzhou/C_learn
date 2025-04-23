#include <bits/types/sigset_t.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

static void int_hander(int s)
{
    write(1, "!", 1);
}

int main(int argc, char **argv)
{
    int      i;
    int      j;
    sigset_t set;
    sigset_t oldset;
    sigset_t saveset;

    //! 要考虑原来是否阻塞的
    signal(SIGINT, int_hander);
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    sigprocmask(SIG_UNBLOCK, &set, &saveset);

    for (j = 0; j < 1000; j++)
    {
        sigprocmask(SIG_BLOCK, &set, &oldset);

        for (i = 0; i < 5; i++)
        {
            write(1, "*", 1);
            sleep(1);
        }
        write(1, "\n", 1);

        // sigprocmask(SIG_UNBLOCK, &set, NULL);
        sigprocmask(SIG_SETMASK, &oldset, NULL);
    }
    // ctrl+\ : quit信号快捷方式

    //!!! 还原原来的阻塞状态
    sigprocmask(SIG_SETMASK, &saveset, NULL);

    exit(0);
}