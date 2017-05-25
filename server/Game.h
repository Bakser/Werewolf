#ifndef Game_H
#define Game_H
#include "eventhandler.h"
#include "EventHandler.h"
#include "Gamestatus.h"
class Gamestatus;
class Player;
class Game:public EventHandler{
    Q_OBJECT
    protected:
        ServerNetworkInterface* networkInterface;
        RoomHandler* room;
        Gamestatus* status;
        std::vector<QString>users;
        std::vector<Player*> waitVote,waitMessage,waitSpecial;
        std::vector<QString> deadbuffer;
        std::map<QString,bool>poied;
    private:
        virtual bool canHandle(QString);
        virtual EventHandler* selectHandler(QString);
        virtual void handle(QString,QString);
        bool judgewait();
        void set(QString,bool,bool,QString);//vote say
        void report(QString);
        void reportall();
        void startAwaitsession(int);
        void broadcast(QString,QString,bool);
        void closeall();
        int deadclear(std::vector<QString>,int);
        int dayround(int);
        int nightround(int);
        QString allvote(QString,int);
    public:
        Game(std::vector<QString>,std::vector<int>,ServerNetworkInterface*,RoomHandler*);
        QString askforonevote(QString,QString,int);//user info
        bool askforonemessage(QString,QString,QString,int);//username channel info
        void run();
    signals:
        void receiveOK();
};
#endif
