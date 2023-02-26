//
// Created by 神奇bug在哪里.
//
#include "base64.h"
#include "serverLog.h"
using namespace std;
int base64::look_back(char a)
{
    int i = 0;
    for (;i <64;i++) {
        if(a==base64_codec[i])
            break;
    }
    return i;
}
/* 将base64编码还原成6位的数据 */
void base64::to_base64() {
    union binary temp;
    while (target.length() % 3 != 0) {
        target.push_back(0);
    }
    //保证原数据为3的整数倍，便于后续循环
    for (int i = 0; i < target.length(); i += 3) {
        temp.bin8_0 = target.at(i);
        temp.bin8_1 = target.at(i+1);
        temp.bin8_2 = target.at(i+2);
        /* 写入三个8位的数据 共24位 */
        result.push_back(base64_codec[temp.bin6_0]);
        result.push_back(base64_codec[temp.bin6_1]);
        result.push_back(base64_codec[temp.bin6_2]);
        result.push_back(base64_codec[temp.bin6_3]);
        /* 输出四个6位的数据 共24位 */
    }
    if(target.at(target.length()-1)==0&&target.at(target.length()-2)==0)
    {
        result.at(result.length()-1)='=';
        result.at(result.length()-2)='=';
    }
    if(target.at(target.length()-1)==0)
    {
        result.at(result.length()-1)='=';
    }


}
void base64::decode()
{
    union binary temp;
    if(target.length()%4)//base64编码的长度一定是4的整数倍（不足会补全）
    {
        log(error,"base64: base64编码错误!");
        return;
    }

    if (target.at(target.length()-1)=='='&&target.at(target.length()-2)=='='&&target.at(target.length()-3)=='=')
    {
        target.at(target.length()-1)='A';
        target.at(target.length()-2)='A';
        target.at(target.length()-3)='A';
    }
    else if (target.at(target.length()-1)=='='&&target.at(target.length()-2)=='=')
    {
        target.at(target.length()-1)='A';
        target.at(target.length()-2)='A';
    }
    else if(target.at(target.length()-1)=='=')
    {
        target.at(target.length()-1)='A';
    }
    //处理末尾的=，使其变成0。
    for (int i = 0; i < target.length(); i += 4) {
        temp.bin6_0 = look_back(target.at(i));
        temp.bin6_1 = look_back(target.at(i+1));
        temp.bin6_2 = look_back(target.at(i+2));
        temp.bin6_3 = look_back(target.at(i+3));
        /* 写入四个6位的数据 共24位 */
        result.push_back(temp.bin8_0);
        result.push_back(temp.bin8_1);
        result.push_back(temp.bin8_2);
        /* 输出三个8位的数据 共24位 */
    }
//理论上最后一个补全的字符应该位'\0',标志着字符串结尾，所以不需要处理。

}

std::string base64::get_result() {
    return std::move(result);
}

base64::binary::binary() {
    bin8_2 = 0;
    bin8_1 = 0;
    bin8_0 = 0;
}//构造函数，保证用0填充完所有的位
