/***********************************************************************
 * @file     mytbf.c
 * @brief
 *           令牌桶库实现
 *
 * @author   lzy (lllzzzyyy@buaa.edu.cn)
 * @url      https://lzyyyyyy.fun
 *
 * @date     2024-05-26
 *
 ***********************************************************************/

#include "mytbf.h"
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>


struct mytbf_st
{
    int cps;
    int burst;
    int token;
    int pos;
};

static struct mytbf_st *job[MYTBF_MAX];
static int              inited = 0;
static struct sigaction sa, alrm_sa_save;


static int get_free_pos( )
{
    int i;

    for (i = 0; i < MYTBF_MAX; i++)
    {
        if (NULL == job[i])
            return i;
    }

    return -1;
}

static void alrm_action(int s, siginfo_t *infop, void *unused)
{
    int i;

    //* 判断信号来源
    if (SI_KERNEL != infop->si_code)
        return;

    for (i = 0; i < MYTBF_MAX; i++)
    {
        if (NULL != job[i])
        {
            job[i]->token += job[i]->cps;
            if (job[i]->token > job[i]->burst)
                job[i]->token = job[i]->burst;
        }
    }
}

static void module_unload( )
{
    int              i;
    struct itimerval itv;

    sigaction(SIGALRM, &alrm_sa_save, NULL);
    if (errno != 0)
    {
        perror("sigaction");
        exit(1);
    }

    itv.it_interval.tv_sec  = 0;
    itv.it_interval.tv_usec = 0;
    itv.it_value.tv_sec     = 0;
    itv.it_value.tv_usec    = 0;

    setitimer(ITIMER_REAL, &itv, NULL);
    if (errno != 0)
    {
        perror("setitimer");
        exit(1);
    }

    for (i = 0; i < MYTBF_MAX; i++)
        free(job[i]);
}

static void module_load( )
{
    struct sigaction sa;
    struct itimerval itv;

    sa.sa_sigaction = alrm_action;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;   // 表示使用sigaction三参数的形式

    sigaction(SIGALRM, &sa, &alrm_sa_save);
    if (errno != 0)
    {
        perror("sigaction");
        exit(1);
    }

    itv.it_interval.tv_sec  = 1;
    itv.it_interval.tv_usec = 0;
    itv.it_value.tv_sec     = 1;
    itv.it_value.tv_usec    = 0;

    setitimer(ITIMER_REAL, &itv, NULL);
    if (errno != 0)
    {
        perror("setitimer");
        exit(1);
    }

    atexit(module_unload);   //!!! atexit()
}

mytbf_t *mytbf_init(int cps, int burst)
{
    struct mytbf_st *me;
    int              pos;

    if (!inited)
    {
        module_load( );
        inited = 1;
    }

    pos = get_free_pos( );
    if (pos < 0)
        return NULL;

    me = malloc(sizeof(*me));
    if (NULL == me)
        return NULL;

    me->cps   = cps;
    me->burst = burst;
    me->token = 0;
    me->pos   = pos;

    job[pos] = me;

    return me;
}

static int min(int a, int b)
{
    return a < b ? a : b;
}

int mytbf_fetchtoken(mytbf_t *ptr, int size)
{
    if (size <= 0)
        return -EINVAL;

    struct mytbf_st *me = ptr;
    int              n;

    while (me->token <= 0)
        pause( );

    n = min(size, me->token);

    me->token -= n;

    return n;
}

int mytbf_returntoken(mytbf_t *ptr, int size)
{
    if (size <= 0)
        return -EINVAL;

    struct mytbf_st *me = ptr;

    me->token += size;
    if (me->token > me->burst)
        me->token = me->burst;

    return size;
}

int mytbf_destroy(mytbf_t *ptr)
{
    struct mytbf_st *me = ptr;

    job[me->pos] = NULL;

    free(ptr);
    return 0;
}
