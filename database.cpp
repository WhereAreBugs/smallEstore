#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-avoid-bind"
#pragma ide diagnostic ignored "performance-inefficient-string-concatenation"
//
// Created by 神奇bug在哪里 on 2022/12/24.
//
#include "database.h"
#include <fstream>
#include <csignal>
#include <unistd.h>
#include <functional>
void pipeReader(int fd, void *buf, uint32_t bytes);
database *globalSignalPointer = nullptr;
/* 在声明任何指针的时候，一定要用空指针进行初始化！
 * 之前一个离谱的bug就是这个指针没有赋值导致的！🤬*/

void database::start(int readerFd[2], int senderFd[2]) {
    /*
     * description: 数据进程的入口
     * return: 不会返回
     */
    close(readerFd[1]);//reader仅读取
    close(senderFd[0]);//sender仅写入
    if (!readFromFile()) {
        log(warning, "数据文件读取失败！");
    }
    globalSignalPointer = this;
    signal(SIGTERM, sigHelder);
    log(info, "database:start success！");
    taskSync(readerFd, senderFd);//主线程负责从管道读取数据并添加到任务列表
    exit(-1);
}

bool database::putValue(const std::string &targetKey, const std::string &targetValue) noexcept(false) {
    /*
     * description: 用于向数据库中添加键值对
     * return: 是否成功
     * more information: 声明noexcept(false)的原因是该函数可能会抛出Out-of-range异常
     */
    try {
        std::string value = datas.at(targetKey); //判断要写入的数据是否已经存在
        if (value == targetValue) {
            log(warning, "待写入的数据: " + targetValue + " 已经存在!");
        } else {
            log(warning, "原数据: " + value + " 将会替换成: " + targetValue);
            databaseLocker.lock();
            datas.at(targetKey) = targetValue;
            databaseLocker.unlock();
        }
    } catch (std::exception &e) {   //若数据不存在则会出现out_of_range错误并被捕获，然后再向容器中写入数据
        databaseLocker.lock();
        datas.emplace(targetKey, targetValue);
        databaseLocker.unlock();
    }
    return true;
}

std::string database::getValue(const std::string &targetKey)
/*
 * description: 用于获取Key对应的Value
 * return: 出错时会返回空的std::string，成功时会返回Value
 */
{
    std::string result;
    try {
        databaseLocker.lock();
        result = datas.at(targetKey);
        databaseLocker.unlock();
        log(info, "database:数据库中找到已经存在的数据:value=" + result);
    } catch (std::exception &e) {
        return result;
    }
    return result;
}

bool database::readFromFile() {
    /*
     * description: 用于从文件中读取数据
     * return: 是否成功
     */
    std::ifstream file;
    file.open("datas.dat", std::ios_base::in | std::ios_base::binary);
    if (!file.is_open())
        return false;
    while (true) {
        uint32_t size;
        std::string value, key;
        file.read(reinterpret_cast<char *>(&size), 4);
        key.resize(size);
        if (size <= 0)
            break;
        else {
            file.read(const_cast<char *>(key.data()), size);
        }

        file.read(reinterpret_cast<char *>(&size), 4);
        if (size <= 0) {
            log(error, "文件不完整！");
            datas.emplace(key, "null");
            return false;
        } else {
            value.resize(size);
            file.read(const_cast<char *>(value.data()), size);
        }
        datas.emplace(key, value);
        log(info, "已从文件中读取: key=" + key + "value=" + value);
        key.clear();
        value.clear();
    }
    file.close();
    return true;
}

bool database::deleteValue(const std::string& t_key) {
    /*
     * description: 从数据库中删除数据
     * return: 是否成功
     */
    try {
        databaseLocker.lock();
        datas.erase(t_key);
        databaseLocker.unlock();
        /* 加锁用于解决一些同步读取的竞态条件 */
    } catch (std::exception &e) {
        log(warning, "待删除的数据不存在！");
        return false;
    }
    return true;
}

bool database::saveToFile() {
    //这个函数理论上只会在退出的时候被调用一次
    log(info, "database:开始保存数据...");
    uint32_t size;
    std::ofstream file;
    file.open("datas.dat", std::ios_base::out | std::ios_base::binary);
    if (!file.is_open()) {
        log(error, "文件保存失败！");
        return false;
    }
    for (auto &data: datas) {
        std::string targetKey = data.first, targetValue = data.second;
        size = targetKey.size();
        file.write(reinterpret_cast<char *>(&size), 4);
        file.write(targetKey.c_str(), size);
        size = targetValue.size();
        file.write(reinterpret_cast<char *>(&size), 4);
        file.write(targetValue.c_str(), size);
        log(info, "已写入到文件,key=" + targetKey + "value=" + targetValue);
    }
    size = 0;
    file.write(reinterpret_cast<char *>(&size), 4);
    file.close();
    log(info, "数据保存完成!");
    return true;
}

