//
// Created by 神奇bug在哪里 on 2022/12/24.
//

#ifndef FINAL_PROJECT_DATABASE_H
#define FINAL_PROJECT_DATABASE_H

#include <deque>
#include <map>
#include <mutex>
#include "serverLog.h"
#include "threadPool.h"
#include <string>

class database : public threadPool {
private:
    std::map<std::string, std::string> datas; //主要的数据存储结构
    std::mutex databaseLocker;
    std::mutex pipeLocker;
    threadPool databaseThreadPool; //线程池

public:
    void start(int readerFd[2], int senderFd[2]);

    bool putValue(const std::string &targetKey, const std::string &targetValue);

    std::string getValue(const std::string &targetKey);

    bool deleteValue(const std::string& t_key);

    bool saveToFile();

    bool readFromFile();

    [[noreturn]] void taskSync(int readerFd[2], int senderFd[2]);

    void putResponse(std::string targetKey, std::string targetValue, int sockID, int senderFd[2]);

    void deleteResponse(std::string targetKey, int sockID, int senderFd[2]);

    void getResponse(std::string targetKey, int sockID, int senderFd[2]);

    ~database() {
        log(warning, "Force exit!\nSaving datas now....");
        databaseThreadPool.stop();
        saveToFile();
    }

    static void sigHelder(int);
};

void pipeWrite(int fd, const void *buf, uint32_t nBytes);

#endif //FINAL_PROJECT_DATABASE_H
