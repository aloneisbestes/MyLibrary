#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

#include "../common/common.h"
#include <cassert>

/**
 * @brief 
 * ThreadPool: 线程池类，采用单例模式实现
 */
#define THREADPOOL_MAX_NUM 64


class ThreadPool {
public:
    inline ThreadPool(UInt32 size=4) {
        assert(size <= THREADPOOL_MAX_NUM);

    }

    inline ~ThreadPool() {

    }

public:
    static ThreadPool &instance() {
        return __threadpool;
    }

private:
    /**
     * @brief 
     * initThreadPool用于初始化ThreadPool类
     */
    void initThreadPool(UInt32 size) {

    }

private:
    static ThreadPool __threadpool; // 单例线程池

private:
    /* 不允许拷贝构造、赋值、移动构造以及移动赋值 */
    ThreadPool(const ThreadPool &) = delete;
    ThreadPool(ThreadPool &&) = delete;
    ThreadPool &operator=(const ThreadPool &) = delete;
    ThreadPool &operator=(ThreadPool &&) = delete;
};

#endif //__THREAD_POOL_H__