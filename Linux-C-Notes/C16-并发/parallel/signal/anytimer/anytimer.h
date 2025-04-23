/********************************************************************
 * @file     anytimer.h
 * @brief
 *           单一计时器实现任意数量定时器
 * @author   lzy (lllzzzyyy@buaa.edu.cn)
 * @url      https://lzyyyyyy.fun
 *
 * @date     2024-05-27
 *
 ********************************************************************/

#ifndef __ANYTIMER__H__
#define __ANYTIMER__H__

#define JOB_MAX 1024
typedef void at_jobfunc_t(void *);

/********************************************************************
 * @brief    创建定时器
 * @details
 * @param    sec
 * @param    jobp
 * @param    arg
 * @return   int
 *       >= 0         成功，返回定时器ID
 *       == -EINVAL   失败，参数错误
 *       == -ENOMEM   失败，内存不足
 *       == -ENOSPC   失败，数组满
 ********************************************************************/
int at_addjob(int sec, at_jobfunc_t *jobp, void *arg);

/********************************************************************
 * @brief    取消定时器
 * @details
 * @param    id
 * @return   int
 *       == 0           成功，定时器已取消
 *       == -EINVAL     失败，参数错误
 *       == -EBUSY      失败，指定任务已完成
 *       == -ECANCELED  失败，定时器重复取消
 ********************************************************************/
int at_canceljob(int id);

/*********************************************************************
 * @brief    回收任务
 * @details
 * @param    id
 * @return   int
 *       == 0           成功，任务已回收
 *       == -EINVAL     失败，参数错误
 ********************************************************************/
int at_waitjob(int id);

int at_pausejob(int id);
int at_resumejob(int id);

#endif   //!__ANYTIMER__H__