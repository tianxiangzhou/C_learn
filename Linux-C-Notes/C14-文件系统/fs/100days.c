#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TIMESTRSIZE 128

/**
 * @brief    找出100天以后是哪一天
 * @details
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

    time(&stamp);
    tm = localtime(&stamp);
    strftime(timestr, TIMESTRSIZE, "Now: %Y-%m-%d", tm);
    puts(timestr);

    tm->tm_mday += 100;
    //  mktime 会先调整tm溢出的情况
    mktime(tm);
    strftime(timestr, TIMESTRSIZE, "100 days later: %Y-%m-%d", tm);
    puts(timestr);

    exit(0);
}