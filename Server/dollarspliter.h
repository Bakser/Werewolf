#ifndef DOLLARSPLITER_H
#define DOLLARSPLITER_H

#include <QString>
#include <vector>
#include "spliter.h"

class DollarSpliter : public Spliter
{
public:
    DollarSpliter() {}
    ~DollarSpliter() {}
    virtual std::vector<QString> split(QString);
};
#endif // DOLLARSPLITER_H
