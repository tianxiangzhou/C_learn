#include <stdio.h>
#include <stdlib.h>


#define FNAME "/tmp/out"


struct node_st
{
    char            data;
    struct node_st *l, *r;
};


struct node_st *tree = NULL;

/**
 * @brief    插入节点
 * @details
 *           小左大右
 *
 *       !!! 为什么要传入二级指针
 *       !!! 因为你可能改变的是根节点自身，不仅仅是改变根节点指向的值。
 *       !!! 要改变一级指针本身，就需要传入二级指针。
 *
 * @param    root
 * @param    data
 * @return  int
 */
static int insert(struct node_st **root, int data)
{
    struct node_st *node;

    if (NULL == *root)
    {
        node = malloc(sizeof(*node));
        if (NULL == node)
            return -1;

        node->data = data;
        node->l    = NULL;
        node->r    = NULL;

        *root = node;
        return 0;
    }

    if (data <= (*root)->data)
        return insert(&(*root)->l, data);
    return insert(&(*root)->r, data);
}


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


static int save_(struct node_st *root, FILE *fp)
{
    fputc('(', fp);
    /* if error */

    if (NULL == root)
    {
        fputc(')', fp);
        return 0;
    }

    fputc(root->data, fp);
    /* if error */

    save_(root->l, fp);
    save_(root->r, fp);

    fputc(')', fp);
    /* if error */
}

static int save(struct node_st *root, const char *path)
{
    FILE *fp;
    fp = fopen(path, "w");
    if (NULL == fp)
        return -1;

    save_(tree, fp);

    fputc('\n', fp);

    fclose(fp);

    return 0;
}

int main( )
{
    char             arr[] = "cefadjbh";
    int              i;
    struct score_st *datap;

    for (i = 0; i < sizeof(arr) / sizeof(*arr) - 1; i++)
    {
        /* 小往左，大往右 */
        insert(&tree, arr[i]);
    }

    draw(tree);

    save(tree, FNAME);

    exit(0);
}