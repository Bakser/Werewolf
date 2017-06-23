/*
名称：Game.cpp
作者：计62 王晓智 2016011257
时间：2017.5.30
内容：实现游戏逻辑类
版权：全部自行完成
*/
#include "Game.h"
#include <map>
#include <iostream>
#include <vector>
#include <sstream>
#include <qtimer.h>
#include <queue>
#include <qeventloop.h>
const int DebugMulti=10;
Game::Game(std::vector<QString> _users,std::vector<int> setting,ServerNetworkInterface* _networkInterface,RoomHandler* _room){
    networkInterface=_networkInterface;
    room=_room;
    users=_users;
    status=new Gamestatus(_users,setting,this);
    stage=round=0;
    hunterflag=capflag=sayflag=voteflag=dclrflag=0;
}

bool Game::canHandle(QString message){//责任链到此为止
    return 1;
}
EventHandler* Game::selectHandler(QString message){
    return this;
}
bool Game::judgewait(){
    for(auto i:waitVote)
        if(!i->voted)
            return 0;
    for(auto i:waitMessage)
        if(!i->said)
            return 0;
    for(auto i:waitVote)
        i->voted=0;
    for(auto i:waitMessage)
        i->said=0;
    //waitVote=waitMessage=waitSpecial=std::vector<Player*>();
    return 1;
}
void Game::set(QString username,bool vote,bool say,QString channel=QString("Room")){//各种通信格式参考逻辑主文档
    sendMessage(username,QString("Set\n")+(vote?QString("1 "):QString("0 "))+(say?QString("1 "):QString("0 "))+channel);
}
void Game::report(QString username){
    sendMessage(username,QString("Status\n")+status->showonestatus(username)+status->showalivestatus());
}
void Game::reportall(){
    for(auto c:status->playerid)
        report(c);
}
void Game::broadcast(QString type,QString message,bool f=0){
    if(type==QString("Allalive")){
        for(auto c:users)
            if(status->alive[c])
                sendMessage(c,message);
        return;
    }
    for(auto c:users)
        if(status->canbroad(c,type,f))
            sendMessage(c,message);
}
void Game::handle(QString username,QString message){
    if(message[0]=='w'&&message[4]=='c')
        broadcast(QString("werewolf"),message,1);
    status->player[username]->handle(message);
    if(judgewait()){//如果满足了等待要求，做对应处理
        sayflag=0;
        if(hunterflag){
            if(solvehunter())
                return;
        }
        if(capflag)solvecap();
        if(!waitq.empty()){
            solveq();
            return;
        }
        else if(waitMessage.size()){
            set(waitMessage[0]->username,0,0);
            waitMessage.clear();
        }
        if(!capflag&&!hunterflag&&waitq.empty()){
            if(!voteflag&&!dclrflag)stage+=2;
            run();
        }
    }
}
void Game::askforonevote(QString username,QString info){
    waitVote=waitMessage=std::vector<Player*>();
    waitVote.push_back(status->player[username]);
    if(info.length())
        sendMessage(username,info);
    set(username,1,0);
}
QString Game::resforonevote(QString username){
    set(username,0,0);
    waitVote=std::vector<Player*>();
    return status->player[username]->lastvote;
}
bool Game::askforonemessage(QString username,QString channel,QString info){
    waitVote=waitMessage=std::vector<Player*>();
    waitMessage.push_back(status->player[username]);
    if(info.length())
        sendMessage(username,info);
    set(username,0,1,channel);
    return 1;
}
void Game::closeall(){
    for(auto c:users)
        set(c,0,0);
}
int Game::deadclr(std::vector<QString> buffer,bool flag=0){
    if(buffer.empty()){
        dclrflag=0;
        return 0;
    }
    QString tmp=QString("Die\n");
    for(auto c:buffer){
        tmp+=nameform(c);
        sendMessage(c,"Youdie");
    }
    room->broadcast(tmp);
    waitVote=waitMessage=std::vector<Player*>();
    for(auto c:buffer)
        if(status->role[c]==QString("hunter")&&!poied[c]){
            sendMessage(c,"Carry");
            set(c,1,0);
            hunterflag=dclrflag=1;
            waitVote.push_back(status->player[c]);
        }
    for(auto c:buffer)
        if(status->cap[c]){
            room->broadcast("Captaindie");
            sendMessage(c,"Pass");
            set(c,1,0);
            capflag=dclrflag=1;
            waitVote.push_back(status->player[c]);
        }
    //死亡结算中如果出现猎人崩人，警徽移交等事件，进入等待
    int res=0;
    for(auto c:buffer)
        res=std::max(res,status->die(c));
    if(res)return res;
    reportall();
    if(flag){
        for(auto c:buffer){
            sendMessage(c,"Tellsth");
            set(c,((status->role[c]==QString("hunter")&&!poied[c])||status->cap[c]),1,"Room");
            sayflag=dclrflag=1;
            waitMessage.push_back(status->player[c]);
        }
    }
    return res;
}
bool Game::solvehunter(){
    for(auto c:users)
        if(status->role[c]==QString("hunter")){
            hunterflag=0;
            QString x=status->player[c]->lastvote;
            if(x.length()){
                room->broadcast(QString("Hunter\n")+nameform(c)+nameform(x));
                deadclr(std::vector<QString>(1,x),1);
                return 1;
            }
        }
   return 0;
}
void Game::solvecap(){
    for(auto c:users)
        if(status->cap[c]){
            capflag=0;
            QString x=status->player[c]->lastvote;
            room->broadcast(QString("Captian\n")+nameform(x));
            if(x.length())
                status->changecap(x);
        }
}
void Game::solveq(){
    QString x=waitq.front();waitq.pop();//每次从队列中取一个进行发言
    if(waitMessage.size()){
        set(waitMessage[0]->username,0,0);
        waitMessage.clear();
    }
    waitMessage.push_back(status->player[x]);
    set(x,0,1,"Room");
}
void Game::allvote(QString info){
    waitVote=waitMessage=std::vector<Player*>();
    for(auto c:users)
        if(status->alive[c])
            waitVote.push_back(status->player[c]);
    if(info.length())
        broadcast("Allalive",info);
    broadcast("Allalive","Set\n1 0 Room");
}
QString Game::resforallvote(){
    broadcast("Allalive","Set\n0 0 Room");
    return status->vote(waitVote);
}
//spflag 1-hunter 2-capdie 3-choose cap 4-equal
int Game::dayround(int rn){
    qDebug()<<"Daystage "<<stage;
    srand(time(0));
    int order=rand()&1,s=0,n=users.size();
    QString cap("");
    if(stage==1){
        qDebug() << "dayround #" << rn;
        room->broadcast(QString("Day ")+IntToStr(rn>>1));
        closeall();
        int tmp=deadclr(deadbuffer,rn==1);
        deadbuffer.clear();
        if(tmp)return tmp;
        if(dclrflag)return 0;
        if(status->setting[6]){
            if(rn==1){
                room->broadcast(QString("TalkCaptain"));
                waitMessage=waitVote=std::vector<Player*>();
                while(!waitq.empty())waitq.pop();
                for(auto c:users)
                    if(status->alive[c])
                        waitq.push(c);
                solveq();
                return 0;
            }
        }
        else goto stage3;
        return 0;
    }
    if(stage==3){
        stage3:
        if(status->setting[6]){
            if(rn==1&&!voteflag){
                allvote("ChooseCap");
                voteflag=1;
                return 0;
            }
            if(rn==1&&voteflag){
                voteflag=0;
                QString t=resforallvote();
                qDebug()<<"Vote cap "<<t;
                if(t[0]=='@')
                    t=QString("");
                else status->changecap(t);
                broadcast("Allalive",QString("Captain\n")+nameform(t));
            }
        }
        for(auto c:users)
            if(status->alive[c]&&status->cap[c]){
                cap=c;
                askforonevote(c,"Order");
            }
        if(!cap.length()){
            stage=5;
            goto stage5;
        }
        return 0;
    }
    if(stage==5){
        stage5:
        for(auto c:users)
            if(status->alive[c]&&status->cap[c])
                cap=c;
        if(cap.length()){
            order=status->player[cap]->lastvote[0]=='1';
            for(int i(0);i<n;i++)
                if(users[i]==cap)
                    s=i;
        }
        order=!order?-1:1;
        waitMessage=waitVote=std::vector<Player*>();
        while(!waitq.empty())waitq.pop();
        for(int i((s+order+n)%n);i!=s;i=(i+order+n)%n)
            waitq.push(users[i]);
        waitq.push(users[s]);
        solveq();
        return 0;
    }
    if(stage==7){
        if(!voteflag){
            allvote("Vote");
            voteflag=1;
            return 0;
        }
        if(voteflag){
            voteflag=0;
            QString t=resforallvote();
            qDebug()<<"Vote die "<<t;
            if(t[0]=='@'){
                broadcast("Allalive",QString("Equal\n")+t);
                voteflag=1;
                allvote("Vote");
                return 0;
            }
            else deadbuffer.push_back(t);
            stage+=2;
            goto label2;
            return 0;
        }
    }
    if(stage==9){
        label2:
        int tmp=deadclr(deadbuffer,1);
        deadbuffer.clear();
        if(dclrflag)return 0;
        if(tmp)return tmp;
        stage=0;round++;
        tmp=nightround(round);
        if(tmp)return tmp;
        return 0;
    }
}
int Game::nightround(int rn){
    qDebug()<<"Nightstage "<<stage;
    static std::map<QString,bool> guarded,killed,saved,poisoned;
    if(stage==0){
        qDebug() << "nightround #" << rn;
        room->broadcast(QString("Night ")+IntToStr(rn>>1));
        reportall();
        closeall();
    //守卫
        bool tflag=1;
        for(auto c:status->roleplayer[QString("defender")])
            if(status->alive[c->username]){
                askforonevote(c->username,QString("Guard"));
                tflag=0;
            }
        if(tflag){
            stage=2;
            goto stage2;
        }
        return 0;
    }
    if(stage==2){
        stage2:
        for(auto c:status->roleplayer[QString("defender")])
            if(status->alive[c->username]){
                QString tmp=resforonevote(c->username);
                qDebug()<<"Guard "<<tmp;
                if(tmp.length())
                    guarded[tmp]=1;
            }
        qDebug()<<"Guarded";
        waitVote=waitMessage=std::vector<Player*>();
        for(auto c:status->roleplayer[QString("werewolf")])
            if(status->alive[c->username])
                waitVote.push_back(c);
        for(auto c:waitVote)
            set(c->username,1,1,QString("Wolf"));
        return 0;
    }
    if(stage==4){
        for(auto c:waitVote)
            set(c->username,0,0);
        QString tmp=status->vote(waitVote);
        qDebug()<<"Wolfkill "<<tmp;
        if(tmp[0]!='@')killed[tmp]=1;
        else tmp=QString("");
        qDebug()<<"Wolfed";
        QString killd=tmp;
        bool tflag=1;
        for(auto c:status->roleplayer[QString("witch")])
            if(status->alive[c->username]&&!status->used1[c->username])
                askforonevote(c->username,QString("Witch\n@")+killd),tflag=0;
        if(tflag){
            stage=6;
            goto stage6;
        }
        return 0;
     }
    if(stage==6){
        stage6:
        for(auto c:status->roleplayer[QString("witch")])
            if(status->alive[c->username]&&!status->used1[c->username]){
                QString tmp=resforonevote(c->username);
                qDebug()<<"Witch save "<<tmp;
                if(tmp.length())
                    saved[tmp]=1,status->used1[c->username]=1;
            }
        qDebug()<<"Witch1";
        bool tflag=1;
        for(auto c:status->roleplayer[QString("witch")])
            if(status->alive[c->username]&&!status->used2[c->username])
                askforonevote(c->username,QString("Witch")),tflag=0;
        if(tflag){
            stage=8;
            goto stage8;
        }
        return 0;
    }
    if(stage==8){
        stage8:
       for(auto c:status->roleplayer[QString("witch")])
           if(status->alive[c->username]&&!status->used2[c->username]){
               QString tmp=resforonevote(c->username);
               qDebug()<<"Witch poi "<<tmp;
               if(tmp.length())
                   poisoned[tmp]=1,status->used2[c->username]=1;
           }
        qDebug()<<"Witched2";
        bool tflag=1;
        for(auto c:status->roleplayer[QString("prophet")])
            if(status->alive[c->username])
                askforonevote(c->username,QString("Prophet")),tflag=0;
        if(tflag){
            stage=10;
            goto stage10;
        }
        return 0;
    }
    if(stage==10){
        stage10:
        for(auto c:status->roleplayer[QString("prophet")])
            if(status->alive[c->username]){
                QString tmp=resforonevote(c->username);
                qDebug()<<"Prophet verify "<<tmp;
                if(tmp.length())
                    sendMessage(c->username,((status->role[tmp]==QString("werewolf"))?QString("Bad"):QString("Good")));
            }
        qDebug()<<"Propheted";
        for(auto c:users)
            if((killed[c]&&(int(guarded[c])+int(saved[c])!=1))||poisoned[c])
                deadbuffer.push_back(c),poied[c]=poisoned[c];
        guarded.clear();killed.clear();saved.clear();poisoned.clear();
        stage=1;round++;
        int tres=dayround(round);
        if(tres)return tres;
        return 0;
    }
}
void Game::gameend(int res){
    room->broadcast("GameEnded");
    this->broadcast("werewolf",res==2?"YouWin":"YouLose",1);
    for(auto c:users)
        if(!status->canbroad(c,"werewolf",1))
            sendMessage(c,res==2?"YouLose":"YouWin");
    room->broadcast(QString("EndStatus\n")+status->showallstatus());
}
void Game::run(){
    qDebug()<<"Run";
    int res=0;
    if(stage&1)res=dayround(round);//奇数stage标号代表白天，偶数夜晚
    else res=nightround(round);
    if(!res)return;
    gameend(res);
}
