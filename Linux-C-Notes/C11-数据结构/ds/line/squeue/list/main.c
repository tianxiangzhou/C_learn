#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

#define NAMESIZE 32

struct score_st
{
    int  id;
    char name[NAMESIZE];
    int  math;
    int  chinese;
};

static int print_s(void *record)
{
    struct score_st *r = record;

    printf("%d %s %d %d\n", r->id, r->name, r->math, r->chinese);
}

int main( )
{
    QUEUE          *qu;
    struct score_st tmp;
    int             i, ret;

    qu = queue_create(sizeof(struct score_st));
    if (NULL == qu)
        exit(1);

    for (i = 0; i < 6; i++)
    {
        tmp.id = i;
        snprintf(tmp.name, NAMESIZE, "stu%d", i);
        tmp.math    = rand( ) % 100;
        tmp.chinese = rand( ) % 100;

        if (0 != queue_en(qu, &tmp))
            break;
    }

    while (1)
    {
        ret = queue_de(qu, &tmp);
        if (-1 == ret)
            break;

        print_s(&tmp);
    }

    queue_destroy(qu);

    exit(0);
}