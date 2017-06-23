#ifndef DOLLARSPLITER_H
#define DOLLARSPLITER_H

#include <QString>
#include <vector>
#include "spliter.h"

//按照美元符号进行分割的字符串分割器
class DollarSpliter : public Spliter
{
public:
    DollarSpliter() {}
    ~DollarSpliter() {}
    virtual std::vector<QString> split(QString);
};
#endif // DOLLARSPLITER_H
