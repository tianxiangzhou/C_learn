#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/***********************************************************************
 * @brief    使用time函数实现计时功能
 * @param    argc
 * @param    argv
 * @return  int
 ***********************************************************************/
int main(int argc, char **argv)
{
    time_t    end;
    long long count = 0;

    end = time(NULL) + 5;

    while (time(NULL) <= end)
        count++;

    printf("%lld\n", count);

    exit(0);
}