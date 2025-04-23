#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage:...\n");
        exit(1);
    }

    int fd;

    fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd < 0)
    {
        perror("open()");
        exit(1);
    }

    // 生成一个5G的文件
    // !!! 整数溢出
    lseek(fd, 5LL * 1024LL * 1024LL * 1024LL - 1LL, SEEK_SET);

    // 写入尾0
    write(fd, "", 1);

    close(fd);
    exit(0);
}