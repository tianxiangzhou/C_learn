/**
 * @file     main.c
 * @brief    球钟算法
 *
 * @author   lzy (lllzzzyyy@buaa.edu.cn)
 * @url      https://lzyyyyyy.fun
 *
 * @date     2024-04-18
 *
 */
#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
#include "sqstack.h"

#define NR_BALL 27

int check(queue *qu)
{
    int i = (qu->head + 1) % MAXSIZE;

    do
    {
        if (qu->data[i] > qu->data[(i + 1) / MAXSIZE])
            return 0;
        i = (i + 1) % MAXSIZE;
    } while (i != qu->tail);

    return 1;
}

int main( )
{
    int      i;
    queue   *qu;
    int      t, value;
    int      time;
    sqstack *st_min, *st_fivemin, *st_hour;

    qu = qu_create( );
    if (NULL == qu)
        exit(1);

    st_min = st_create( );
    if (NULL == st_min)
        exit(1);

    st_fivemin = st_create( );
    if (NULL == st_fivemin)
        exit(1);

    st_hour = st_create( );
    if (NULL == st_hour)
        exit(1);


    for (i = 1; i <= NR_BALL; i++)
        qu_enqueue(qu, &i);

    qu_travel(qu);

    while (1)
    {
        qu_dequeue(qu, &t);
        time++;

        if (st_min->top != 3)
        {
            st_push(st_min, &t);
        }
        else
        {
            while (!st_isempty(st_min))
            {
                st_pop(st_min, &value);
                qu_enqueue(qu, &value);
            }
            if (st_fivemin->top != 10)
                st_push(st_fivemin, &t);
            else
            {
                while (!st_isempty(st_fivemin))
                {
                    st_pop(st_fivemin, &value);
                    qu_enqueue(qu, &value);
                }
                if (st_hour->top != 10)
                    st_push(st_hour, &t);
                else
                {
                    while (!st_isempty(st_hour))
                    {
                        st_pop(st_hour, &value);
                        qu_enqueue(qu, &value);
                    }
                    qu_enqueue(qu, &t);
                    if (check(qu))
                        break;
                }
            }
        }
    }

    printf("time = %d\n", time);

    qu_destroy(qu);
    st_destroy(st_min);
    st_destroy(st_fivemin);
    st_destroy(st_hour);

    exit(0);
}