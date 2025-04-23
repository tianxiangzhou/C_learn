#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * @brief    实现一个简单的su命令
 * @details
 *           Usage: mysu uid
 *
 * @param    argc
 * @param    argv
 * @return  int
 */
int main(int argc, char **argv)
{
    if (argc < 3)
    {
        fprintf(stderr, "Usage: mysu uid");
        exit(1);
    }

    pid_t pid;

    pid = fork( );
    if (pid < 0)
    {
        perror("fork");
        exit(1);
    }

    if (0 == pid)
    {
        // child process
        setuid(atoi(argv[1]));
        execvp(argv[2], argv + 2);
        perror("execvp");
        exit(1);
    }
    else   // parent process
        wait(NULL);

    exit(0);
}

/**
 *  !!!
 *  此时，执行./mysu 0 cat /etc/shadow 依旧没有权限
 *  su - 切换到 root 用户
 *  通过
 *  chown root mysu && chmod u+s mysu 即可
 *  再回到普通用户，执行./mysu 0 cat /etc/shadow 即可查看 shadow 文件
 */