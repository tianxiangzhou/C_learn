#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    putchar('a');
    write(1, "b", 1);

    putchar('a');
    write(1, "b", 1);

    putchar('a');
    write(1, "b", 1);

    /**
     * 这里标准IO与文件IO混用
     * 实际输出：
     * bbbaaa
     *
     * 命令 strace
     * 可以跟踪系统调用
     *
     */

    exit(0);
}