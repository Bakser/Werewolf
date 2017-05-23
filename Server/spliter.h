#ifndef SPLITER_H
#define SPLITER_H

#include <vector>
#include <QString>

class Spliter
{
public:
    Spliter() {}
    virtual ~Spliter() {}
    virtual std::vector<QString> split(QString) = 0;
};

#endif // SPLITER_H
