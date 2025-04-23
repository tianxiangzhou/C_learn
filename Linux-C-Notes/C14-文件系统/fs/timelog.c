#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define FNAME   "time.log"
#define BUFSIZE 1024

/**
 * @brief    往文件里面输出时间戳
 * @details
 *           实例格式：2019-12-12 12:12:12
 *
 * @param    argc
 * @param    argv
 *
 * @return  int
 */
int main(int argc, char **argv)
{
    FILE      *fp;
    time_t     stamp;
    struct tm *tm;
    char       buf[BUFSIZE];
    int        count = 0;

    fp = fopen(FNAME, "a+");
    if (fp == NULL)
    {
        perror("fopen()");
        exit(1);
    }

    while (fgets(buf, BUFSIZE, fp) != NULL)
        count++;

    while (1)
    {
        stamp = time(NULL);

        tm = localtime(&stamp);
        if (NULL == tm)
        {
            perror("localtime()");
            exit(1);
        }

        strftime(buf, BUFSIZE, "%Y-%m-%d %H:%M:%S", tm);

        fprintf(fp, "%-4d%s\n", ++count, buf);

        /*
         *  加了sleep(1)之后就没有输出？
         *  全缓冲
         *  因为缓冲区没有满，没有刷新到文件里面
         */
        fflush(fp);

        sleep(1);
    }

    fclose(fp);
    exit(0);
}

//! 最终效果
// *[main][~/Linux-C-Notes/C13-Linux系统编程/fs]$ ./test
// ^C
// *[main][~/Linux-C-Notes/C13-Linux系统编程/fs]$ cat time.log
// 1   2024-05-11 21:53:26
// 2   2024-05-11 21:53:27
// 3   2024-05-11 21:53:28
// 4   2024-05-11 21:53:29
// 5   2024-05-11 21:53:30
// *[main][~/Linux-C-Notes/C13-Linux系统编程/fs]$ ./test
// ^C
// *[main][~/Linux-C-Notes/C13-Linux系统编程/fs]$ cat time.log
// 1   2024-05-11 21:53:26
// 2   2024-05-11 21:53:27
// 3   2024-05-11 21:53:28
// 4   2024-05-11 21:53:29
// 5   2024-05-11 21:53:30
// 6   2024-05-11 21:53:35
// 7   2024-05-11 21:53:36
// 8   2024-05-11 21:53:37
// 9   2024-05-11 21:53:38