#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define CPS     10
#define BUFSIZE CPS
#define BURST   100   //!! token上限

// static volatile int token = 0;
static volatile sig_atomic_t token = 0;   //!!! 保证原子

static void alrm_handler(int s)
{
    alarm(1);   //!! 产生新的alarm
    token++;
    if (token > BURST)
        token = BURST;
}

/***********************************************************************
 * @brief    slowcat
 * @details  流量控制，令牌桶实现
 * @param    argc
 * @param    argv
 * @return   int
 ***********************************************************************/
int main(int argc, char **argv)
{
    int  sfd, dfd = 1;
    char buf[BUFSIZE];
    int  len, ret, pos;

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <src>\n", argv[0]);
        exit(1);
    }

    signal(SIGALRM, alrm_handler);
    alarm(1);

    do   //!!!
    {
        sfd = open(argv[1], O_RDONLY);
        if (sfd < 0)
        {
            //!!!
            if (errno != EINTR)
            {
                perror("open");
                exit(1);
            }
        }
    } while (sfd < 0);

    while (1)
    {
        while (token <= 0)
            pause( );   //!

        token--;        //!!! 这条指令不一定原子

        //* 阻塞在这里的时候，token会自增
        while ((len = read(sfd, buf, BUFSIZE)) < 0)
        {
            //!!!
            if (EINTR == errno)
                continue;

            perror("read");
            break;
        }
        if (len == 0)
            break;

        pos = 0;
        while (len > 0)
        {
            /* 可能没写完被别的中断打断 */
            ret = write(dfd, buf + pos, len);
            if (ret < 0)
            {
                //!!!
                if (EINTR == errno)
                    continue;
                perror("write");
                exit(1);
            }
            pos += ret;
            len -= ret;
        }

        // sleep(1);   //! 能实现，但是移植性不好
    }

    close(sfd);

    exit(0);
}
