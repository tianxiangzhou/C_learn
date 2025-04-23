#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#define CPS     10
#define BUFSIZE CPS

static volatile int loop = 0;

static void alrm_handler(int s)
{
    // alarm(1);   //!! 产生新的alarm
    loop = 1;
}

/***********************************************************************
 * @brief    slowcat
 * @details  流量控制，漏筒实现
 * @param    argc
 * @param    argv
 * @return   int
 ***********************************************************************/
int main(int argc, char **argv)
{
    int              sfd, dfd = 1;
    char             buf[BUFSIZE];
    int              len, ret, pos;
    struct itimerval itv;

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <src>\n", argv[0]);
        exit(1);
    }

    signal(SIGALRM, alrm_handler);
    // alarm(1);

    itv.it_interval.tv_sec  = 1;
    itv.it_interval.tv_usec = 0;
    itv.it_value.tv_sec     = 1;
    itv.it_value.tv_usec    = 0;
    if (setitimer(ITIMER_REAL, &itv, NULL) < 0)
    {
        perror("setitimer");
        exit(1);
    }

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
        while (!loop)
            pause( );   //!
        loop = 0;

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
