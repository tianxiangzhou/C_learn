#include <stdio.h>
#include <stdlib.h>

#include "sqlist.h"

int main( )
{
    sqlist *list  = NULL;
    sqlist *list1 = NULL;

    datatype arr[]  = {12, 23, 34, 45, 56};
    datatype arr1[] = {89, 90, 78, 67, 56, 43};

    int i, err;

    list = sqlist_create( );
    // sqlist_create1(&list);
    if (NULL == list)
    {
        fprintf(stderr, "sqlist_create() failed!\n");
        exit(1);
    }

    list1 = sqlist_create( );
    if (NULL == list1)
    {
        fprintf(stderr, "sqlist_create() failed!\n");
        exit(1);
    }


    for (i = 0; i < sizeof(arr) / sizeof(*arr); i++)
    {
        // !!! '=' 的优先级低于 '!='
        if ((err = sqlist_insert(list, 0, &arr[i])) != 0)
        {
            if (-1 == err)
                fprintf(stderr, "The arr is full.\n");
            else if (-2 == err)
                fprintf(stderr, "The pos you want to insert is wrong.\n");
            else
                fprintf(stderr, "Error!\n");
            exit(1);
        }
    }

    for (i = 0; i < sizeof(arr1) / sizeof(*arr1); i++)
    {
        // !!! '=' 的优先级低于 '!='
        if ((err = sqlist_insert(list1, 0, &arr1[i])) != 0)
        {
            if (-1 == err)
                fprintf(stderr, "The arr is full.\n");
            else if (-2 == err)
                fprintf(stderr, "The pos you want to insert is wrong.\n");
            else
                fprintf(stderr, "Error!\n");
            exit(1);
        }
    }

    // !!! 用打印行号排查段错误
    // printf("%d\n", __LINE__);
    sqlist_display(list);
    sqlist_display(list1);

    sqlist_union(list, list1);
    sqlist_display(list);



#if 0
    sqlist_delete(list, 1);
    sqlist_display(list);
#endif

    sqlist_destroy(list);
    sqlist_destroy(list1);

    exit(0);
}