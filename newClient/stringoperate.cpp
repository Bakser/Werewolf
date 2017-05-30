#include "stringoperate.h"

std::vector<QString> split(QString text, QString pattern)
{
    std::vector<QString> ans;
    int last = 0, next;
    while ((next = text.indexOf(pattern, last)) != -1) {
        if (last < next)
            ans.push_back(text.mid(last, next - last));
        last = next + 1;
    }
    if (last < text.length())
        ans.push_back(text.mid(last, text.length() - last));
    return ans;
}
