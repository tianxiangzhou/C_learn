#include <stdio.h>
#include <stdlib.h>

#include "list.h"

list *list_create( )
{
    list *me;
    me = malloc(sizeof(*me));
    if (NULL == me)
        return NULL;

    me->next = NULL;

    return me;
}

// 从第一个有效节点作为第0个
int list_insert_at(list *me, int i, datatype *data)
{
    int   k    = 0;
    list *node = me, *newnode;

    if (i < 0)
        return -1;
    // return -EINVAL;

    while (k < i && node != NULL)
    {
        node = node->next;
        k++;
    }

    if (NULL != node)
    {
        newnode = malloc(sizeof(*newnode));
        if (NULL == newnode)
            return -2;

        newnode->data = *data;
        newnode->next = NULL;

        newnode->next = node->next;
        node->next    = newnode;

        return 0;
    }
    else
        return -3;
}

// 有序插入
int list_order_insert(list *me, datatype *data)
{
    list *p = me, *q;

    while (p->next && p->next->data < *data)
        p = p->next;

    q = malloc(sizeof(*q));
    if (NULL == q)
        return -1;

    q->data = *data;
    q->next = p->next;
    p->next = q;

    return 0;
}

int list_delete_at(list *me, int i, datatype *data)
{
    int   k = 0;
    list *p = me, *q;

    *data = -1;

    if (i < 0)
        return -1;

    while (k < i)
    {
        p = p->next;
        k++;
    }

    if (p)
    {
        q       = p->next;
        p->next = q->next;
        *data   = q->data;
        free(q);
        q = NULL;

        return 0;
    }
    else
        return -2;
}

int list_delete(list *me, datatype *data)
{
    list *p = me, *q;
    while (p->next && p->next->data != *data)
        p = p->next;

    if (NULL == p->next)
        return -1;
    else
    {
        q       = p->next;
        p->next = q->next;
        free(q);
        q = NULL;
    }

    return 0;
}

int list_isempty(list *me)
{
    if (NULL == me->next)
        return 0;
    return 1;
}

void list_display(list *me)
{
    list *node = me->next;
    if (0 == list_isempty(me))
        return;

    while (NULL != node)
    {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");

    return;
}

void list_destroy(list *me)
{
    list *node, *next;

    for (node = me->next; node != NULL; node = next)
    {
        next = node->next;
        free(node);
    }

    free(me);

    return;
}