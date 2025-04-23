#include <crypt.h>
#include <shadow.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * @brief    加密输入的密码并与shadow文件中的密码进行比较
 * @details
 *        !!! compile: gcc check.c -o check -lcrypt
 *        !!! 需要root权限运行
 *
 * @param    argc
 * @param    argv   [in]  用户名
 *
 * @return  int
 */
int main(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage:...\n");
        exit(1);
    }

    char        *input_pass;
    struct spwd *shadowline;
    char        *crypt_pass;

    //* getpass()函数在输入密码时不会回显密码
    input_pass = getpass("PassWord: ");

    //* getspnam()函数通过用户名获取shadow文件中的密码
    shadowline = getspnam(argv[1]);

    //* 加密输入的密码
    crypt_pass = crypt(input_pass, shadowline->sp_pwdp);

    if (0 == strcmp(crypt_pass, shadowline->sp_pwdp))
        puts("OK!");
    else
        puts("Error!");

    exit(0);
}