#ifndef GLOBALS_H
#define GLOBALS_H

#include <QString>

class Globals
{
public:
    static QString meid;
    static int roomnumber;
    static QString player_id[50];
    static bool player_alive[50];//1-alive;0-died
    static int nplayer;
    static int merole;
};



#endif // GLOBALS_H
