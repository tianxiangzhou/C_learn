#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    FILE  *fp;
    char  *linebuf;
    size_t linesize;

    if (argc < 2)
    {
        fprintf(stderr, "Usage...\n");
        exit(1);
    }

    fp = fopen(argv[1], "r");
    if (NULL == fp)
    {
        perror("fopen()");
        exit(1);
    }

    // !!!
    linebuf  = NULL;
    linesize = 0;

    while (1)
    {
        if (getline(&linebuf, &linesize, fp) < 0)
            break;
        printf("%d\n", strlen(linebuf));
        printf("%d\n", linesize);
        // 此时输出linesize值不对，是因为没有初始化
        // 修改后发现，linesize初始值就是120，是后面不够再增加
    }

    // !!!
    free(linebuf);

    fclose(fp);
    exit(0);
}