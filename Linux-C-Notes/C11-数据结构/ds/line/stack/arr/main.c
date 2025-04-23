#include <stdio.h>
#include <stdlib.h>

#include "sqstack.h"

int main( )
{
    datatype arr[] = {19, 23, 0, 45, 67};
    sqstack *st;
    int      i;

    st = st_create( );
    if (NULL == st)
        exit(1);

    for (i = 0; i < sizeof(arr) / sizeof(*arr); i++)
        st_push(st, &arr[i]);

    st_travel(st);

    datatype tmp;
    while (0 == st_pop(st, &tmp))
    {
        printf("POP:%d\n", tmp);
    }

#if 0
    datatype tmp = 1;
    int      ret;
    
    ret = st_push(st, &tmp);
    if (0 != ret)
        printf("st_push failed.\n");
    else
        st_travel(st);

    st_destroy(st);
#endif

    exit(0);
}