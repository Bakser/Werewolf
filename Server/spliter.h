#ifndef SPLITER_H
#define SPLITER_H

#include <vector>
#include <QString>

//通信字符串分割器
class Spliter
{
public:
    Spliter() {}
    virtual ~Spliter() {}
    virtual std::vector<QString> split(QString) = 0; //返回一个vector顺次保存分割后的字符串
};

#endif // SPLITER_H
