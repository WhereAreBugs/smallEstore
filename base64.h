//
// Created by 神奇bug在哪里.
//

#ifndef BASE64_BASE64_H
#define BASE64_BASE64_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
class base64{
    void to_base64();
    void decode();
    int look_back(char a);
    union binary
    {
        struct {
            unsigned int bin8_2 : 8;
            unsigned int bin8_1 : 8;
            unsigned int bin8_0 : 8;
        };
        struct {
            unsigned int bin6_3 : 6{};
            unsigned int bin6_2 : 6{};
            unsigned int bin6_1 : 6{};
            unsigned int bin6_0 : 6{};
        };

        binary();
    };
/* 想了半天，感觉要对其进行分割，最简单的方案还是使用联合 */
    const char base64_codec[64] = {
            'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H','I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
            'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X','Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
            'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n','o', 'p', 'q', 'r', 's', 't', 'u', 'v',
            'w', 'x', 'y', 'z', '0', '1', '2', '3','4', '5', '6', '7', '8', '9', '+', '/'
    };
    std::string target;
    std::string result;
    std::string get_result();
//base64编码，用数组便于转换。
};

#endif //BASE64_BASE64_H
