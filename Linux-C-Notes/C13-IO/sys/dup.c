#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FNAME "/tmp/out"

int main(int argc, char **argv)
{
  int fd;

  /***
   * bug:
   * 1. 假如默认没有1，这里有bug。
   * 2. 假如这个非原子操作的操作的过程，有可能被别的进程影响。
   */
  fd = open(FNAME, O_WRONLY | O_CREAT | O_TRUNC, 0600);
  if (fd < 0)
  {
    perror("open");
    exit(1);
  }

  // close(1);
  // dup(fd);
  dup2(fd, 1);
  // 使用 dup2 原子操作
  // 且dup2如果两个参数相等，不会做任何事

  // !!!
  if (1 != fd)
    close(fd);

#if 0
    close(1);

    fd = open(FNAME, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd < 0)
    {
        perror("open");
        exit(1);
    }
#endif

  /********************************************************************/
  puts("hello!");

  // TODO: 将sdtout回到终端

  exit(0);
}
