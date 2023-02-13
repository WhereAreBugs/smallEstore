//
// Created by 神奇bug在哪里 on 2022/12/16.
//

#ifndef FINAL_PROJECT_NETWORKIO_H
#define FINAL_PROJECT_NETWORKIO_H

/* 该分支不再能在mac上可用 */
#include <netinet/in.h>
#include <deque>
#include "serverLog.h"
#include "threadPool.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
/* 这是epoll的分支，所以自然就使用epoll啦 */
#include <csignal>
#include <cstring>
/* 为了能够使用memset */
#include <string>

class networkIO {
private:
    int listenSockId = -1;
    struct sockaddr_in ipConfig;
    struct epoll_event listenEpollEvent[64];
    struct epoll_event listenEV{};
    int listeningEpoll;
    std::vector<std::thread> acceptThreads;
    threadPool networkIoThreads;
    std::mutex pipeReadLocker;
    std::mutex pipeSendLocker;
public:
    int init(short port);

    /* 默认端口采用1433，也就是SQL的默认端口 */
    [[noreturn]] static void accepts(networkIO *_this, int readerFd[2]);

    void start(int readerFd[2], int senderFd[2]);

    ~networkIO() {
        log(warning, "server触发了回收!");
        stop();
    }

    void stop() const;

    [[noreturn]] void senderTaskerGetter(int *senderFd);

    void *reader(int *readerFd, int targetSockId);

    void putResponse(bool status, int sockId);

    void deleteResponse(bool status, int sockId);

    void getResponse(uint32_t size, std::string targetValue, int sockId);
};

bool sendField(int target_sock_id, void *data_to_send, uint32_t size, int extra);

bool sendHeader(int target_sock_id, uint32_t full_size, uint32_t type);

void pipeReader(int fd, void *buf, uint32_t bytes);

#endif //FINAL_PROJECT_NETWORKIO_H
