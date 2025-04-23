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
static __sighandler_t   alrm_handler_save;   //!!! 保存原来的alarm行为


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

static void alrm_handler(int s)
{
    int i;

    alarm(1);

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
    int i;

    signal(SIGALRM, alrm_handler_save);
    alarm(0);
    for (i = 0; i < MYTBF_MAX; i++)
        free(job[i]);
}

static void module_load( )
{
    alrm_handler_save = signal(SIGALRM, alrm_handler);
    alarm(1);

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
