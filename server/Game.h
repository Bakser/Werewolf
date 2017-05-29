#ifndef Game_H
#define Game_H
#include "eventhandler.h"
#include "RoomHandler.h"
#include "Gamestatus.h"
#include <queue>
class Gamestatus;
class Player;
class Game: public EventHandler{
    //Q_OBJECT
    protected:
        RoomHandler* room;
        Gamestatus* status;
        std::vector<QString>users;
        std::vector<Player*> waitVote,waitMessage,waitSpecial;
        std::vector<QString> deadbuffer;
        std::map<QString,bool>poied;
        int stage,round;
        std::queue<QString> waitq;
        bool hunterflag,capflag,sayflag,voteflag;
    private:
        virtual bool canHandle(QString);
        virtual EventHandler* selectHandler(QString);
        virtual void handle(QString,QString);
        bool judgewait();
        void set(QString,bool,bool,QString);//vote say
        void report(QString);
        void reportall();
        //void startAwaitsession(int);
        void broadcast(QString,QString,bool);
        void closeall();
        int deadclr(std::vector<QString>,bool);
        int dayround(int);
        int nightround(int);
        void solvecap();
        void solveq();
        void solvehunter();
        void gameend(int);
        void allvote(QString,int);
        QString resforallvote();
    public:
        //void sendMessage(QString,QString);
        Game(std::vector<QString>,std::vector<int>,ServerNetworkInterface*,RoomHandler*);
        void askforonevote(QString,QString,int);//user info
        QString resforonevote(QString);
        bool askforonemessage(QString,QString,QString,int);//username channel info
        void run();
    //signals:
        //void receiveOK();
};
#endif
