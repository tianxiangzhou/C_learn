#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define TIMESTRSIZE 1024
#define FMTSTRSIZE  1024

/**
 * @brief    mydate
 * @details
 *           Usage:
 *               mydate [-H 12|24] [-y 2|4] [-m] [-d] [-M] [-S]
 *           Options:
 *               -y: year 2位,4位
 *               -m: month
 *               -d: day
 *               -H: hour 12小时制,24小时制
 *               -M: minute
 *               -S: second
 *
 * @param    argc
 * @param    argv
 *
 * @return  int
 */
int main(int argc, char **argv)
{
    time_t     stamp;
    struct tm *tm;
    char       timestr[TIMESTRSIZE];
    int        c;
    char       fmtstr[FMTSTRSIZE];
    fmtstr[0] = '\0';
    FILE *fp  = stdout;

    time(&stamp);
    tm = localtime(&stamp);

    while (1)
    {
        //* 选项传参
        // c = getopt(argc, argv, "H:y:MSmd");

        //* 加'-'，接收非选项传参
        c = getopt(argc, argv, "-H:y:MSmd");
        if (c < 0)
            break;

        switch (c)
        {
            //* 非选项传参，返回1
        case 1:
            if (stdout == fp)   //! 先入为主
            {
                fp = fopen(argv[optind - 1], "w");
                if (NULL == fp)
                {
                    perror("fopen()");
                    fp = stdout;
                }
            }
            break;

        case 'H':
            if (0 == strcmp(optarg, "12"))
                strncat(fmtstr, "%I(%P) ", FMTSTRSIZE - 1);
            else if (0 == strcmp(optarg, "24"))
                strncat(fmtstr, "%H ", FMTSTRSIZE - 1);
            else
                fprintf(stderr,
                        "Usage: %s [-H 12|24] [-y 2|4] [-m] [-d] [-M] [-S]\n",
                        argv[0]);
            break;

        case 'M': strncat(fmtstr, "%M ", FMTSTRSIZE - 1); break;

        case 'S': strncat(fmtstr, "%S ", FMTSTRSIZE - 1); break;

        case 'y':
            if (0 == strcmp(optarg, "2"))
                strncat(fmtstr, "%y ", FMTSTRSIZE - 1);
            else if (0 == strcmp(optarg, "4"))
                strncat(fmtstr, "%Y ", FMTSTRSIZE - 1);
            else
                fprintf(stderr,
                        "Usage: %s [-H 12|24] [-y 2|4] [-m] [-d] [-M] [-S]\n",
                        argv[0]);
            break;

        case 'm': strncat(fmtstr, "%m ", FMTSTRSIZE - 1); break;

        case 'd': strncat(fmtstr, "%d ", FMTSTRSIZE - 1); break;

        default: break;
        }
    }

    strncat(fmtstr, "\n", FMTSTRSIZE - 1);
    strftime(timestr, TIMESTRSIZE, fmtstr, tm);

    fputs(timestr, fp);

    if (fp != stdout)
        fclose(fp);

    exit(0);
}