#include "anytimer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

static void f1(void *p)
{
    printf("f1():%s\n", (char *)p);
}

static void f2(void *p)
{
    printf("f2():%s\n", (char *)p);
}

int main(int argc, char **argv)
{
    int job1;

    puts("Begin!");

    job1 = at_addjob(5, f1, "aaa");
    if (job1 < 0)
    {
        fprintf(stderr, "at_addjob() failed!:%s\n", strerror(-job1));
        exit(1);
    }

    job1 = at_addjob(2, f2, "bbb");
    if (job1 < 0)
    {
        fprintf(stderr, "at_addjob() failed!:%s\n", strerror(-job1));
        exit(1);
    }

    job1 = at_addjob(7, f1, "ccc");
    if (job1 < 0)
    {
        fprintf(stderr, "at_addjob() failed!:%s\n", strerror(-job1));
        exit(1);
    }

    puts("End!");


    while (1)
    {
        write(1, ".", 1);
        sleep(1);
    }


    exit(0);
}