#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define LEFT  30000000
#define RIGHT 30000200

/**
 * @brief    求质数（多进程版）
 * @details
 *
 * @param    argc
 * @param    argv
 * @return  int
 */
int main(int argc, char **argv)
{
    int   i, j, mark;
    pid_t pid;

    for (i = LEFT; i <= RIGHT; i++)
    {

        pid = fork( );
        if (pid < 0)
        {
            perror("fork()");
            exit(1);
        }

        if (pid == 0)   // child
        {
            mark = 1;
            for (j = 2; j < i / 2; j++)
            {
                if (i % j == 0)
                {
                    mark = 0;
                    break;
                }
            }
            if (mark)
                printf("%d is a primer\n", i);

            sleep(1000);   // * 让父进程先结束
            exit(0);       // ! 退出子进程
            // ! init 在孤儿进程 exit 后才收尸
        }
    }

    // sleep(1000);   // * 让子进程先结束，子进程会变成僵尸态
    exit(0);
}