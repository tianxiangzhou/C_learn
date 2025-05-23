#ifndef SQSTACK_H__
#define SQSTACK_H__

#define SIZE 32

typedef int type;

typedef struct node_st
{
    type data[SIZE];
    int  top;
} sqstack;

sqstack *st_create(void);

int st_isempty(sqstack *);

int st_push(sqstack *, type *);

/* 取出栈顶元素 */
int st_pop(sqstack *, type *);

/* 查看栈顶元素 */
int st_top(sqstack *, type *);

void st_travel(sqstack *);

void st_destroy(sqstack *);

#endif