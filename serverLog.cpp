//
// Created by 神奇bug在哪里 on 2022/12/23.
//
#include "serverLog.h"
#include "settings.h"

enum log_level global_log_level = GLOBAL_LOG_LEVEL;
/*
 * description: 以下函数均是用来日志输出的
 * return: 无
 */
void log(enum log_level level, const std::string &context) {
    if (level >= global_log_level) {
        std::cout << (level == info ? INFO_COLOR : (level == warning ? WARNING_COLOR : ERROR_COLOR));
        std::cout << (level == info ? "[I] " : (level == warning ? "[W] " : "[E] "));
        std::cout << context << COLOR_END << std::endl;
    }
}

void log(enum log_level level, const std::string &context, int id) {
    if (level >= global_log_level) {
        std::cout << (level == info ? INFO_COLOR : (level == warning ? WARNING_COLOR : ERROR_COLOR));
        std::cout << (level == info ? "[I] " : (level == warning ? "[W] " : "[E] "));
        std::cout << context << "\t[ID]: " << id << COLOR_END << std::endl;
    }
}

