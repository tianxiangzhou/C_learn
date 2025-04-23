#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#if 1
#    define debug(fmt, args...) printf(fmt, ##args)
#else
#    define debug(fmt, args...)
#endif

/**
 * @brief    读取一行
 * @details
 *           循环读入一个字符
 *           如何判断读完一行? 读到0x0d, 0x0a
 *
 * @param    fd
 * @param    buf
 *
 * @return  int 读到的一行数据的数据个数( n>=0 )
 *              -1: 读到文件尾部或者出错
 */
static int read_line(int fd, unsigned char *buf)
{
    unsigned char c;
    int           len;
    int           i   = 0;
    int           err = 0;

    while (1)
    {
        len = read(fd, &c, 1);
        if (len <= 0)
        {
            err = -1;
            break;
        }
        else
        {
            if (c != '\n' && c != '\r')
            {
                buf[i] = c;
                i++;
            }
            else /* 碰到回车换行 */
            {
                err = 0;
                break;
            }
        }
    }

    buf[i] = '\0';

    if (err && (0 == i))
        /* 读到文件尾部且无有效数据 */
        return -1;
    else
        return i;
}

/**
 * @brief    处理一行的数据, 计算出总分和评价
 * @details
 *
 * @param    data_buf
 * @param    result_buf
 *
 * @return  int
 */
static void process_data(unsigned char *data_buf, unsigned char *result_buf)
{
    /**
     *   eg1: data_buf=",语文,数学,英语,总分,评价"
     *      result_buf=",语文,数学,英语,总分,评价"
     *
     *   eg2: data_buf="张三,90,91,92,,"
     *      result_buf="张三,90,91,92,273,A+"
     *
     */

    char  name[100];
    int   scores[3];
    int   sum;
    char *levels[] = {"A+", "A", "B"};
    int   level;

    // debug("data_buf[0]: %x\n", data_buf[0]);
    if (0xef == data_buf[0]) /* 对于UTF-8, 前三个字符是0xef 0xbb 0xbf */
    {
        strcpy(result_buf, data_buf);
    }
    else
    {
        // debug("data_buf: %s\n", data_buf);
        // debug("进入了\n");
        /**
         * @brief    从字符串得到数据
         * @details
         *           拆分信息: scanf分隔符
         *           %[^,]: 读数据直到碰到逗号
         *
         */
        sscanf(data_buf,
               "%[^,],%d,%d,%d,,",
               name,
               &scores[0],
               &scores[1],
               &scores[2]);

        debug("name: %s, scores: %d, %d, %d\n",
              name,
              scores[0],
              scores[1],
              scores[2]);

        sum = scores[0] + scores[1] + scores[2];
        if (sum >= 270)
            level = 0;
        else if (sum >= 240)
            level = 1;
        else
            level = 2;

        sprintf(result_buf,
                "%s,%d,%d,%d,%d,%s",
                name,
                scores[0],
                scores[1],
                scores[2],
                sum,
                levels[level]);
    }
}


/**
 * @brief    处理csv表格
 * @details
 *           Usage: ./W_process_excel data.csv result.csv
 *
 * @param    argc
 * @param    argv
 *
 * @return  int
 */
int main(int argc, char **argv)
{
    int           fd_data, fd_result;
    int           len;
    unsigned char data_buf[1000];
    unsigned char result_buf[1000];

    if (argc != 3)
    {
        printf("Usage: %s data.csv result.csv\n", argv[0]);
        exit(1);
    }

    fd_data = open(argv[1], O_RDONLY);
    if (fd_data < 0)
    {
        perror("open data.csv");
        exit(1);
    }
    else
        printf("data file fd: %d\n", fd_data);

    fd_result = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_result < 0)
    {
        perror("open result.csv");
        exit(1);
    }
    else
        printf("result file fd: %d\n", fd_result);

    while (1)
    {
        /* 读取1行 */
        len = read_line(fd_data, data_buf);
        if (-1 == len)
            break;

        // if (len != 0)
        //     debug("%s\n\r", data_buf);

        if (len != 0)
        {
            /* 处理1行 */
            process_data(data_buf, result_buf);

            /* 写入结果文件 */
            write(fd_result, result_buf, strlen(result_buf));
            write(fd_result, "\r\n", 2);
        }
    }

    close(fd_data);
    close(fd_result);

    exit(0);
}