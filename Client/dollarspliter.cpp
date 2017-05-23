#include "dollarspliter.h"
#include <QRegExp>

std::vector<QString> DollarSpliter::split(QString s)
{
    std::vector<QString> ans;
    int last = 0, next;
    while ((next = s.indexOf(QRegExp("$"), last)) != -1) {
        ans.push_back(s.mid(last, next - last));
        last = next + 1;
    }
    ans.push_back(s.mid(last, s.length() - last));
    return ans;
}

