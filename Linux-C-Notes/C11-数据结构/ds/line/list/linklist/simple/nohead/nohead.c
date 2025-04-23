#include <stdio.h>
#include <stdlib.h>

#include "nohead.h"


#if 0
struct node_st *list_insert(struct node_st *list, struct score_st *data)
{
    struct node_st *new;

    new = malloc(sizeof(*new));
    if (NULL == new)
        return NULL;

    new->data = *data;
    new->next = list;
    list      = new;

    return list;
}
#endif

int list_insert(struct node_st **list, struct score_st *data)
{
    struct node_st *new;

    new = malloc(sizeof(*new));
    if (NULL == new)
        return -1;

    new->data = *data;
    new->next = *list;
    *list     = new;

    return 0;
}

void list_show(struct node_st *list)
{
    struct node_st *cur;

    for (cur = list; NULL != cur; cur = cur->next)
    {
        printf("%d %s %d %d\n",
               cur->data.id,
               cur->data.name,
               cur->data.math,
               cur->data.chinese);
    }
}

// 删除首位
int list_delete(struct node_st **list)
{
    struct node_st *cur;

    if (NULL == *list)
        return -1;

    cur   = *list;
    *list = (*list)->next;

    free(cur);

    return 0;
}

struct score_st *list_find(struct node_st **list, int id)
{
    struct node_st *cur;

    if (NULL == *list)
        return NULL;

    // for (cur = *list; NULL != cur->next; cur = cur->next)
    // !!! 是cur不为空
    for (cur = *list; NULL != cur; cur = cur->next)
    {
        if (id == cur->data.id)
        {
            // printf("%d %s %d %d\n",
            //        cur->data.id,
            //        cur->data.name,
            //        cur->data.math,
            //        cur->data.chinese);
            return &(cur->data);
        }
    }

    return NULL;
}

int list_destroy(struct node_st **list)
{
    struct node_st *cur;

    if (NULL == list)
        return -1;

    for (cur = *list; NULL != cur; cur = *list)
    {
        *list = cur->next;
        free(cur);
    }
}