#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>

static jmp_buf save;

static void d(void)
{
    printf("%s():Begin.\n", __FUNCTION__);

    printf("%s():Jump now.\n", __FUNCTION__);
    longjmp(save, 6);
    // longjmp(save, 0);   // !!! 如果返回0，实际会返回1，避免与另一种情况冲突

    printf("%s():End.\n", __FUNCTION__);
}

static void c(void)
{
    printf("%s():Begin.\n", __FUNCTION__);
    printf("%s():Call d().\n", __FUNCTION__);

    d( );

    printf("%s():d() returned.\n", __FUNCTION__);
    printf("%s():End.\n", __FUNCTION__);
}

static void b(void)
{
    printf("%s():Begin.\n", __FUNCTION__);
    printf("%s():Call c().\n", __FUNCTION__);

    c( );

    printf("%s():c() returned.\n", __FUNCTION__);
    printf("%s():End.\n", __FUNCTION__);
}

static void a(void)
{
    int ret;

    printf("%s():Begin.\n", __FUNCTION__);

    ret = setjmp(save);
    if (0 == ret)
    {
        printf("%s():Call b().\n", __FUNCTION__);
        b( );
        printf("%s():b() returned.\n", __FUNCTION__);
    }
    else
    {
        printf("%s():Jumped back here with code %d.\n", __FUNCTION__, ret);
    }

    printf("%s():End.\n", __FUNCTION__);
}


/**
 * @brief   jmp
 * @details
 *           d跳回a
 *
 * @param    argc
 * @param    argv
 * @return  int
 */
int main(int argc, char **argv)
{
    printf("%s():Begin.\n", __FUNCTION__);
    printf("%s():Call a().\n", __FUNCTION__);

    a( );

    printf("%s():a() returned.\n", __FUNCTION__);
    printf("%s():End.\n", __FUNCTION__);

    exit(0);
}


// ! out
// main():Begin.
// main():Call a().
// a():Begin.
// a():Call b().
// b():Begin.
// b():Call c().
// c():Begin.
// c():Call d().
// d():Begin.
// d():Jump now.
// a():Jumped back here with code 6.
// a():End.
// main():a() returned.
// main():End.