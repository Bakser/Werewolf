#ifndef PEOPLE_H
#define PEOPLE_H

#include <QObject>
#include <QPushButton>
#include <QLabel>

class people
{
public:
    people();
    int number;
    enum identity{FORESEE,GUARD,HUNTER,VILLAGER,WITCH,WOLF};
    QPixmap Img;
    people(int idn,identity id);
private:
};

#endif // PEOPLE_H
