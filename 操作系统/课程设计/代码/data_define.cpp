//
// Created by Zhang Boyu on 2019/12/28.
//

#include "data_define.h"

void outputStr(string s){
    // 先用cout进行输出，后续使用QString进行输出
    std::cout<<s<<endl;
}

//需要特别注意的是，年份是从1900年起至今多少年，而不是直接存储如2011年，月份从0开始的，0表示一月，星期也是从0开始的， 0表示星期日，1表示星期一。
QString parseTM(tm t)
{
    // 年-月-日：时分秒
    return QString::number(1900+t.tm_year)+"年"+QString::number(t.tm_mon+1)+"月"+QString::number(t.tm_mday)+"日("+QString::number(t.tm_hour)+"时"+QString::number(t.tm_min)+"分"+QString::number(t.tm_sec)+"秒)";
}

//需要特别注意的是，年份是从1900年起至今多少年，而不是直接存储如2011年，月份从0开始的，0表示一月，星期也是从0开始的， 0表示星期日，1表示星期一。
QString parseTMSimple(tm t)
{
    // 年-月-日：时分秒
    return "("+QString::number(t.tm_hour)+"时"+QString::number(t.tm_min)+"分"+QString::number(t.tm_sec)+"秒)";
}
