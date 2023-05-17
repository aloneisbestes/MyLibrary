#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

#include "../common/common.h"
#include <cassert>
#include <mutex>
#include <queue>
#include <thread>
#include <condition_variable>
#include <functional>
#include <future>


/**
 * @brief 
 * ThreadPool: 线程池类，采用单例模式实现
 */
#define THREADPOOL_MAX_NUM 64


class ThreadPool {
public:
    inline ThreadPool(UInt32 size=4): m_stop(false){
        assert(size <= THREADPOOL_MAX_NUM);
        initThreadPool(size);
    }

    inline ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_stop = true;
        }

        m_condition.notify_all();
        for (std::thread &worker : m_workers) {
            worker.join();
        }
    }

public:
    static ThreadPool *instance() {
        static ThreadPool *__threadpool = new ThreadPool;
        return __threadpool;
    }
    
    virtual void workerFunction() {
        while (true) {
            std::function<void()> task;
            {
                std::unique_lock<std::mutex> lock(m_mutex);
                m_condition.wait(lock, [this] { return m_stop || !m_tasks.empty(); });

                if (m_stop && m_tasks.empty()) {
                    return;
                }

                task = std::move(m_tasks.front());
                m_tasks.pop();
            }
            task(); // Execute the task with the stored parameter
        }
    }

    template <class F, class... Args>
    void enqueue(F&& f, Args&&... args) {
        {
            std::unique_lock<std::mutex> lock(m_mutex);

            // Store the task with the parameter in the task queue
            m_tasks.emplace([f, args...]() { f(args...); });
        }
        m_condition.notify_one();
        //m_condition.notify_all();
    }

private:
    /**
     * @brief 
     * initThreadPool用于初始化ThreadPool类
     */
    void initThreadPool(UInt32 size) {
        for (size_t i = 0; i < size; ++i) {
            m_workers.emplace_back(std::bind(&ThreadPool::workerFunction, this));
            //DebugPrint("创建线程%lu", i+1);
        }
    }

private:
    //static ThreadPool *__threadpool; // 单例线程池
    std::vector<std::thread> m_workers;
    std::queue<std::function<void()>> m_tasks;
    std::mutex m_mutex;
    std::condition_variable m_condition;
    std::atomic<bool> m_stop;

private:
    /* 不允许拷贝构造、赋值、移动构造以及移动赋值 */
    ThreadPool(const ThreadPool &) = delete;
    ThreadPool(ThreadPool &&) = delete;
    ThreadPool &operator=(const ThreadPool &) = delete;
    ThreadPool &operator=(ThreadPool &&) = delete;
};

#endif //__THREAD_POOL_H__