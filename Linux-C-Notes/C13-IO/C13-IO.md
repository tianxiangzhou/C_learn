# 目录

- [目录](#目录)
- [I/O操作](#io操作)
  - [标准IO](#标准io)
  - [文件IO/系统调用IO](#文件io系统调用io)
    - [文件描述符的概念](#文件描述符的概念)
    - [文件IO操作相关函数](#文件io操作相关函数)
    - [例题：通过文件IO处理csv表格](#例题通过文件io处理csv表格)
    - [文件IO与标准IO的区别](#文件io与标准io的区别)
    - [IO的效率问题](#io的效率问题)
      - [习题](#习题)
      - [解答](#解答)
      - [结果](#结果)
    - [文件共享](#文件共享)
    - [原子操作](#原子操作)
    - [程序中的重定向：`dup`, `dup2`](#程序中的重定向dup-dup2)
    - [同步](#同步)
    - [/dev/fd/目录](#devfd目录)

# I/O操作

输入输出是一切实现的基础。

- 标准IO：`stdio`

- 系统调用IO（文件IO）：`sysio`

优先使用**标准IO**，兼容性更好，还有合并系统调用的优势。

## 标准IO

```c
/* stdio */
/* FILE类型贯穿始终 */

FILE *fopen(const char *path, const char *mode);
/**
 * fopen 返回指针的储存位置？ 1.栈  2.静态区  3.堆
 * 正确答案：3.堆。
 * 因为如果是栈，就是函数内部局部变量，无法返回地址。
 * 如果是静态区，无法确定需要多少个这个变量。
 * 
 * 只有 r 和 r+ 一定要求文件存在
 * 另外几种不存在会创建
 * 
 * 创建文件的权限
 * 0666 & ~umask
 * 
 * 对于普通用户
 * umask 得到 022
 * 
*/
int fclose(FILE *fp);

int fputc(int c, FILE *stream);
int fgetc(FILE *stream);

char *fgets(char *s, int size, FILE *stream);
/**
 * 两种正常返回的情况：
 * 1. 读了 size-1 个字节，最后一个字节留给 '\0'
 * 2. 读到了 '\n'
 * 
 * eg. 加入用fgets(buf, 5, stream) 来读 abcd
 * 是会读两次的
 * 第一次：abcd'\0'
 * 第二次：'\n''\0'
*/
int fputs(const char *restrict s, FILE *restrict stream);

/**
 * 这一对函数常用但是无法验证边界
 * 尽量一次只读单字节，更安全
 * 
 * 返回值：成功读/写的对象的数量
*/
size_t fread(void *ptr, size_t size, size_t nemmb, FILE *stream);
size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);


int printf(const char *restrict format, ...);
/**
 * 常用于 fprintf(stderr,...)
*/
int fprintf(FILE *restrict stream, const char *restrict format, ...);
int dprintf(int fd, const char *restrict format, ...);

/**
 * 将格式化内容输出到一个字符串
 * 
 * 和 atoi() 正好相反
 * 
*/
int sprintf(char *restrict str, const char *restrict format, ...);

/**
 * 比sprintf多了size参数，更安全
*/
int snprintf(char   str[restrict.size],
             size_t size,
             const char *restrict format,
             ...)

// !!! 慎用%s
int scanf(const char *restrict format, ...);
int fscanf(FILE *restrict stream,
                  const char *restrict format, ...);


/**
 * 移动文件当前位置指针
 * 
 * 可用于生成空洞文件，下载器原理
 * 
 * @prarm: offset 移动多远
 * @prarm: whence 移动方向
 *         SEEK_SET, SEEK_CUR, SEEK_END
 * 
 * @return  成功0，失败-1
*/
int fseek(FILE *stream, long offset, int whence);

/**
 * 反映当前文件指针所在位置
 * 
 * 这个long的负值部分无法使用。
 * 所以文件无法超过2G。
 * 
*/
long ftell(FILE *stream);

/**
 * 解决上面long的问题。
 * 
 * 最好编译时加上
 * #define _FILE_OFFSET_BITS 64
 * 可以写入makefile
 * 
 * 但是这俩函数是方言，前面那个long的一对支持C89，C99
 * 
*/
int fseeko(FILE *stream, off_t offset, int whence);
off_t ftello(FILE *stream);

/**
 * 将文件指针置于文件首 
 * equivalent to:
 * fseek(stream, 0L, SEEK_SET);
*/
void rewind(FILE *stream);

/**
 *  缓冲区的作用：
 *     大多数情况下是好事，合并系统调用
 * 
 * 行缓冲： 换行时候刷新，满了的时候刷新，强制刷新（标准输出是这样的，因为是终端设备）
 * 
 * 全缓冲： 满了的时候刷新，强制刷新（默认，只要不是终端设备）
 * 
 * 无缓冲： 如stderr，需要立即输出的内容
*/
fflush();

/**
 * @prarm: mode
 * 三种缓冲模式: 
 *            _IONBF
 *            _IOLBF
 *            _IOFBF
*/
int setvbuf(FILE *stream, char *buf, int mode, size_t size);

/**
 * 为了读取一行
 * 
 * 使用办法：
 *   #define _GNU_SOURCE  这个不想写到代码里面的话可以写到makefile
 *   eg. CFLAGS+=-D_FILE_OFFSET_BITS=64 -D_GNU_SOURCE
 *   #include <stdio.h>
 * 
 * !!! 里面有 malloc 动作，未释放
 * !!! 是方言，可以自己封装一个mygetline和mygetline_free
 * !!! 但是根据chatgpt，好像直接 free(*lineptr) 就行了
 * 
*/
ssize_t getline(char **lineptr, size_t *n, FILE *stream);

/**
 * 临时文件
 *       1. 如何不冲突的创建
 *       2. 及时销毁
 * 
 * tmpnam: 创建临时文件名字
 *         有并发危险，因为产生名字和创建文件是两步
 * 
 * tmpfile: 创建临时文件
 *          是匿名文件，ls -a 都看不到
 *          避免冲突
*/
char *tmpnam(char *s);
FILE *tmpfile(void);

```

## 文件IO/系统调用IO

文件描述符（`fd`）是在文件IO中贯穿始终的类型。

### 文件描述符的概念

是一个整型数，是一个指针数组的下标。

优先使用当前可用范围内最小的。

### 文件IO操作相关函数

- `open`
- `close`
- `read`
- `write`
- `lsee`

可以使用`./open file &`来后台运行一个程序。

然后通过`ps`查看进程号

然后进入`/proc/进程号/fd`查看文件描述符

前三个是标准输入、输出、错误，后面的是打开的文件描述符

```c
/**
 * flag:
 *
 * r  -> O_RDONLY
 * r+ -> O_RDWR
 * w  -> O_WRONLY | O_CREAT | O_TRUNC
 * w+ -> O_RDWR   | O_TRUNC | O_CREAT
 *
 * O_RDONLY     只读
 * O_WRONLY     只写
 * O_RDWR       读写
 * O_CREAT      创建
 * O_TRUNC      截断
 * O_APPEND     追加
 * O_EXCL       排他(若要创建的文件已存在则报错)
 * O_NONBLOCK   非阻塞
 * O_SYNC       同步
 * O_DSYNC      数据同步
 * O_RSYNC      读同步
 * O_DIRECT     直接IO
 * O_LARGEFILE  大文件
 * O_DIRECTORY  目录
 * O_NOFOLLOW   不跟踪符号链接
 * O_CLOEXEC    close-on-exec
 * O_PATH       仅打开目录
 * O_TMPFILE    临时文件
 * O_NOCTTY     不分配控制终端
 * 
 * 如果有creat就必须用三参数的形式
 * C语言没有重载，这是变参函数
 * 
 * @prarm: pathname 文件路径
 * @prarm: flags    文件打开方式
 * @prarm: mode     文件权限
 *                  假如0666，就是rw-rw-rw-，110110110
 * 
*/
int open(const char *pathname, int flags);
int open(const char *pathname, int flags, mode_t mode);

int close(int fd);

/**
 * @return 读取的字节数，失败返回-1
*/
ssize_t read(int fd, void *buf, size_t count);

/**
 *  想要控制写入的位置，需要使用lseek
 * 
 * @return 写入的字节数，失败返回-1
*/
ssize_t write(int fd, const void *buf, size_t count);

/**
 *  移动文件指针
 * 
 * @prarm: offset 移动多远
 * @prarm: whence 移动方向
 *         SEEK_SET, SEEK_CUR, SEEK_END
 * 
 * @return  成功0，失败-1
*/
off_t lseek(int fd, offt offset, int whence);

```

### 例题：通过文件IO处理csv表格

```csv
,语文,数学,英语,总分,评价
张三,90,91,92,,
李四,80,81,82,,
王五,70,71,72,,
```

思路：逐行处理

可以使用16进制查看工具

### 文件IO与标准IO的区别

区别：响应速度&吞吐量

文件IO需要频繁进入内核，标准IO通过缓冲区合并系统调用。

响应速度快就文件IO，吞吐量大就标准IO。

> [!warning]
> 二者不可混用

转换方法：`fileno`, `fdopen`

### IO的效率问题

#### 习题

将`mycpy.c`程序进行更改，将`BUFSIZE`的值放大，观察进程消耗的时间，注意性能出现拐点的值以及程序何时段错误。

#### 解答

将`BUFSIZE`作为命令行参数传入，`int bufsize = atoi(argv[3]);`

通过脚本进行试验：

```bash
#!/bin/bash

# 生成一个 5GB 的文件
dd if=/dev/urandom of=/tmp/bigfile bs=1G count=5

# 输入和输出文件的路径
src="/tmp/bigfile"
dst="/tmp/outfile"

# 编译你的程序
gcc -o mycpy_bufsize mycpy_bufsize.c

# 初始化 BUFSIZE
bufsize=512

# 循环，每次 BUFSIZE * 2
while true; do
  # 用 time 命令运行你的程序，并将结果重定向到一个临时文件
  { time ./mycpy_bufsize $src $dst $bufsize; } 2> time.txt
  
  # 检查程序的退出状态
  if [ $? -ne 0 ]; then
    echo "Max BUFSIZE before segfault: $bufsize"
    break
  fi

  # 提取 time 的结果
  real_time=$(grep real time.txt | awk -F' ' '{print $2}')
  user_time=$(grep user time.txt | awk -F' ' '{print $2}')
  sys_time=$(grep sys time.txt | awk -F' ' '{print $2}')

  # 输出 BUFSIZE 和 time 的结果
  echo "BUFSIZE: $bufsize, Real Time: $real_time, User Time: $user_time, Sys Time: $sys_time"
  
  # BUFSIZE * 2
  bufsize=$((bufsize * 2))
done

# 删除临时文件
rm time.txt
rm $src
rm $dst

```

#### 结果

```bash
wan@SK-20240106UQUX:~/Linux-C-Notes/C13-Linux系统编程/io/sys$ ./time.sh
BUFSIZE: 512, Real Time: 0m7.672s, User Time: 0m0.650s, Sys Time: 0m7.007s
BUFSIZE: 1024, Real Time: 0m5.026s, User Time: 0m0.201s, Sys Time: 0m4.651s
BUFSIZE: 2048, Real Time: 0m3.535s, User Time: 0m0.158s, Sys Time: 0m3.183s
BUFSIZE: 4096, Real Time: 0m2.418s, User Time: 0m0.059s, Sys Time: 0m2.232s
BUFSIZE: 8192, Real Time: 0m2.363s, User Time: 0m0.040s, Sys Time: 0m2.150s
BUFSIZE: 16384, Real Time: 0m2.279s, User Time: 0m0.030s, Sys Time: 0m2.079s
BUFSIZE: 32768, Real Time: 0m2.238s, User Time: 0m0.020s, Sys Time: 0m2.026s
BUFSIZE: 65536, Real Time: 0m2.114s, User Time: 0m0.000s, Sys Time: 0m1.972s
BUFSIZE: 131072, Real Time: 0m2.302s, User Time: 0m0.019s, Sys Time: 0m1.982s
BUFSIZE: 262144, Real Time: 0m2.244s, User Time: 0m0.000s, Sys Time: 0m2.016s
BUFSIZE: 524288, Real Time: 0m2.254s, User Time: 0m0.000s, Sys Time: 0m2.039s
BUFSIZE: 1048576, Real Time: 0m2.249s, User Time: 0m0.010s, Sys Time: 0m2.037s
BUFSIZE: 2097152, Real Time: 0m2.304s, User Time: 0m0.000s, Sys Time: 0m2.108s
BUFSIZE: 4194304, Real Time: 0m2.234s, User Time: 0m0.010s, Sys Time: 0m2.082s
Max BUFSIZE before segfault: 8388608
```

在`ulimit -a`中，我的系统的`stack size`是`8192`，所以`BUFSIZE`不能超过`8192`，否则会段错误。与测试结果一致。

### 文件共享

多个任务共同操作一个文件或者协同完成任务

面试题：写程序删除一个文件的第10行

补充函数：

```c
// 截断文件到某长度
int truncate(const char *path, off_t length);
int ftruncate(int fd, off_t length);
```

```c
// 最简单思路，将11行开始的内容到第10行开始处覆盖写
while()
{
    lseek 11 + read +lseek 10 + write
}

// 优化思路，两个文件描述符，一个读一个写
1 -> open r  -> fd1 -> lseek 11
2 -> open r+ -> fd2 -> lseek 10

while()
{
    1->fd1-> read
    2->fd2-> write
}

// 两个进程, 设计进程间通信
process1 -> open -> r
process2 -> open -> r+

p1->read -> p2->write

```

答案源码：

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define BUFFER_SIZE 4096

int delete_line(const char* filename, int line_to_delete) {
    int fd_read, fd_write;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    off_t read_offset = 0, write_offset = 0;
    int current_line = 1;
    
    // 打开文件用于读取
    fd_read = open(filename, O_RDONLY);
    if (fd_read == -1) {
        perror("无法打开文件进行读取");
        return -1;
    }
    
    // 打开文件用于写入
    fd_write = open(filename, O_RDWR);
    if (fd_write == -1) {
        perror("无法打开文件进行写入");
        close(fd_read);
        return -1;
    }
    
    // 计算要删除的行的偏移量
    char ch;
    while (current_line < line_to_delete) {
        if (read(fd_read, &ch, 1) != 1) {
            // 文件行数少于要删除的行
            close(fd_read);
            close(fd_write);
            return -1;
        }
        
        if (ch == '\n') {
            current_line++;
        }
        
        read_offset++;
        write_offset++;
    }
    
    // 找到要删除的行的结束位置
    while (read(fd_read, &ch, 1) == 1) {
        read_offset++;
        if (ch == '\n') {
            break; // 找到行尾
        }
    }
    
    // 从要删除行的下一行开始读取并写入到要删除行的位置
    lseek(fd_read, read_offset, SEEK_SET);
    lseek(fd_write, write_offset, SEEK_SET);
    
    // 读取剩余内容并写入
    while ((bytes_read = read(fd_read, buffer, BUFFER_SIZE)) > 0) {
        if (write(fd_write, buffer, bytes_read) != bytes_read) {
            perror("写入错误");
            close(fd_read);
            close(fd_write);
            return -1;
        }
    }
    
    // 截断文件以删除多余内容
    off_t file_size = lseek(fd_read, 0, SEEK_END);
    if (ftruncate(fd_write, file_size - (read_offset - write_offset)) == -1) {
        perror("截断文件失败");
        close(fd_read);
        close(fd_write);
        return -1;
    }
    
    // 关闭文件
    close(fd_read);
    close(fd_write);
    
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "用法: %s <文件名> <要删除的行号>\n", argv[0]);
        return 1;
    }
    
    int line_to_delete = atoi(argv[2]);
    if (line_to_delete <= 0) {
        fprintf(stderr, "错误: 行号必须是正整数\n");
        return 1;
    }
    
    if (delete_line(argv[1], line_to_delete) != 0) {
        fprintf(stderr, "删除行失败\n");
        return 1;
    }
    
    printf("成功删除第 %d 行\n", line_to_delete);
    return 0;
}
```

### 原子操作

指不可分割的操作

作用：解决竞争和冲突

如`tmpnam`函数，产生文件名和创建文件是两步，会有并发问题。

### 程序中的重定向：`dup`, `dup2`

```c
/**
 *  dup 和 dup2 都是复制文件描述符
 *  dup2 可以指定新的文件描述符
 *  dup 会返回一个新的文件描述符
 */
int dup(int oldfd);
int dup2(int oldfd, int newfd);
```

### 同步

同步内核层面的buffer和cache

```c
void sync(void);
int fsync(int fd);
int fdatasync(int fd); // 只刷新数据，不刷新亚数据

// 文件描述符所有的操作几乎都来源于该函数
int fcntl(int fd, int cmd, ... /* arg */);

// 设备相关的内容
int ioctl(int fd, unsigned long request, ... /* arg */);

```

### /dev/fd/目录

**虚目录**：显示当前进程的文件描述符信息
