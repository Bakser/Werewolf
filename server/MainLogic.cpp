#include "MainLogic.h"
#include <map>
#include <iostream>
void EventHandler::sendMessage(Qstring username,Qstring message){
    networkInterface->sendMessage(username,message);
}
void EventHandler::tryHandle(Qstring username,Qstring message){
    if(this->canHandle(message))
        this->handle(message);
    else
        selectHandler(message)->tryHandle(username,message);
}
int EventHandler::parseToInt(Qstring message){
    bool flag=0;
    int res=1;
    for(auto c:message)
        if(c==' ')flag=1;
        else if(c=='\n')return res;
        else if (flag)
            res=res*(c-'0');
    return res;
}
ServerCenter::ServerCenter(ServerNetworkInterface* _networkInterface){
    this->networkInterface=_networkInterface;
}
virtual bool ServerCenter::canHandle(Qstring message){
    return message[0]=='j'||(message[0]=='w'&&message[2]=='r');
}
virtual void ServerCenter::handle(Qstring username,Qstring message){
    if(message[0]=='j'){
        int roomnumber=parseToInt(message);
        if(this->Rooms.count(roomnumber))
            this->Rooms[roomnumber]=new RoomHandler(this->networkInterface);//TODO
        this->Rooms[roomnumber]->tryHandle(username,message);
    }
    else if(message[0]=='w'&&message[2]=='r')){
        for(auto i:rooms)
            i.second->broadcast(message);
    }
}
virtual EventHandler* ServerCenter::selectHandler(Qstring message){
    return this->Rooms[parseToInt(message)];
}
RoomHandler::RoomHandler(ServerNetworkInterface* _networkInterface){
    this->networkInterface=_networkInterface;
    readycnt=0;
    gamestarted=0;
}
virtual bool RoomHandler::canHandle(Qstring message){
    return message[0]=='j'||message[0]=='b'||message[0]=='l'||message[0]=='h'||message[0]=='s'||message[0]=='r';
}
virtual EventHandler* RoomHandler::selectHandler(Qstring message){
    if(!gamestarted)
        std::cerr<<"Yao Shou La"<<std::endl;
    return game;
}
bool RoomHandler::EnterRoom(Qstring username){
    if(!users.size()){
        owner=username;
        sendMessage(username,Qstring("Owner"));
    }
    else{
        if(users.size()+1>setting[0])
            sendMessage(username,Qstring("Full"));
        else sendMessage(username,Qstring("Success"));
    }
    users.push_back(username);
    ready[username]=0;//这里不考虑username冲突
}
bool RoomHandler::LeaveRoom(Qstring username){
    bool flag=0;
    for(vector<Qstring>::iterator it=users.begin();it!=users.end();it++)
        if(*it==username){
            users.erase(it);
            flag=1;
            sendMessage(username,Qstring("Success"));
            break;
        }
    if(!flag)
        std::cerr<<"Yao Shou la!"<<std::endl;
}
bool RoomHandler::canStart(){
    return readycnt==users.size()&&users.size()==setting[0];
}
void RoomHandler::flush(){
    Qstring sta=get_status();
    for(auto i:users)
        sendMessage(i,sta);
    if(users[0]!=owner){
        sendMessage(users[0],Qstring("OwnerNew"));//注意可以半路更换房主
        owner=user[0];
    }
    sendMessage(owner,canStart()?Qstring("StartButton 1"):Qstring("StartButton 0"));
}
void RoomHandler::broadcast(Qstring message){
    for(auto i:users)
        sendMessage(i,message);
}
Qstring RoomHandler::get_status(){
    Qstring res("Status\n");
    for(auto i:setting)
        res+=IntToStr(i)+Qstring(" ");//此处行尾有一个空格
    res+=Qstring("\n")；
    for(auto i:users)
        res+=i+(ready[i]?" 1\n":" 0\n");//注意没有补足该有的行数
    return res;
}
void RoomHandler::buildroom(Qstring str){
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
virtual void RoomHandler::handle(Qstring username,Qstring message){
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
            game->receivechat(username,message);//To be dicussed
    }
    else if(message[0]=='s')
        startgame();
    this->flush();
}
void RoomHandler::startgame(){
    gamestarted=1;
    game=new Game(users,setting,networkInterface,this);//传递应该有的信息
    this->broadcast(Qstring("Gamestarted"));
    game->run();//TODO
    delete game;
}
Player::Player(Qstring _username,Qstring _role){
    username=_username;
    role=_role;
    said=voted=0;
}
void Player::handle(Qstring message){
    if(message[4]=='c')said=1; //worldchat已经被过滤
    else if(message[0]=='v'){
        voted=1;
        int s=0,t=message.length();
        for(int i(0);i<message.length();i++)
            if(message[i]=='@')s=i+1;
            else if(message[i]=='\n')t=i;
        if(s>=t)lastvote=Qstring("");
        else lastvote=message.substring(s,t);
    }
    else special=1;//保证不是别的
}
//7
const Qstring roleToInt[]={Qstring("villager"),Qstring("werewolf"),Qstring("prophet"),Qstring("witch"),Qstring("defender"),Qstring("hunter")};
Gamestatus::Gamestatus(vector<Qstring> users,vector<int> _setting){
    setting=_setting;
    playerid=users;
    int sum=0;
    vector<int>_roles;
    for(int i(1);i<7;i++)
        for(int j(0);j<setting[i];j++)
            _roles.push_back(i);
    for(int i(0);i<setting[0]-sum;i++)
        _roles.push_back(0);
    srand(time(0));
    random_shuffle(_roles);
    for(int i(0);i<users.size();i++){
        Qstring c=users[i];
        alive[c]=1;
        cap[c]=0;
        role[c]=roleToInt[_roles[i]];
        player[c]=new Player(c,roleToInt[_roles[i]]);
        if(!roleplayer.count(roleToInt[_roles[i]]))
            roleplayer[roleToInt[_roles[i]]]=vector<Player*>(player[c]);
        else roleplayer[roleToInt[_roles[i]]].push_back(player[c]);
    }
}
Qstring Gamestatus::showonestatus(Qstring name){
    return name+Qstring(" ")+role[name]+(alive[name]?Qstring(" 1"):Qstring(" 0"))+(cap[c]?Qstring(" 1\n"):Qstring(" 0\n"));;
}
Qstring Gamestatus::showalivestatus(){
    Qstring res;
    for(auto c:playerid)
        res+=c+(alive[c]?Qstring(" 1"):Qstring(" 0"))+(cap[c]?Qstring(" 1\n"):Qstring(" 0\n"));
    return res;
}
Qstring Gamestatus::showallstatus(){
    Qstring res;
    for(auto c:playerid)
        res+=showonestatus(c);
    return res;
}
bool Gamestatus::canbroad(Qstring username,Qstring type,bool f=0){
    return role[username]==type&&(alive[username]||f);
}
//Qstring("prophet"),Qstring("witch"),Qstring("defender"),Qstring("hunter"
int Gamestatus::judgeend(){//0 没结果 1 好人赢 2 狼人赢
    bool flag1=1,flag2=1,flag3=1;
    for(auto i:roleplayer[Qstring("werewolf")])
        if(alive[i->username])
            flag1=0;
    if(flag1)return 1;
    for(auto i:roleplayer[Qstring("villager")])
        if(alive[i->username])
            flag2=0;
    for(auto i:roleplayer[Qstring("prophet")])
        if(alive[i->username])
            flag3=0;
    for(auto i:roleplayer[Qstring("witch")])
        if(alive[i->username])
            flag3=0;
    for(auto i:roleplayer[Qstring("defender")])
        if(alive[i->username])
            flag3=0;
    for(auto i:roleplayer[Qstring("hunter")])
        if(alive[i->username])
            flag3=0; 
    if(flag2||flag3)return 2;
    return 0;
}
int Gamestatus::die(Qstring username){
    alive[username]=0;
    return judgeend();
}
void Gamestatus::changecap(Qstring username){
    for(auto c:playerid)
        cap[c]=0;
    cap[username]=1;
    return;
}
Qstring Gamestatus::vote(vector<Player*> voters){
    static map<Qstring,double> mp;
    mp.clear();
    for(auto c:voters)
        if(c->lastvote!=Qstring("")){
            if(!mp.count(c->lastvote))mp[c->lastvote]=0.0;
            mp[c->lastvote]+=(cap[c->username]?1.5:1.0);
        }
    double tmp=0.0;Qstring res;
    for(auto c:mp)
        if(mp.second>tmp){
            tmp=mp.second;
            res=mp.first;
        }
    return res;
}
Game::Game(vector<Qstring> _users,vector<int> setting,ServerNetworkInterface* _networkInterface,EventHandler* _room){
    networkInterface=_networkInterface;
    room=_room;
    users=_users;
    status=new Gamestatus(_users,setting);
}
bool Game::canHandle(Qstring message){
    return 1;
}
EventHandler* Game::selectHandler(Qstring message){
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
    waitVote=waitMessage=waitSpecial=vector<Player*>();
    return 1;
}
void Game::set(Qstring username,bool vote,bool say,Qstring channel=Qstring("Room")){
    sendMessage(username,Qstring("Set\n")+(vote?Qstring("1 "):Qstring("0 "))+(say?Qstring("1 "):Qstring("0 "))+channel);
}
void Game::report(Qstring username){
    sendMessage(username,Qstring("Status\n")+status->showonestatus(username)+status->showalivestatus());
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
void Game::broadcast(Qstring type,Qstring message,bool f=0){
    for(auto c:users)
        if(status->canbroad(c,type,f))
            sendMessage(c,message);
}
void Game::handle(Qstring username,Qstring message){
    if(message[0]=='w'&&message[4]=='c')
        broadcast(Qstring("werewolf"),message);
    status->player[username]->handle(message);
    if(judgewait())
        emit receiveOK();
}
int Game::dayround(int rn){
}
int Game::nightround(int rn){
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
    room->broadcast(Qstring("EndStatus\n")+status->showallstatus());
}