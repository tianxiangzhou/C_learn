#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "llist.h"

#define NAMESIZE 32

struct score_st
{
    int  id;
    char name[NAMESIZE];
    int  math;
    int  chinese;
};

void print_s(const void *record)
{
    const struct score_st *r = record;

    printf("%d %s %d %d\n", r->id, r->name, r->math, r->chinese);
}

int id_cmp(const void *key, const void *record)
{
    const int             *k = key;
    const struct score_st *r = record;

    return (*k - r->id);
}

int name_cmp(const void *key, const void *record)
{
    const char            *k = key;
    const struct score_st *r = record;

    return strcmp(k, r->name);
}


int main( )
{
    LLIST          *handler;
    int             i, ret;
    struct score_st tmp;

    handler = llist_create(sizeof(struct score_st));
    if (NULL == handler)
        exit(1);

    for (i = 0; i < 7; i++)
    {
        tmp.id = i;
        snprintf(tmp.name, NAMESIZE, "std%d", i);
        tmp.math    = rand( ) % 100;
        tmp.chinese = rand( ) % 100;

        ret = handler->insert(handler, &tmp, LLIST_FORWARD);
        if (ret)
            exit(1);
    }

    handler->travel(handler, print_s);



#if 0
    printf("\n\n");

    // int id = 3;
    char *del_name = "std6";

    // ret = llist_delete(handler, &id, id_cmp);
    ret = llist_delete(handler, del_name, name_cmp);
    if (ret)
        printf("llist_deleter failed!\n");

    llist_travel(handler, print_s);



    int              id = 3;
    struct score_st *data;

    data = llist_find(handler, &id, id_cmp);
    if (NULL == data)
        printf("Can not find!\n");
    else
        print_s(data);

#endif


    llist_destroy(handler);

    exit(0);
}