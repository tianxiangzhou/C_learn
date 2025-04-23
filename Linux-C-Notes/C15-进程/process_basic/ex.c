#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * @brief    data +%s
 * @details
 *
 * @param    argc
 * @param    argv
 * @return  int
 */
int main(int argc, char **argv)
{
    puts("Begin!");
    fflush(NULL);   // !!!

    execl("/bin/date", "date", "+%s", NULL);
    // NULL 作为参数列表的结束标志

    // !! 如果不出错，不会到这里
    perror("execl()");
    exit(1);

    puts("End!");

    exit(0);
}