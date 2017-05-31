#ifndef GLOBALS_H
#define GLOBALS_H

#include <QString>
#include <vector>
class Globals
{
public:
    static QString meid;
    static int roomnumber;
    static QString player_id[50];
    static bool player_alive[50];//1-alive;0-died
    static int nplayer;
    static int merole;
    static bool newGameStarted;
    static QString master;
    static QString lastDefend;
    static QString meroleString;
    static void update(QString);
    static void reset();
    static void dieUpdate(QString);
    /*
    QString meid;
    int roomnumber;
    QString *player_id;
    bool *player_alive;
    int nplayer;
    int merole;
    bool afterInitialize;
    Globals();
    ~Globals();
    void update(QString);
    */
};



#endif // GLOBALS_H
