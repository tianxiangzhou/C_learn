#include <stdio.h>
#include <stdlib.h>

#include "sqstack.h"

sqstack *st_create(void)
{
    sqstack *st;

    st = malloc(sizeof(*st));
    if (NULL == st)
        return NULL;

    st->top = -1;

    return st;
}

int st_isempty(sqstack *st)
{
    return (-1 == st->top);
}

int st_push(sqstack *st, type *data)
{
    if (SIZE - 1 == st->top)
        return -1;

    st->data[++st->top] = *data;

    return 0;
}

/* 取出栈顶元素 */
int st_pop(sqstack *st, type *data)
{
    if (st_isempty(st))
        return -1;

    *data = st->data[st->top--];

    return 0;
}


/* 查看栈顶元素 */
int st_top(sqstack *st, type *data)
{
    if (st_isempty(st))
        return -1;

    *data = st->data[st->top];

    return 0;
}

void st_travel(sqstack *st)
{
    if (st_isempty(st))
        return;

    int i;

    for (i = 0; i <= st->top; i++)
        printf("%d ", st->data[i]);
    printf("\n");
}

void st_destroy(sqstack *st)
{
    free(st);
}
