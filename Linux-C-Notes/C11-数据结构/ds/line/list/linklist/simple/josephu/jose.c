#include <stdio.h>
#include <stdlib.h>

#define JOSE_NUM 8

typedef struct node_st
{
    int             data;
    struct node_st *next;
} list;

// try something
#if 0
list *jose_create(int a[], int n)
{
    list *me, *p;
    me = malloc(sizeof(*me));
    if (NULL == me)
        return NULL;

    for (int i = 0; i < n; i++)
    {
        me->data = me;

        p        = malloc(sizeof(*p));
        p        = me;
        p->data  = a[i];
        me->next = p;
    }

    return me;
}
#endif

list *jose_create(int n)
{
    list *me, *newnode, *cur;
    int   i = 1;

    me = malloc(sizeof(*me));
    if (NULL == me)
        return NULL;
    me->data = i;
    me->next = me;
    i++;

    cur = me;

    for (; i <= n; i++)
    {
        newnode = malloc(sizeof(*newnode));
        if (NULL == newnode)
            return NULL;
        newnode->data = i;
        newnode->next = me;

        cur->next = newnode;
        cur       = newnode;
    }

    return me;
}

void jose_show(list *me)
{
    list *list;

    for (list = me; list->next != me; list = list->next)
    {
        // sleep(1);
        printf("%d ", list->data);
        // fflush(NULL);
    }
    printf("%d\n", list->data);
}

void jose_kill(list **me, int n)
{
    list *cur = *me, *node;
    int   i   = 1;

    while (cur != cur->next)
    {
        while (i < n)
        {
            node = cur;
            cur  = cur->next;
            i++;
        }

        printf("%d ", cur->data);
        node->next = cur->next;
        free(cur);

        cur = node->next;
        i   = 1;
    }

    *me = cur;

    printf("\n");
}

int main( )
{
    list *list;

    list = jose_create(JOSE_NUM);

    jose_show(list);

    jose_kill(&list, 3);

    jose_show(list);

    exit(0);
}