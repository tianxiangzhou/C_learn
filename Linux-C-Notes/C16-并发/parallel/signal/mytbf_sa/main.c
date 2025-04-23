#include "mytbf.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define CPS     10
#define BUFSIZE 1024
#define BURST   100   //!! token上限


int main(int argc, char **argv)
{
    int      sfd, dfd = 1;
    char     buf[BUFSIZE];
    int      len, ret, pos;
    int      size;
    mytbf_t *tbf;

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <src>\n", argv[0]);
        exit(1);
    }

    tbf = mytbf_init(CPS, BURST);
    if (NULL == tbf)
    {
        fprintf(stderr, "mytbf_init failed\n");
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
        size = mytbf_fetchtoken(tbf, BUFSIZE);
        if (size < 0)
        {
            fprintf(stderr, "mytbf_fetchtoken failed: %s\n", strerror(errno));
        }

        //* 阻塞在这里的时候，token会自增
        while ((len = read(sfd, buf, size)) < 0)
        {
            //!!!
            if (EINTR == errno)
                continue;

            perror("read");
            break;
        }
        if (len == 0)
            break;

        if (size - len > 0)
            mytbf_returntoken(tbf, size - len);

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
    mytbf_destroy(tbf);
    exit(0);
}
