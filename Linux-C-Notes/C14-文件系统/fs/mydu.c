#include <glob.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#define PATHSIZE 1024

static int path_noloop(const char *path)
{
    char *pos;

    /**
     * @brief    strrchr
     * @details
     *
     *           找到 path 中最后一个 '/' 字符的位置
     */
    pos = strrchr(path, '/');
    if (NULL == pos)
        exit(1);

    if ((0 == strcmp(pos + 1, ".") || 0 == strcmp(pos + 1, "..")))
        return 0;

    return 1;
}

static int64_t mydu(const char *path)
{
    // 优化递归
    // 将部分与递归无关的变量拿出栈，用 static 修饰
    static struct stat statres;
    static char        nextpath[PATHSIZE];
    glob_t             globres;
    int64_t            sum;
    int                i;

    if (lstat(path, &statres) < 0)
    {
        perror("lstat()");
        exit(1);
    }

    if (!S_ISDIR(statres.st_mode))
    {
        /* 非目录 */
        return statres.st_blocks;
        /*
         * st_blocks 代表磁盘块数量，一个磁盘块大小为512字节
         * 所以除以2才表示多少个1k字节
         */
    }

    /* 目录 */
    /* 例如：/aaa/bbb/ccc/ddd/eee/fff */

    strncpy(nextpath, path, PATHSIZE);
    strncat(nextpath, "/*", PATHSIZE);   //[W]
    // if (glob(nextpath, 0, NULL, &globres))
    // {
    //     perror("glob(), 1");
    //     exit(1);
    // }
    glob(nextpath, 0, NULL, &globres);

    // !!! 要考虑 . 和 .. 目录
    strncpy(nextpath, path, PATHSIZE);
    strncat(nextpath, "/.*", PATHSIZE);   //[W]
    /*
     * 这个警告是因为 strncat 函数的第三个参数（即 PATHSIZE）等于目标字符串
     * nextpath 的大小。这可能会导致 nextpath 缓冲区溢出，因为 strncat
     * 函数会在目标字符串的末尾添加一个 null 字符（'\0'）。
     */

    // !!! APPEND
    // if (glob(nextpath, GLOB_APPEND, NULL, &globres))
    // {
    //     perror("glob(), APPEND");
    //     exit(1);
    // }
    glob(nextpath, GLOB_APPEND, NULL, &globres);

    sum = statres.st_blocks;

    for (i = 0; i < globres.gl_pathc; i++)
    {
        if (path_noloop(globres.gl_pathv[i]))
        {
            sum += mydu(globres.gl_pathv[i]);
        }
    }

    // !!!
    globfree(&globres);
    return sum;
}

/**
 * @brief    mydu
 * @details
 *           Usage: mydu [FILE]...
 *
 *           用到了递归的思想
 *
 *           !!! 未考虑权限问题
 *
 * @param    argc
 * @param    argv
 *
 * @return  int
 */
int main(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: mydu [FILE]...\n");
        exit(1);
    }

    printf("%lld\n", mydu(argv[1]) / 2);

    exit(0);
}