#include <stdio.h>
#include <stdlib.h>

static void f1(void)
{
    puts("f1() is working!");
}

static void f2(void)
{
    puts("f2() is working!");
}

static void f3(void)
{
    puts("f3() is working!");
}

int main(int argc, char **argv)
{
    puts("Begin!");

    atexit(f1);
    atexit(f2);
    atexit(f3);

    puts("End!");

    exit(0);
}
// out:
// *[main][~/Linux-C-Notes/C13-Linux系统编程/fs]$ ./atexit
// Begin!
// End!
// f3() is working!
// f2() is working!
// f1() is working!