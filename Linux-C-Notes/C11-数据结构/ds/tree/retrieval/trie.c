#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DESC_SIZE 256
#define KEY_SIZE  256
#define BUFSIZE   512
#define FNAME     "log"

struct node_st
{
    struct node_st *ch[26];
    char            desc[DESC_SIZE];
};

static int get_word(FILE *fp, char *key, char *desc)
{
    char  buf[BUFSIZE];
    char *retp;
    int   i, j;

    retp = fgets(buf, BUFSIZE, fp);
    if (NULL == retp)
        return -1;

    for (i = 0; i < KEY_SIZE - 1 && buf[i] != ':'; i++)
        key[i] = buf[i];
    key[i] = '\0';

    i++;

    for (j = 0; j < DESC_SIZE - 1 && buf[i] != '\0'; j++, i++)
        desc[j] = buf[i];
    desc[j] = '\0';

    return 0;
}

static struct node_st *newnode( )
{
    struct node_st *node;
    int             i;

    node = malloc(sizeof(*node));
    if (NULL == node)
        return NULL;

    node->desc[0] = '\0';

    for (i = 0; i < 26; i++)
        node->ch[i] = NULL;

    return node;
}

static int insert(struct node_st **root, char *key, char *desc)
{
    if (NULL == *root)
    {
        *root = newnode( );
        if (NULL == *root)
            return -1;
    }

    if ('\0' == *key)
    {
        strcpy((*root)->desc, desc);
        return 0;
    }

    return insert((*root)->ch + *key - 'a', key + 1, desc);
}

static char *find(struct node_st *root, char *key)
{
    if (NULL == root)
        return NULL;

    if ('\0' == *key)
        return root->desc;

    return find(root->ch[*key - 'a'], key + 1);
}

int main( )
{
    struct node_st *tree;
    FILE           *fp;
    char            desc[DESC_SIZE] = {'\0'}, key[KEY_SIZE] = {'\0'};
    int             ret;
    char           *datap;

    fp = fopen(FNAME, "r");
    if (NULL == fp)
    {
        fprintf(stderr, "fopen():error!\n");
        exit(1);
    }

    while (1)
    {
        ret = get_word(fp, key, desc);
        if (-1 == ret)
            break;

        // puts(key);
        // puts(desc);

        insert(&tree, key, desc);
    }

    datap = find(tree, "donkey");
    if (NULL == datap)
        printf("Can not find!\n");
    else
        puts(datap);

    fclose(fp);

    exit(0);
}