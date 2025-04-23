#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//!!! 不加volatile关键字，loop变量的值不会被修改，导致死循环!!!
static volatile int loop = 1;

static void alrm_handler(int sig)
{
    loop = 0;
}

/***********************************************************************
 * @brief    用sig实现计时
 * @param    argc
 * @param    argv
 * @return   int
 ***********************************************************************/
int main(int argc, char **argv)
{
    long long count = 0;

    //!!!
    signal(SIGALRM, alrm_handler);
    alarm(5);
    //!!! signal注册时钟信号的行为需要在alarm之前

    while (loop)
        count++;

    printf("%lld \n", count);

    exit(0);
}