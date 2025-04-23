/***********************************************************************
 * @file     mytbf.h
 * @brief
 *           令牌桶库
 *
 * @author   lzy (lllzzzyyy@buaa.edu.cn)
 * @url      https://lzyyyyyy.fun
 *
 * @date     2024-05-26
 *
 ***********************************************************************/
#ifndef __MYTBF__H__
#define __MYTBF__H__

#define MYTBF_MAX 1024
typedef void mytbf_t;

mytbf_t *mytbf_init(int cps, int burst);

int mytbf_fetchtoken(mytbf_t *, int);

int mytbf_returntoken(mytbf_t *, int);

int mytbf_destroy(mytbf_t *);

#endif   //!__MYTBF__H__