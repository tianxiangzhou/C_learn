#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#define PAT "/etc"

/**
 * @brief    解析PAT下文件个数
 * @details
 *
 * @param    argc
 * @param    argv
 *
 * @return  int
 */
int main(int argc, char **argv)
{
    DIR           *dp;
    struct dirent *cur;

    dp = opendir(PAT);
    if (NULL == dp)
    {
        perror("opendir()");
        exit(1);
    }

    // !!! 注意括号
    while ((cur = readdir(dp)) != NULL)
    {
        puts(cur->d_name);
    }

    closedir(dp);

    exit(0);
}