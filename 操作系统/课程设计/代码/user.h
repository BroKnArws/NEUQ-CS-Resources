#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>
#include <QStringList>

class User
{
public:
    User();
    // 用户名
    static QStringList userName;
    static std::string userName0;
    static std::string userName1;
    static std::string userName2;
    static std::string userName3;
    static int count;
};

#endif // USER_H
