//
//  main.cpp
//  Final_project
//
//  Created by 神奇bug在哪里 on 2022/12/21.
//

#include "init.h"
#include "networkIO.h"
#include <wait.h>
#include <unistd.h>

int main() {
    log(info, "starting...");
    pInit = &init;
    init.start();
    //理论上不会再往下执行
    log(error, "Unknown Reason for main exiting!");
    return 0;
}

void sigHandler(int singleNum) {
    /*
     * description: 用于处理外部的退出信号
     * return: 无
     */
    log(info, "主进程已收到信号", singleNum);
    pInit->exit();
}

void init::exit() {
    /*
     * description: 主进程的退出函数，会回收所有的子进程
     * return: 无，将会直接退出
     */
    for (int i = 0; i < pid.size(); ++i) {
        kill(pid.at(i), SIGTERM);
        waitpid(pid.at(i), nullptr, 1);
        log(info, "进程已回收", i);
    }
    /* 用以停止所有正在运行的进程 */
    log(info, "所有进程均已完成回收！");
    ::exit(0);
}

[[noreturn]] void init::start() {
    int readerFd[2], senderFd[2];
    /*
     * readerFd:用于读取线程和数据库之间的交互
     * senderFd:用于发送线程和数据库之间的交互
     */
    /* 下面开始创建管道 */
    if (pipe(readerFd) == -1 || pipe(senderFd) == -1) {
        log(error, "init: 管道出现错误！");
        ::exit(errno);
    }
    /* 下面开始创建进程 */
    pid_t processorID;
    processorID = fork();
    if (processorID == 0) {
        /*
         * 进程1: 数据进程
         * description: 用于处理数据IO和文件IO
         */
        database database;
        database.start(readerFd, senderFd);//正常情况下该函数将不会返回
        log(error, "databaseMain:数据进程异常退出！");
        ::exit(errno);
    }
    pid.emplace_back(processorID);
    processorID = fork();
    if (processorID == 0) {
        /*
         * 进程2: 网络进程
         * description: 用于处理网络IO
         */
        networkIO networkIO;
        networkIO.start(readerFd, senderFd); //正常情况下该函数不会返回
        log(error, "networkIO:网络IO进程异常退出！");
        ::exit(errno);
    }
    pid.emplace_back(processorID);
    /* 下面父进程关闭管道 */
    close(readerFd[0]);
    close(readerFd[1]);
    close(senderFd[0]);
    close(senderFd[1]);
    log(info, "父进程已关闭全部管道!");
    signal(SIGTERM, sigHandler); //注册信号处理函数
    signal(SIGSEGV, sigHandler);
    signal(SIGINT, sigHandler);
    signal(SIGSTOP, sigHandler);
    signal(SIGKILL, sigHandler);
    signal(SIGQUIT, sigHandler);
    log(info, "主进程信号处理函数注册完成");
    management();
    /*
     * 进程0: init进程
     * description: 用于监控子进程的运行状态
     * return: 无
     */
}

[[noreturn]] void init::management() {
    /*
     * description: init进程的主要管理部分
     * return: 无
     */
    auto * status = new int; //用于接收子进程的退出状态
    while (true){
        waitpid(-1,status,0);
        if (WIFEXITED(* status))//进程异常退出
        {
            log(error,"子进程异常退出！");
            restart();
        }
        else
            break;
    }
    exit();//正常退出
    ::exit(-1);
}

void init::restart() {
    /*
     * description: 用于子进程的错误恢复
     * return: 无
     */
    log(warning,"init: 进程自动重启开始...");
    for (int i = 0; i < pid.size(); ++i) {
        kill(pid.at(i), SIGTERM);
        waitpid(pid.at(i), nullptr, 1);
        log(info, "进程已停止", i);
    }
    log(warning,"init:开始重启!");
    pInit->start();
}


