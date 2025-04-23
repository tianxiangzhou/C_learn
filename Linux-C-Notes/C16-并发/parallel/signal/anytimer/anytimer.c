/********************************************************************
 * @file     anytimer.c
 * @brief
 *           单一定时器实现任意数量的定时器。
 * @author   lzy (lllzzzyyy@buaa.edu.cn)
 * @url      https://lzyyyyyy.fun
 *
 * @date     2024-05-27
 *
 ********************************************************************/

#include "anytimer.h"
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>


typedef enum stat
{
    RUNNING,
    DONE,
    CANCELLED
} eStat;

typedef struct at_job
{
    int           sec;
    at_jobfunc_t *jobp;
    void         *arg;
    eStat         flag;
} at_job_t;

static at_job_t        *jobs[JOB_MAX];
static int              inited = 0;
static struct sigaction sa, alrm_sa_save;

static int find_id( )
{
    int i;

    for (i = 0; i < JOB_MAX; i++)
    {
        if (NULL == jobs[i])
            return i;
    }

    return -ENOSPC;
}

static void alrm_action(int sig, siginfo_t *infop, void *ucontext)
{
    int i;

    //* 判断信号来源
    if (SI_KERNEL != infop->si_code)
        return;

    for (i = 0; i < JOB_MAX; i++)
    {
        if (jobs[i] != NULL)
        {
            jobs[i]->sec -= 1;
            if (0 == jobs[i]->sec)
            {
                jobs[i]->jobp(jobs[i]->arg);
                jobs[i]->flag = DONE;
            }
        }
    }
}

static void unload_module( )
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

    for (i = 0; i < JOB_MAX; i++)
    {
        if (NULL != jobs[i])
            free(jobs[i]);
    }
}

static void load_module( )
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

    atexit(unload_module);   //!!! atexit()
}

int at_addjob(int sec, at_jobfunc_t *jobp, void *arg)
{
    if (sec < 0 || jobp == NULL)
        return -EINVAL;

    if (!inited)
    {
        load_module( );
        inited = 1;
    }

    at_job_t *job;
    int       id;

    job = malloc(sizeof(*job));
    if (NULL == job)
        return -ENOMEM;

    job->sec  = sec;
    job->jobp = jobp;
    job->arg  = arg;
    job->flag = RUNNING;
    id        = find_id( );
    if (id < 0)
        return -ENOSPC;

    jobs[id] = job;
    return id;
}

int at_canceljob(int id)
{
    if (id < 0 || id >= JOB_MAX)
        return -EINVAL;

    at_job_t *job = jobs[id];
    if (job == NULL)
        return -EINVAL;

    if (job->flag == DONE)
        return -EBUSY;

    if (job->flag == CANCELLED)
        return -ECANCELED;

    jobs[id]->flag = CANCELLED;

    return 0;
}

int at_waitjob(int id)
{
    if (id < 0 || id >= JOB_MAX)
        return -EINVAL;

    at_job_t *job = jobs[id];
    if (job == NULL)
        return -EINVAL;

    if (job->flag == RUNNING)
        return -EINVAL;

    free(job);
    jobs[id] = NULL;

    return 0;
}