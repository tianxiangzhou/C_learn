#include <stdio.h>
#include <stdlib.h>

typedef struct node_st
{
    int             coef;
    int             exp;
    struct node_st *next;
} list;

list *poly_create(int a[][2], int n)
{
    list *me, *newnode, *cur;

    me = malloc(sizeof(me));
    if (NULL == me)
        return NULL;
    me->next = NULL;

    cur = me;

    for (int i = 0; i < n; i++)
    {
        newnode = malloc(sizeof(*newnode));
        if (NULL == newnode)
            return NULL;

        newnode->coef = a[i][0];
        newnode->exp  = a[i][1];
        newnode->next = NULL;

        cur->next = newnode;
        cur       = newnode;
    }

    return me;
}

void poly_show(list *me)
{
    list *cur;

    for (cur = me->next; NULL != cur; cur = cur->next)
    {
        printf("(%d %d) ", cur->coef, cur->exp);
    }
    printf("\n");
}

void poly_union(list *p1, list *p2)
{
    list *p, *q, *r;

    p = p1->next;
    q = p2->next;
    r = p1;

    while (p && q)
    {
        if (p->exp < q->exp)
        {
            r->next = p;
            r       = p;
            p       = p->next;
        }
        else if (p->exp > q->exp)
        {
            r->next = q;
            r       = q;
            q       = q->next;
        }
        else
        {
            p->coef += q->coef;
            if (p->coef)
            {
                r->next = p;
                r       = p;
            }

            p = p->next;
            q = q->next;
        }
    }

    if (NULL == p)
        r->next = q;
    else
        r->next = p;
}

int main( )
{
    int a[][2] = {{5, 0}, {2, 1}, {8, 8}, {3, 16}};
    int b[][2] = {{6, 1}, {16, 6}, {-8, 8}};

    list *p1, *p2;

    p1 = poly_create(a, 4);
    if (NULL == p1)
        exit(1);

    p2 = poly_create(b, 3);
    if (NULL == p2)
        exit(1);

    poly_show(p1);
    poly_show(p2);

    poly_union(p1, p2);
    poly_show(p1);

    exit(0);
}