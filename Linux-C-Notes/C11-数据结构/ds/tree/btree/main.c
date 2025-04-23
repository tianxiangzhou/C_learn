#include <stdio.h>
#include <stdlib.h>

#include <queue.h>

#define NAMESIZE 32

struct score_st
{
    int  id;
    char name[NAMESIZE];
    int  math;
    int  chinese;
};

struct node_st
{
    struct score_st data;
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
static int insert(struct node_st **root, struct score_st *data)
{
    struct node_st *node;

    if (NULL == *root)
    {
        node = malloc(sizeof(*node));
        if (NULL == node)
            return -1;

        node->data = *data;
        node->l    = NULL;
        node->r    = NULL;

        *root = node;
        return 0;
    }

    if (data->id <= (*root)->data.id)
        return insert(&(*root)->l, data);
    return insert(&(*root)->r, data);
}


struct score_st *find(struct node_st *root, int id)
{
    if (NULL == root)
        return NULL;

    if (id == root->data.id)
        return &root->data;

    if (id < root->data.id)
        return find(root->l, id);
    return find(root->r, id);
}

static void print_s(struct score_st *d)
{
    printf("%d %s %d %d\n", d->id, d->name, d->math, d->chinese);
}


static void draw_(struct node_st *root, int level)
{
    if (NULL == root)
        return;

    draw_(root->r, level + 1);

    for (int i = 0; i < level; i++)
        printf("    ");
    print_s(&root->data);

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

    // getchar();
}


/**
 * @brief    计算某个节点的节点总个数
 * @details
 *
 * @param    root
 * @return  int
 */
static int get_num(struct node_st *root)
{
    if (NULL == root)
        return 0;

    return get_num(root->l) + get_num(root->r) + 1;
}


static struct node_st *find_min(struct node_st *root)
{
    if (NULL == root->l)
        return root;

    return find_min(root->l);
}


/**
 * @brief    左旋
 * @details
 *
 * @param    root
 */
static void turn_left(struct node_st **root)
{
    struct node_st *cur = *root;

    *root  = cur->r;
    cur->r = NULL;

    find_min(*root)->l = cur;

    // draw(tree);
}


static struct node_st *find_max(struct node_st *root)
{
    if (NULL == root->r)
        return root;

    return find_min(root->r);
}


/**
 * @brief    右旋
 * @details
 *
 * @param    root
 */
static void turn_right(struct node_st **root)
{
    struct node_st *cur = *root;

    *root  = cur->l;
    cur->l = NULL;

    find_max(*root)->r = cur;

    // draw(tree);
}



/**
 * @brief    平衡
 * @details
 *
 * @param    root
 */
static void balance(struct node_st **root)
{
    if (NULL == *root)
        return;

    int sub;

    while (1)
    {
        sub = get_num((*root)->l) - get_num((*root)->r);

        if (sub >= -1 && sub <= 1)
            break;
        if (sub < -1)
            turn_left(root);
        if (sub > 1)
            turn_right(root);
    }

    balance(&(*root)->l);
    balance(&(*root)->r);
}


/**
 * @brief    删除某个节点
 * @details
 *           左子树顶上来
 *
 * @param    root
 * @param    tmpid
 */
static void delete(struct node_st **root, int id)
{
    struct node_st **node = root;
    struct node_st  *cur;

    while (*node != NULL && (*node)->data.id != id)
    {
        if (id < (*node)->data.id)
            node = &(*node)->l;
        else
            node = &(*node)->r;
    }

    if (NULL == *node)
        return;

    cur = *node;

    if (NULL == cur->l)
        *node = cur->r;
    else
    {
        *node               = cur->l;
        find_max(cur->l)->r = cur->r;
    }

    free(cur);
}


#if 0
/**
 * @brief    前序遍历
 * @details
 *           中序和后序改一改输出顺序就行
 *
 * @param    root
 */
static void travel(struct node_st *root)
{
    if (NULL == root)
        return;
    print_s(&root->data);

    travel(root->l);

    travel(root->r);
}
#endif


/**
 * @brief    按层遍历
 * @details
 *           使用一个队列存储同一层
 *
 * @param    root
 */
static void travel(struct node_st *root)
{
    if (NULL == root)
        return;

    int             ret;
    QUEUE          *qu;
    struct node_st *cur;

    qu = queue_create(sizeof(struct node_st *));
    if (NULL == qu)
        return;

    queue_en(qu, &root);
    /* if error */

    while (1)
    {
        ret = queue_de(qu, &cur);
        if (-1 == ret)
            break;

        print_s(&cur->data);

        if (NULL != cur->l)
            queue_en(qu, &cur->l);

        if (NULL != cur->r)
            queue_en(qu, &cur->r);
    }

    queue_destroy(qu);
}

int main( )
{
    int             arr[] = {1, 2, 3, 7, 6, 5, 9, 8, 4};
    int             i;
    struct score_st tmp, *datap;

    for (i = 0; i < sizeof(arr) / sizeof(*arr); i++)
    {
        tmp.id = arr[i];
        snprintf(tmp.name, NAMESIZE, "stu%d", arr[i]);
        tmp.math    = rand( ) % 100;
        tmp.chinese = rand( ) % 100;

        /* 小往左，大往右 */
        insert(&tree, &tmp);
    }

    draw(tree);

    printf("\n\n");

    balance(&tree);

    draw(tree);

    printf("\n\n");

    travel(tree);

#if 0
    int tmpid = 5;
    delete (&tree, tmpid);

    draw(tree);
#endif

#if 0
    int tmpid = 2;
    datap     = find(tree, tmpid);
    if (NULL == datap)
        printf("Can not find the id %d\n", tmpid);
    else
        print_s(datap);
#endif

    exit(0);
}