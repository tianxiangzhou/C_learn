#include <stdio.h>
#include <stdlib.h>

#include "nohead.h"

int main( )
{
    int             i, ret;
    struct node_st *list = NULL;
    struct score_st tmp;

    for (i = 0; i < 7; i++)
    {
        tmp.id = i;
        snprintf(tmp.name, NAMESIZE, "stu%d", i);
        tmp.math    = rand( ) % 100;
        tmp.chinese = rand( ) % 100;

        // list = list_insert(list, &tmp);
        ret = list_insert(&list, &tmp);
        if (0 != ret)
            exit(1);
    }


    list_show(list);

    printf("\n\n");

    int              id = 13;
    struct score_st *ptr;
    ptr = list_find(&list, id);
    if (NULL == ptr)
        printf("Can not find!\n");
    else
        printf("%d %s %d %d", ptr->id, ptr->name, ptr->math, ptr->chinese);


#if 0
    list_delete(&list);

    list_show(list);
#endif

    list_destroy(&list);

    exit(0);
}