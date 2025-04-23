#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    char buf[1024];
    int  year = 2014, month = 5, day = 13;

    printf("%d-%d-%d\n", year, month, day);

    sprintf(buf, "%d-%d-%d", year, month, day);
    puts(buf);

#if 0
    char str[] = "123456";

    printf("%d\n", atoi(str));
    /**
     * 输出 123456
     * 
     * 如果str是123a456
     * 输出123
     * 
     */
#endif

    exit(0);
}