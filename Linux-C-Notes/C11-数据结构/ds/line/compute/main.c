#include <stdio.h>
#include <stdlib.h>

#include "sqstack.h"

// !!! 课程不完整，程序未写完
// TODO: snum和sop需要不同的datatype

static void compute(sqstack *snum, int *op)
{
    datatype n1, n2, n;

    st_pop(snum, &n2);
    st_pop(snum, &n1);

    switch (*op)
    {
    case '+': n = n1 + n2; break;
    case '-': n = n1 - n2; break;
    case '*': n = n1 * n2; break;
    case '/': n = n1 / n2; break;

    default: exit(1);
    }
    st_push(snum, &n);
}

static void deal_bracket(sqstack *snum, sqstack *sop)
{
    datatype old_op;

    st_top(sop, &old_op);

    while (old_op != '(')
    {
        st_pop(sop, &old_op);
        compute(snum, &old_op);
        st_top(sop, &old_op);
    }

    st_pop(sop, &old_op);
}

static int get_pri(int op)
{
    switch (op)
    {
    case '(': return 0;
    case '+':
    case '-': return 1;
    case '*':
    case '/': return 2;
    default: return -1;
    }
}


static void deal_op(sqstack *snum, sqstack *sop, char op)
{
    datatype old_op;

    if (st_isempty(sop) || op == '(')
    {
        st_push(sop, (datatype *)&op);
        return;
    }

    st_top(sop, &old_op);

    if (get_pri(op) > get_pri(old_op))
    {
        st_push(sop, (datatype *)&op);
        return;
    }

    while (get_pri(op) <= get_pri(old_op))
    {
        st_pop(sop, &old_op);
        compute(snum, &old_op);
        if (st_isempty(sop))
            break;

        st_top(sop, &old_op);
    }
    st_push(sop, (datatype *)&op);
}


int main( )
{
    int      i;
    char     str[] = "(11+3)*2-5";
    sqstack *snum, *sop;
    int      value = 0;
    int      flag  = 0;
    int      old_op;

    snum = st_create( );
    if (NULL == snum)
        exit(1);

    sop = st_create( );
    if (NULL == sop)
        exit(1);

    while (str[i] != '\n')
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            value = 10 * value + (str[i] - '0');
            flag  = 1;
        }
        else   // is a op
        {
            if (flag)
            {
                st_push(snum, &value);
                flag  = 0;
                value = 0;
            }

            if (str[i] == ')')
            {
                deal_bracket(snum, sop);
            }
            else   // ( + - * /
            {
                deal_op(snum, sop, str[i]);
            }
        }
        i++;
    }

    if (flag)
        st_push(snum, &value);

    while (!st_isempty(sop))
    {
        st_pop(sop, &old_op);
        compute(snum, &old_op);
    }




    st_destroy(snum);
    st_destroy(sop);

    exit(0);
}