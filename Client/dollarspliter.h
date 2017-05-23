#ifndef DOLLARSPLITER_H
#define DOLLARSPLITER_H

#include "spliter.h"

class DollarSpliter : public Spliter
{
public:
    DollarSpliter() {}
    ~DollarSpliter() {}
    std::vector<QString> split(QString);
};

#endif // DOLLARSPLITER_H
