#include <stdio.h>
#include <stdlib.h>


#define FNAME "/tmp/out"


struct node_st
{
    char            data;
    struct node_st *l, *r;
};


struct node_st *tree = NULL;


static void draw_(struct node_st *root, int level)
{
    if (NULL == root)
        return;

    draw_(root->r, level + 1);

    for (int i = 0; i < level; i++)
        printf("    ");
    printf("%c\n", root->data);

    draw_(root->l, level + 1);
}

/**
 * @brief    绘制树
 * @details
 *           躺下来，根在左，子节点在右。
 *           这样子，深度即制表符个数。
 *D
 * @param    root
 */
static void draw(struct node_st *root)
{
    draw_(root, 0);

    printf("\n\n");
}

static struct node_st *load_(FILE *fp)
{
    int             c;
    struct node_st *root;

    c = fgetc(fp);
    /* if error */

    if ('(' != c)
    {
        fprintf(stderr, "fgetc():error.\n");
        exit(1);
    }

    c = fgetc(fp);
    if (')' == c)
        return 0;

    root = malloc(sizeof(*root));
    if (NULL == root)
        exit(1);

    root->data = c;
    root->l    = load_(fp);
    root->r    = load_(fp);

    fgetc(fp);
    /* if error */

    return root;
}



static struct node_st *load(const char *path)
{
    FILE           *fp;
    struct node_st *root;

    fp = fopen(path, "r");
    if (NULL == fp)
        return NULL;

    root = load_(fp);

    fclose(fp);

    return root;
}

int main( )
{
    struct node_st *root;

    root = load(FNAME);

    draw(root);

    exit(0);
}