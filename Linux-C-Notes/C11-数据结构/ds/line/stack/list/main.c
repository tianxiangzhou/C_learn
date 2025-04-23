#include <stdio.h>
#include <stdlib.h>

#include <stack.h>

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
    STACK          *st;
    struct score_st tmp;
    int             i, ret;

    st = stack_create(sizeof(struct score_st));
    if (NULL == st)
        exit(1);

    for (i = 0; i < 7; i++)
    {
        tmp.id = i;
        snprintf(tmp.name, NAMESIZE, "stu%d", i);
        tmp.math    = rand( ) % 100;
        tmp.chinese = rand( ) % 100;

        if (stack_push(st, &tmp))
            exit(1);
    }

    while (1)
    {
        ret = stack_pop(st, &tmp);
        if (-1 == ret)
            break;
        print_s(&tmp);
    }

    stack_destroy(st);

    exit(0);
}