#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    pid_t pid;

    /*
     *  如果 ./fork1 > /tmp/out
     *  begin会由父进程输出两次
     *  缓冲问题
     *  文件时全缓冲
     */
    printf("[%d]Begin!\n", getpid( ));

    fflush(NULL);   // !!! 在fork之前刷新该刷新的流

    pid = fork( );
    if (pid < 0)
    {
        perror("fork()");
        exit(1);
    }

    if (pid == 0)   // child
    {
        printf("[%d]Child is working!\n", getpid( ));
    }
    else   // parent
    {
        printf("[%d]Parent is working!\n", getpid( ));
    }

    printf("[%d]End!\n", getpid( ));

    // getchar();

    exit(0);
}