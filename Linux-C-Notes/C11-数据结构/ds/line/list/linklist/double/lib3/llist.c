#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "llist.h"

int   llist_insert(LLIST *ptr, const void *data, int mode);
void *llist_find(LLIST *ptr, const void *key, llist_cmp *);
int   llist_delete(LLIST *, const void *key, llist_cmp *);
int   llist_fetch(LLIST *, const void *key, llist_cmp *, void *data);
void  llist_travel(LLIST *ptr, llist_op *op);

LLIST *llist_create(int initsize)
{
    LLIST *new;

    new = malloc(sizeof(*new));   // !!! 不是sizeof(initsize),也不是new,是*new
    if (NULL == new)
        return NULL;

    new->size      = initsize;
    new->head.prev = &new->head;
    new->head.next = &new->head;

    new->insert = llist_insert;
    new->delete = llist_delete;
    new->find   = llist_find;
    new->fetch  = llist_fetch;
    new->travel = llist_travel;

    return new;
}

int llist_insert(LLIST *ptr, const void *data, int mode)
{
    struct llist_node_st *newnode;

    newnode = malloc(sizeof(*newnode) + ptr->size);   // -4
    if (NULL == newnode)
        return -1;

    memcpy(newnode->data, data, ptr->size);

    if (LLIST_FORWARD == mode)
    {
        newnode->prev = &ptr->head;
        newnode->next = ptr->head.next;
    }
    else if (LLIST_BACKWARD == mode)
    {
        newnode->prev = ptr->head.prev;
        newnode->next = &ptr->head;
    }
    else   // error
    {
        return -3;
    }

    // !!! 妙啊
    newnode->next->prev = newnode;
    newnode->prev->next = newnode;

    return 0;
}

static struct llist_node_st *find_(LLIST *ptr, const void *key, llist_cmp *cmp)
{
    struct llist_node_st *cur;

    for (cur = ptr->head.next; cur != &ptr->head; cur = cur->next)
    {
        if (0 == cmp(key, cur->data))
            break;
    }

    return cur;   // 找不到的时候，返回的cur就是ptr，返回NULL
}

void *llist_find(LLIST *ptr, const void *key, llist_cmp *cmp)
{
    struct llist_node_st *node;
    node = find_(ptr, key, cmp);
    if (node == &ptr->head)
        return NULL;

    return node->data;
}

int llist_delete(LLIST *ptr, const void *key, llist_cmp *cmp)
{
    struct llist_node_st *node;

    node = find_(ptr, key, cmp);
    if (node == &ptr->head)
        return -1;

    // !!!
    node->prev->next = node->next;
    node->next->prev = node->prev;
    free(node);
    return 0;
}

int llist_fetch(LLIST *ptr, const void *key, llist_cmp *cmp, void *data)
{
    struct llist_node_st *node;

    node = find_(ptr, key, cmp);
    if (node == &ptr->head)
        return -1;

    node->next->prev = node->prev;
    node->prev->next = node->next;

    if (data != NULL)
        memcpy(data, node->data, ptr->size);

    free(node);

    return 0;
}

void llist_travel(LLIST *ptr, llist_op *op)
{
    struct llist_node_st *cur;

    for (cur = ptr->head.next; cur != &ptr->head; cur = cur->next)
        op(cur->data);
}

void llist_destroy(LLIST *ptr)
{
    struct llist_node_st *cur, *next;

    for (cur = ptr->head.next; cur != &ptr->head; cur = next)
    {
        next = cur->next;
        free(cur);
    }

    free(ptr);
}
