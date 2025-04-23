#include <glob.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define DELIMS " \t\n"

struct cmd_st
{
    glob_t globres;
};


static void prompt(void)
{
    printf("mysh-0.1$ ");
}


/**
 * @brief    解析命令行
 * @details
 *           line 不加 const 是考虑以后可能加 alias 功能
 *
 * @param    line
 * @param    res
 */
static void parse(char *line, struct cmd_st *res)
{
    char *tok;
    int   i = 0;

    //* 根据分隔符分割小串
    // strtok();
    while (1)
    {
        tok = strsep(&line, DELIMS);
        if (NULL == tok)
            break;

        if ('\0' == tok[0])   // 判断是否为空串
            continue;

        // 用glob nocheck 来解析
        // 用 i 来让第一次不追加
        glob(tok, GLOB_NOCHECK | GLOB_APPEND * i, NULL, &res->globres);
        i = 1;
    }
}

int main(int argc, char **argv)
{
    char         *linebuf      = NULL;
    size_t        linebuf_size = 0;
    struct cmd_st cmd;
    pid_t         pid;

    while (1)
    {
        prompt( );

        if (getline(&linebuf, &linebuf_size, stdin) < 0)
            break;

        parse(linebuf, &cmd);

        if (0)
        {
            /* dosomething */
        }
        else   // 外部命令
        {
            pid = fork( );
            if (pid < 0)
            {
                perror("fork");
                exit(1);
            }

            if (0 == pid)   // child
            {
                execvp(cmd.globres.gl_pathv[0], cmd.globres.gl_pathv);
                perror("execvp");
                exit(1);
            }
            else   // parent
            {
                wait(NULL);
            }
        }
    }

    exit(0);
}