//
// Created by 神奇bug在哪里 on 2023/1/8.
//
#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <vector>
#include <queue>
#include <atomic>
#include <future>
#include <stdexcept>
#include "settings.h"


class threadPool {
    unsigned short minSize = MIN_WORK_THREAD;       //初始化线程数量
    using Task = std::function<void()>;  //定义函数类型
    std::vector<std::thread> threadIDs;          //线程池，采用vector进行动态扩容和删减。之前想尝试用deque，但没有必要
    std::queue<Task> tasks;            //任务队列
    std::mutex taskLocker;                   //任务队列同步锁
    std::mutex addThreadLocker;               //线程池添加线程同步锁
    std::condition_variable taskCv;   //条件阻塞，用来控制线程的运行
    std::atomic<bool> isRunning = true;     //线程池是否正在运行
    std::atomic<int> idleThreadCount{0};  //空闲线程数量


public:
    template<class Func, class... Args>
    /* 使用可变参数模版类 */
    auto addTasks(Func &&f, Args &&... args) -> std::future<decltype(f(args...))> {
        /*
         * description: 用于向线程池提交一个任务
         * return: 返回future对象
         */
        if (!isRunning)    // stopped
            throw std::runtime_error("addTasks on ThreadPool is stopped.");

        using returnType = decltype(f(args...)); // 函数的返回值类型
        auto task = make_shared<std::packaged_task<returnType()>>(
                bind(forward<Func>(f), forward<Args>(args)...)
        ); // 把函数入口及参数绑定
        std::future<returnType> future = task->get_future();
        {    // 添加任务到队列
            std::lock_guard<std::mutex> lock{
                    taskLocker};//对当前块的语句加锁  lock_guard 是 mutex 的 stack 封装类，构造的时候 lock()，析构的时候 unlock()
            tasks.emplace([task]() { // push(Task{...}) 放到队列后面
                (*task)();
            });
        }
        if (idleThreadCount < 1 && threadIDs.size() < MAX_WORK_THREAD)
            addThread(1);
        taskCv.notify_one(); // 唤醒一个线程执行
        return future;
    }

    inline ~threadPool() {
        isRunning = false;
        taskCv.notify_all(); // 唤醒所有线程，并且执行清空任务队列
        for (std::thread &thread: threadIDs) {
            if (thread.joinable())
                thread.join(); // 等待全部任务结束
        }
    }

    inline threadPool() {
        addThread(MIN_WORK_THREAD);
    }

    inline void stop() {
        /*
         * description: 用于部分情况下强行停止线程池（不知道为什么有时候析构函数不执行，很怪）
         * return: 无
         * additional information: 下面的内容是复制的析构函数的内容
         */
        isRunning = false;
        taskCv.notify_all(); // 唤醒所有线程，并且执行清空任务队列
        for (std::thread &thread: threadIDs) {
            if (thread.joinable())
                thread.join(); // 等待全部任务结束
        }
        log(warning, "线程池已手动停止！");
    }

private:
    //添加指定数量的线程
    void addThread(unsigned short size) {
        if (!isRunning)    //神奇的问题发生了
                log(error,"线程池: 线程创建出现异常!");
        std::unique_lock<std::mutex> lockGrow{addThreadLocker}; //自动线程添加锁(防止出现竞态条件)
        for (; threadIDs.size() < MAX_WORK_THREAD && size > 0; --size) {   //增加线程数量,但不超过MAX_WORK_THREAD定义的最大大小
            threadIDs.emplace_back([this]
            { //工作线程函数
                while (true) //防止销毁线程池的时候工作线程直接停止,此时任务队列可能不为空
                {
                    Task task; // 获取一个待执行的任务
                    {
                        std::unique_lock<std::mutex> lock{taskLocker};
                        taskCv.wait(lock, [this] { // 等待任务传入, 或需要停止
                            return !isRunning || !tasks.empty();
                        });
                        if (!isRunning && tasks.empty())
                            return; //任务队列空了，直接退出
                        idleThreadCount--;
                        task = std::move(tasks.front()); // 按先进先出从队列取一个 task,使用std::move避免多余的拷贝构造
                        tasks.pop();
                    }
                    task();//执行任务
                    if (idleThreadCount > 0 && threadIDs.size() > minSize) //自动释放空闲线程,避免峰值过后大量空闲线程
                        return;
                    {
                        std::unique_lock<std::mutex> lock{taskLocker};
                        idleThreadCount++;
                    }
                }
            });
            {
                std::unique_lock<std::mutex> lock{taskLocker};
                idleThreadCount++;
            }
        }
    }
};
#endif