#ifndef Game_H
#define Game_H
#include "eventhandler.h"
#include "EventHandler.h"
#include "Gamestatus.h"
class Gamestatus;
class Game:public EventHandler{
    Q_OBJECT
    protected:
        ServerNetworkInterface* networkInterface;
        EventHandler* room;
        Gamestatus* status;
        std::vector<QString>users;
        std::vector<Player*>waitVote,waitMessage,waitSpecial;
        std::vector<QString>deadbuffer;
        std::map<QString,bool>poied;
    private:
        virtual bool canHandle(QString);
        virtual EventHandler* selectHandler(QString);
        virtual void handle(QString,QString);
        bool judgewait();
        void set(QString,bool,bool,QString channel=QString("Room"));//vote say
        void report(QString);
        void reportall(QString);
        void startAwaitsession(int);
        void broadcast(QString,QString,bool=0);
        void closeall();
        int deadclear(std::vector<QString>,bool);
        int dayround(int);
        int nightround(int);
        QString allvote(QString,int);
    public:
        Game(std::vector<QString>,std::vector<int>,ServerNetworkInterface*,EventHandler*);
        QString askforonevote(QString,QString,int=10000);//user info
        bool askforonemessage(QString,QString,QString,int=10000);//username channel info
        void run();
    signals:
        void receiveOK();
};
#endif
