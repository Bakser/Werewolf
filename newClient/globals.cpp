#include "globals.h"
#include <QString>
#include "stringoperate.h"
#include <QDebug>

QString Globals::meid="4";//自己的username
int Globals::roomnumber=222;

//根据包改，此处为测试
bool Globals::player_alive[50]={1,1,1,1,1,1,1,1,1,1};
QString Globals::player_id[50]={"231","b","qw","sdf","d","d","23fe","d","sd","ers"};
int Globals::nplayer=10;
QString Globals::lastDefend = "";
QString Globals::master = "";
QString Globals::meroleString = "";
int Globals::merole=2;//自己的身份
bool Globals::newGameStarted = false;

void Globals::update(QString s)
{
    //newGameStarted = true;
    std::vector<QString> temp = split(s, "\n");
    nplayer = temp.size() - 2;
    for (int i = 1; i < temp.size(); ++i)
    {
        std::vector<QString> saver = split(temp[i], " ");
        if (i == 1)
        {
            meid = saver[0];
            meroleString = saver[1];
            if (saver[1] == "villager")
                merole = 0;
            else if (saver[1] == "prophet")
                merole = 1;
            else if (saver[1] == "witch")
                merole = 2;
            else if (saver[1] == "werewolf")
                merole = 3;
            else if (saver[1] == "hunter")
                merole = 4;
            else if (saver[1] == "defender")
                merole = 5;
            else
                qDebug() << "Unknown character type";
        }
        else
        {
            player_id[i - 2] = saver[0];
            player_alive[i - 2] = saver[1].toInt();
            if (saver[2].toInt() == 1)
                master = saver[0];
        }
    }
}

void Globals::reset()
{
    newGameStarted = false;
    master = lastDefend = "";
}

void Globals::dieUpdate(QString username)
{
    for (int i = 0; i < nplayer; ++i)
    {
        if (player_id[i] == username)
        {
            player_alive[i] = false;
        }
    }
}
