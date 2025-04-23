#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * @brief    few: folk, execl, wait
 * @details
 *
 * @param    argc
 * @param    argv
 * @return  int
 */
int main(int argc, char **argv)
{
    pid_t pid;

    puts("Begin!");

    fflush(NULL);

    pid = fork( );
    if (pid < 0)
    {
        perror("fork()");
        exit(1);
    }

    if (0 == pid)   // child
    {
        execl("/bin/date", "date", "+%s", NULL);
        perror("execl()");
        exit(1);
    }

    wait(NULL);

    puts("End!");

    exit(0);
}