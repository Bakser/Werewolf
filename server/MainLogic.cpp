#include "Handler.h"
#include <map>
#include <iostream>
#include <vector>
#include <sstream>
void EventHandler::sendMessage(QString username,QString message){
    networkInterface->sendMessage(username,message);
}
void EventHandler::tryHandle(QString username,QString message){
    if(this->canHandle(message))
        this->handle(username,message);
    else
        selectHandler(message)->tryHandle(username,message);
}
// int EventHandler::parseToInt(QString message){
//     bool flag=0;
//     int res=1;
//     for(auto c:message)
//         if(c==' ')flag=1;
//         else if(c=='\n')return res;
//         else if (flag)
//             res=res*(c-'0');
//     return res;
// }
// ServerCenter::ServerCenter(){
// }
ServerCenter::ServerCenter(ServerNetworkInterface* _networkInterface){
    this->networkInterface=_networkInterface;
}
bool ServerCenter::canHandle(QString message){
    return message[0]=='j'||(message[0]=='w'&&message[2]=='r');
}
void ServerCenter::handle(QString username,QString message){
    if(message[0]=='j'){
        int roomnumber=parseToInt(message);
        if(this->Rooms.count(roomnumber))
            this->Rooms[roomnumber]=new RoomHandler(this->networkInterface);//TODO
        this->Rooms[roomnumber]->tryHandle(username,message);
    }
    else if(message[0]=='w'&&message[2]=='r'){
        for(auto i:Rooms)
            i.second->broadcast(message);
    }
}
EventHandler* ServerCenter::selectHandler(QString message){
    return this->Rooms[parseToInt(message)];
}
RoomHandler::RoomHandler(ServerNetworkInterface* _networkInterface){
    this->networkInterface=_networkInterface;
    readycnt=0;
    gamestarted=0;
}
bool RoomHandler::canHandle(QString message){
    return message[0]=='j'||message[0]=='b'||message[0]=='l'||message[0]=='h'||message[0]=='s'||message[0]=='r';
}
EventHandler* RoomHandler::selectHandler(QString message){
    if(!gamestarted)
        std::cerr<<"Yao Shou La"<<std::endl;
    return game;
}
bool RoomHandler::EnterRoom(QString username){
    if(!users.size()){
        owner=username;
        sendMessage(username,QString("Owner"));
    }
    else{
        if(users.size()+1>setting[0])
            sendMessage(username,QString("Full"));
        else sendMessage(username,QString("Success"));
    }
    users.push_back(username);
    ready[username]=0;//这里不考虑username冲突
}
bool RoomHandler::LeaveRoom(QString username){
    bool flag=0;
    for(std::vector<QString>::iterator it=users.begin();it!=users.end();it++)
        if(*it==username){
            users.erase(it);
            flag=1;
            sendMessage(username,QString("Success"));
            break;
        }
    if(!flag)
        std::cerr<<"Yao Shou la!"<<std::endl;
}
bool RoomHandler::canStart(){
    return readycnt==users.size()&&users.size()==setting[0];
}
void RoomHandler::flush(){
    QString sta=get_status();
    for(auto i:users)
        sendMessage(i,sta);
    if(users[0]!=owner){
        sendMessage(users[0],QString("OwnerNew"));//注意可以半路更换房主
        owner=users[0];
    }
    sendMessage(owner,canStart()?QString("StartButton 1"):QString("StartButton 0"));
}
void RoomHandler::broadcast(QString message){
    for(auto i:users)
        sendMessage(i,message);
}
QString RoomHandler::get_status(){
    QString res("Status\n");
    for(auto i:setting)
        res+=IntToStr(i)+QString(" ");
    res+=QString("\n");
    for(auto i:users)
        res+=i+(ready[i]?" 1\n":" 0\n");//注意没有补足该有的行数
    return res;
}
void RoomHandler::buildroom(QString str){
    bool flag=0;int tmp=1;
    for(auto c:str)
        if(c=='\n')flag=1;
        else if(flag){
            if(c==' '){
                setting.push_back(tmp);
                tmp=1;
            }
            else
                tmp*=(c-'0');
        }
    if(setting.size()<7)
        setting.push_back(tmp);
}
void RoomHandler::handle(QString username,QString message){
    if(message[0]=='j')
        EnterRoom(username);
    else if(message[0]=='l')
        LeaveRoom(username);
    else if(message[0]=='b')
        buildroom(message);
    else if(message[0]=='u'){
        ready[username]=1;
        readycnt++;
    }
    else if(message[0]=='d'){
        ready[username]=0;
        readycnt--;
    }
    else if(message[0]=='r'){
        this->broadcast(message);
        if(gamestarted)
            game->tryHandle(username,message);//To be dicussed
    }
    else if(message[0]=='s')
        startgame();
    this->flush();
}
void RoomHandler::startgame(){
    gamestarted=1;
    game=new Game(users,setting,networkInterface,this);//传递应该有的信息
    this->broadcast(QString("Gamestarted"));
    game->run();//TODO
    delete game;
}
Player::Player(QString _username,QString _role){
    username=_username;
    role=_role;
    said=voted=0;
}
void Player::handle(QString message){
    if(message[4]=='c')said=1; //worldchat已经被过滤
    else if(message[0]=='v'){
        voted=1;
        int s=0,t=message.length();
        for(int i(0);i<message.length();i++)
            if(message[i]=='@')s=i+1;
            else if(message[i]=='\n')t=i;
        if(s>=t)lastvote=QString("");
        else lastvote=message.substring(s,t);
    }
    else special=1;//保证不是别的
}
//7
const QString roleToInt[]={QString("villager"),QString("werewolf"),QString("prophet"),QString("witch"),QString("defender"),QString("hunter")};
Gamestatus::Gamestatus(std::vector<QString> users,std::vector<int> _setting,Game* _game){
    setting=_setting;
    playerid=users;
    game=_game;
    int sum=0;
    std::vector<int>_roles;
    for(int i(1);i<7;i++)
        for(int j(0);j<setting[i];j++)
            _roles.push_back(i);
    for(int i(0);i<setting[0]-sum;i++)
        _roles.push_back(0);
    srand(time(0));
    std::random_shuffle(_roles);
    for(int i(0);i<users.size();i++){
        QString c=users[i];
        alive[c]=1;
        cap[c]=used1[c]=used2[c]=0;
        role[c]=roleToInt[_roles[i]];
        player[c]=new Player(c,roleToInt[_roles[i]]);
        if(!roleplayer.count(roleToInt[_roles[i]]))
            roleplayer[roleToInt[_roles[i]]]=std::vector<Player*>(player[c]);
        else roleplayer[roleToInt[_roles[i]]].push_back(player[c]);
    }
}
QString Gamestatus::showonestatus(QString name){
    return name+QString(" ")+role[name]+(alive[name]?QString(" 1"):QString(" 0"))+(cap[c]?QString(" 1\n"):QString(" 0\n"));;
}
QString Gamestatus::showalivestatus(){
    QString res;
    for(auto c:playerid)
        res+=c+(alive[c]?QString(" 1"):QString(" 0"))+(cap[c]?QString(" 1\n"):QString(" 0\n"));
    return res;
}
QString Gamestatus::showallstatus(){
    QString res;
    for(auto c:playerid)
        res+=showonestatus(c);
    return res;
}
bool Gamestatus::canbroad(QString username,QString type,bool f=0){
    return role[username]==type&&(alive[username]||f);
}
//QString("prophet"),QString("witch"),QString("defender"),QString("hunter"
int Gamestatus::judgeend(){//0 没结果 1 好人赢 2 狼人赢
    bool flag1=1,flag2=1,flag3=1;
    for(auto i:roleplayer[QString("werewolf")])
        if(alive[i->username])
            flag1=0;
    if(flag1)return 1;
    for(auto i:roleplayer[QString("villager")])
        if(alive[i->username])
            flag2=0;
    for(auto i:roleplayer[QString("prophet")])
        if(alive[i->username])
            flag3=0;
    for(auto i:roleplayer[QString("witch")])
        if(alive[i->username])
            flag3=0;
    for(auto i:roleplayer[QString("defender")])
        if(alive[i->username])
            flag3=0;
    for(auto i:roleplayer[QString("hunter")])
        if(alive[i->username])
            flag3=0; 
    if(flag2||flag3)return 2;
    return 0;
}
int Gamestatus::die(QString username){
    alive[username]=0;
    return judgeend();
}
void Gamestatus::changecap(QString username){
    for(auto c:playerid)
        cap[c]=0;
    cap[username]=1;
    return;
}
QString Gamestatus::vote(std::vector<Player*> voters){//投票过程 如果多人平票以@username\n格式返回
    static std::map<QString,double> mp;
    mp.clear();
    for(auto c:voters)
        if(c->lastvote!=QString("")){
            if(!mp.count(c->lastvote))mp[c->lastvote]=0.0;
            mp[c->lastvote]+=(cap[c->username]?1.5:1.0);
        }
    double tmp=0.0;QString res;
    bool flag=0;
    for(auto c:mp)
        if(mp.second>tmp){
            tmp=mp.second;
            res=mp.first;
            flag=0;
        }
        else if(mp.second==tmp){
            flag=1;
            if(!flag)res=nameform(res);
            res+=nameform(mp.first);
        }
    return res;
}
Game::Game(std::vector<QString> _users,std::vector<int> setting,ServerNetworkInterface* _networkInterface,EventHandler* _room){
    networkInterface=_networkInterface;
    room=_room;
    users=_users;
    status=new Gamestatus(_users,setting,this);
}
bool Game::canHandle(QString message){
    return 1;
}
EventHandler* Game::selectHandler(QString message){
    std::cerr<<"Yao Shou La"<<std::endl;
    return this;
}
bool Game::judgewait(){
    for(auto i:waitVote)
        if(!i->voted)
            return 0;
    for(auto i:waitMessage)
        if(!i->said)
            return 0;
    for(auto i:waitSpecial)
        if(!i->special)
            return 0;
    for(auto i:waitVote)
        i->voted=0;
    for(auto i:waitMessage)
        i->said=0;
    for(auto i:waitSpecial)
        i->special=0;
    //waitVote=waitMessage=waitSpecial=std::vector<Player*>();
    return 1;
}
void Game::set(QString username,bool vote,bool say,QString channel=QString("Room")){
    sendMessage(username,QString("Set\n")+(vote?QString("1 "):QString("0 "))+(say?QString("1 "):QString("0 "))+channel);
}
void Game::report(QString username){
    sendMessage(username,QString("Status\n")+status->showonestatus(username)+status->showalivestatus());
}
void Game::reportall(){
    for(auto c:status->playerid)
        report(c);
}
void Game::startAwaitsession(int msec){
    QTimer *timer = new QTimer(this);
    timer.setInterval(msec);
    QEventloop *loop = new QEventloop(this);
    timer->start();
    connect(timer, SIGNAL(timeout()), loop, SLOT(quit()));
    connect(this, SIGNAL(receiveOK()), loop, SLOT(quit()));
    loop.exec();
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
    if(judgewait())
        emit receiveOK();
}
QString Game::askforonevote(QString username,QString info,int msec=10000){//这里的计时请client调小点自己计，务必不要在计时结束后发包
    set(username,1,0);
    waitVote=waitMessage=std::vector<Player*>();
    waitVote.push_back(status->player[username]);
    status->player[username]->voted=0;
    if(info.length())
        sendMessage(username,info);
    startAwaitsession(msec);
    set(username,0,0);
    return status->player[username]->lastvote;
}
bool Game::askforonemessage(QString username,QString channel,QString info,int msec=20000){
    set(username,0,1,channel);
    waitVote=waitMessage=std::vector<Player*>();
    waitMessage.push_back(status->player[username]);
    status->player[username]->said=0;
    if(info.length())
        sendMessage(username,info);
    startAwaitsession(msec);
    set(username,0,0);
    return 1;
}
void Game::closeall(){
    for(auto c:users)
        set(c,0,0);
}
int deadclear(std::vector<QString> buffer,int say){
    if(buffer.empty())return 0;
    QString tmp=QString("Die\n");
    for(auto c:buffer){
        tmp+=nameform(c);
        sendMessage(c,"Youdie");
    }
    if(say!=2)room->broadcast(tmp);
    for(auto c:buffer)
        if(status->role[c]==QString("hunter")&&!poied[c]){
            QString tmp=askforonevote(c,"Carry");
            if(tmp.length()){
                deadclear(std::vector<QString>(tmp),2);
                room->broadcast(QString("Hunter\n")+nameform(c)+nameform(tmp);
            }
        }
    for(auto c:buffer)
        if(status->cap[c]){
            room->broadcast("Captaindie");
            QString tmp=askforonevote(c,"Pass");
            room->broadcast(QString("Captian\n")+nameform(tmp));
            if(tmp.length())
                status->changecap(tmp);
        }
    if(say){
        for(auto c:buffer)
            askforonemessage(c,"Room","Tellsth");
    }
    int res=0;
    for(auto c:buffer)
        res=max(res,status->die(c));
    reportall();
    return res;
}
QString Game::allvote(QString info,int msec){
    waitVote=waitMessage=std::vector<Player*>();
    for(auto c:users)
        if(status->alive[c]){
            waitVote.push_back(status->player[c]);
            status->player[c]->voted=0;
           }
    if(info.length())
        broadcast("Allalive",info);
    broadcast("Allalive","Set\n1 0 Room");
    startAwaitsession(10000);
    broadcast("Allalive","Set\n0 0 Room");
    return status->vote(waitVote);
}
int Game::dayround(int rn){
    room->broadcast(QString("Day ")+IntToStr(rn>>1));
    closeall();
    int tmp=deadclear(deadbuffer,rn==1);
    deadbuffer.clear();
    QString t;
    if(tmp)return tmp;
    tmp=deadclear(deadbuffer,1);
    if(rn==1){
        t=allvote("",10000);
        if(t[0]=='@')
            t=QString("");
        else status->changecap(t);
        broadcast("Allalive",QString("Captain\n")+nameform(t));
    }
    srand(time(0));
    int order=rand()&1,s=0,n=users.size();QString cap("");
    for(auto c:users)
        if(status->alive[c]&&status->cap[c]){
            cap=c;
            askforonevote(c,"Order");
            order=status->player[c]->lastvote[0]=='1';
        }
    if(cap.length()){
        for(int i(0);i<n;i++)
            if(users[i]==cap)
                s=i;
    }
    order=!order?-1:1;
    for(int i((s+order+n)%n);i!=s;i=(i+order+n)%n)
        askforonemessage(users[i],"Room","",15000);
    if(cap.length()) askforonemessage(cap,"Room","",20000);
    else askforonemessage(users[0],"Room","",15000);
    t=allvote("Vote",10000);
    if(t[0]=='@'){
        broadcast("Allalive",QString("Equal\n")+t);
        t=allvote("Vote",10000);
        if(t[0]!='@')
            deadbuffer.push_back(t);
    }
    else deadbuffer.push_back(t);
    tmp=deadclear(deadbuffer,1);
    if(tmp)return tmp;
}
int Game::nightround(int rn){
    room->broadcast(QString("Night ")+IntToStr(rn>>1));
    reportall();
    closeall();
    static std::map<QString,bool> guarded,killed,saved,poisoned;
    guarded.clear();killed.clear();saved.clear();poisoned.clear();
    static QString tmp;
    //守卫
    for(auto c:status->roleplayer[QString("defender")])
        if(status->alive[c->username]){
            tmp=askforonevote(c->username,QString("Guard"));
            if(tmp.length())
                guarded[tmp]=1;
        }
    //狼人
    waitVote=waitMessage=std::vector<Player*>();
    for(auto c:status->roleplayer[QString("werewolf")])
        if(status->alive[c->username]){
            waitVote.push_back(c);
            c->voted=0;
        }
    for(auto c:waitVote)
        set(c->username,1,1,QString("Wolf"));
    startAwaitsession(30000);
    for(auto c:waitVote)
        set(c->username,0,0);
    tmp=status->vote(waitVote);
    if(tmp[0]!='@')
        killed[tmp]=1;
    //女巫
    static QString killd=tmp;
    for(auto c:status->roleplayer[QString("witch")])
        if(status->alive[c->username]){
            if(!status->used1[c->username]){
                tmp=askforonevote(c->username,QString("Witch\n@")+killd);
                if(tmp.length())
                    saved[tmp]=1,status->used1[c->username]=1;
            }
            if(!status->used2[c->username]){
                tmp=askforonevote(c->username,QString("Witch"));
                if(tmp.length())
                    poisoned[tmp]=1,status->used2[c->username]=1;
            }
        }
    //预言家
    for(auto c:status->roleplayer[QString("prophet")])
        if(status->alive[c->username]){
            tmp=askforonevote(c->username,QString("Prophet"));
            if(tmp.length())
                sendMessage(c->username,(status->role[tmp]==QString("werewolf")?QString("Bad"):QString("Good")));
        }
    for(auto c:users)
        if((killed[c]&&(int(guarded[c])+int(saved[c])!=1))||poisoned[c])
            deadbuffer.push_back(c),poied[c]=1;
    return 0;
}
void Game::run(){
    int res=0;
    for(int round=0;;round++){
        if(round&1)res=dayround(round);
        else res=nightround(round);
        if(res)
            break;
    }
    room->broadcast("GameEnded");
    this->broadcast("werewolf",res==1?"YouWin":"YouLose",1);
    for(auto c:users)
        if(!status->canbroad(c,"werewolf",1))
            sendMessage(c,res==1?"YouLose":"YouWin");
    room->broadcast(QString("EndStatus\n")+status->showallstatus());
}
