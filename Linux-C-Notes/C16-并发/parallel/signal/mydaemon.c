#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/syslog.h>
#include <syslog.h>
#include <time.h>
#include <unistd.h>

#define FNAME "/tmp/out"

static FILE *fp;

static int deamonize(void)
{
    pid_t pid;
    int   fd;

    pid = fork( );
    if (pid < 0)
        return -1;

    if (pid > 0)   // parent process
        exit(0);

    fd = open("/dev/null", O_RDWR);
    if (fd < 0)
        return -1;

    dup2(fd, 0);
    dup2(fd, 1);
    dup2(fd, 2);
    if (fd > 2)
        close(fd);

    setsid( );

    chdir("/");   // 防止一直占用某设备
    // umask(0);

    return 0;
}

static void daemon_exit(int s)
{
    // if(SIGINT == s) 可以进行区分处理

    fclose(fp);   // 当多个信号响应同一个函数，可能多次free
    closelog( );
    exit(0);
}

int main(int argc, char **argv)
{
    int              i;
    struct sigaction sa;

    sa.sa_handler = daemon_exit;
    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, SIGQUIT);
    sigaddset(&sa.sa_mask, SIGTERM);
    sigaddset(&sa.sa_mask, SIGINT);
    sa.sa_flags = 0;
    // !! 为了防止重入，对其中一个信号注册时要阻塞另外两个信号
    // 干脆就三个一起阻塞

    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);

    // signal(SIGINT, daemon_exit);
    // signal(SIGQUIT, daemon_exit);
    // signal(SIGTERM, daemon_exit);

    openlog("mydaemon", LOG_PID, LOG_DAEMON);

    if (deamonize( ))
    {
        syslog(LOG_ERR, "daemonize() failed!");
        exit(1);
    }
    else
    {
        syslog(LOG_INFO, "daemonize() success!");
    }

    fp = fopen(FNAME, "w");
    if (fp == NULL)
    {
        syslog(LOG_ERR, "fopen() failed!: %s", strerror(errno));
        exit(1);
    }

    syslog(LOG_INFO, "%s was opened successfully!", FNAME);

    for (i = 0;; i++)
    {
        fprintf(fp, "%d\n", i);
        fflush(fp);   //! 刷新缓冲区
        syslog(LOG_DEBUG, "%d is printed", i);
        sleep(1);
    }

    // 目前守护进程只能异常终止，下面其实无法执行到
    // fclose(fp);
    // closelog( );

    exit(0);
}