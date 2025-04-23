#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief    用user id获取用户名
 * @details
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
        fprintf(stderr, "Usage: %s <user id>\n", argv[0]);
        exit(1);
    }

    struct passwd *pwdline;

    pwdline = getpwuid(atoi(argv[1]));

    puts(pwdline->pw_name);

    exit(0);
}