void database::sigHelder(int signum) {
    log(warning, "数据进程收到信号！", signum);
    globalSignalPointer->databaseThreadPool.stop();
    globalSignalPointer->saveToFile();
    exit(signum);
}

void database::taskSync(int *readerFd, int *senderFd) {
    uint32_t type = 0;
    int sockID = -1;
    while (true) {
        pipeReader(readerFd[0], &type, sizeof(int));
        switch (type) {
            case 0://put
            {
                uint32_t keySize, valueSize = 0;
                std::string targetKey, targetValue;
                pipeReader(readerFd[0], &keySize, 4) ;
                targetKey.resize(keySize);
                pipeReader(readerFd[0], const_cast<char *>(targetKey.data()), keySize);
                pipeReader(readerFd[0], &valueSize, 4);
                targetValue.resize(valueSize);
                pipeReader(readerFd[0], const_cast<char *>(targetValue.data()), valueSize);
                pipeReader(readerFd[0], &sockID, sizeof(int));
                log(info, "database:收到put请求！");
                databaseThreadPool.addTasks(
                        std::bind(&database::putResponse, this, targetKey, targetValue, sockID, senderFd));
                break;
            }
            case 1://delete
            {
                uint32_t keySize;
                std::string targetKey;
                pipeReader(readerFd[0], &keySize, 4);
                targetKey.resize(keySize);
                pipeReader(readerFd[0], const_cast<char *>(targetKey.data()), keySize);
                pipeReader(readerFd[0], &sockID, sizeof(int));
                log(info, "database:收到delete请求!key=" + targetKey);
                databaseThreadPool.addTasks(std::bind(&database::deleteResponse, this, targetKey, sockID, senderFd));
                break;
            }
            case 2: {
                uint32_t keySize;
                std::string targetKey;
                pipeReader(readerFd[0], &keySize, 4);
                targetKey.resize(keySize);
                pipeReader(readerFd[0], const_cast<char *>(targetKey.data()), keySize);
                pipeReader(readerFd[0], &sockID, sizeof(int));
                log(info, "database:处理Get请求:key=" + targetKey);
                databaseThreadPool.addTasks(std::bind(&database::getResponse, this, targetKey, sockID, senderFd));
                break;
            }
            default: {
                log(error, "database:错误的type！");
                break;
            }
        }//从管道中解析任务并且添加对应的任务到线程池
    }
}

void database::putResponse(const std::string targetKey, const std::string targetValue, int sockID, int senderFd[2]) {
    log(info, "database:子线程开始处理");
    const uint32_t type = 3;
    bool result = putValue(targetKey, targetValue);
    pipeLocker.lock();
    pipeWrite(senderFd[1], &type, 4);
    pipeWrite(senderFd[1], &result, sizeof(bool));
    pipeWrite(senderFd[1], &sockID, sizeof(int));
    pipeLocker.unlock();
}

void database::deleteResponse(std::string targetKey, int sockID, int senderFd[2]) {
    const uint32_t type = 4;
    bool result = deleteValue(targetKey);
    pipeLocker.lock();
    pipeWrite(senderFd[1], &type, 4);
    pipeWrite(senderFd[1], &result, sizeof(bool));
    pipeWrite(senderFd[1], &sockID, sizeof(int));
    pipeLocker.unlock();
}

void database::getResponse(std::string targetKey, int sockID, int senderFd[2]) {
    const uint32_t type = 5;
    std::string value = getValue(targetKey);

    if (value.empty()) {
        log(error, "查找键值对失败");
        uint32_t valueSize = 4;
        value = "null";
        pipeLocker.lock();
        pipeWrite(senderFd[1], &type, 4);
        pipeWrite(senderFd[1], &valueSize, 4);
        pipeWrite(senderFd[1], const_cast<char *>(value.data()), valueSize);
        pipeWrite(senderFd[1], &sockID, sizeof(int));
        pipeLocker.unlock();
        log(info, "database:Get请求完成处理，已经放回管道");
    } else {
        uint32_t valueSize = value.size();
        log(info, "database:查找键值对成功！value=" + value);
        pipeLocker.lock();
        pipeWrite(senderFd[1], &type, 4);
        pipeWrite(senderFd[1], &valueSize, 4);
        pipeWrite(senderFd[1], const_cast<char *>(value.data()), valueSize);
        pipeWrite(senderFd[1], &sockID, sizeof(int));
        pipeLocker.unlock();
        log(info, "database:数据写入管道完成");
    }
}


void pipeWrite(int fd, const void *buf, uint32_t nBytes) {
    uint32_t writeSize = 0;
    while (writeSize < nBytes)
    {
        long temp = write(fd,reinterpret_cast<const char *>(buf)+writeSize, nBytes - writeSize);
        if (temp==-1)
        {
            log(error,"pipeWrite:发生了管道写入错误",errno);
            continue;
        }
        writeSize += temp;
    }
}

#pragma clang diagnostic pop