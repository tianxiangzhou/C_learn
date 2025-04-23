#ifndef LLIST_H__
#define LLIST_H__

#define LLIST_FORWARD  1
#define LLIST_BACKWARD 2

struct llist_node_st
{
    void                 *data;
    struct llist_node_st *prev;
    struct llist_node_st *next;
};

typedef struct
{
    int                  size;
    struct llist_node_st head;
} LLIST;

typedef void llist_op(const void *);
typedef int  llist_cmp(const void *, const void *);

LLIST *llist_create(int initsize);

int llist_insert(LLIST *ptr, const void *data, int mode);

void *llist_find(LLIST *ptr, const void *key, llist_cmp *);

int llist_delete(LLIST *, const void *key, llist_cmp *);

int llist_fetch(LLIST *, const void *key, llist_cmp *, void *data);

void llist_travel(LLIST *ptr, llist_op *op);

void llist_destroy(LLIST *ptr);

#endif
