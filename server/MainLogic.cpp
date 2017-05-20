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
/*
Game开始前的client向server数据格式 xxxxx代表房间号
join xxxxx

build xxxxx     //向用户发送你是房主后才要求一个build包指定房间类型 换行一定要标准的\n
xx xx xx xx xx xx     //几个人 几个狼 几个预言家 几个守卫 几个猎人 几个警长（0/1）行尾最好多一个空格

leave xxxxx

up xxxxx

down xxxxx

start xxxxx
*/
virtual bool ServerCenter::canHandle(Qstring message){
    return message[0]=='j';
}
virtual void ServerCenter::handle(Qstring username,Qstring message){
    int roomnumber=parseToInt(message);
    if(this->Rooms.count(roomnumber))
        this->Rooms[roomnumber]=new RoomHandler(this->networkInterface);//TODO
    this->Rooms[roomnumber]->tryHandle(username,message);
}
virtual EventHandler* ServerCenter::selectHandler(Qstring message){
    return this->Rooms[parseToInt(message)];
}
/*
向用户发的包的格式
Status    //每次收到Status包刷新一次页面
xx xx xx xx  //设置
user1 0/1 //用户与是否举手，不足，需client自己补全
user2 0/1

Success

Owner

OwnerNew

Full //房间满了

StartButton 0/1 //给房主
*/
RoomHandler::RoomHandler(ServerNetworkInterface* _networkInterface){
    this->networkInterface=_networkInterface;
    readycnt=0;
}
virtual bool RoomHandler::canHandle(Qstring message){
    return message[0]=='j'||message[0]=='b'||message[0]=='l'||message[0]=='h'||message[0]=='s';
}
virtual EventHandler* RoomHandler::selectHandler(Qstring message){
    std::cerr<<"Yao Shou La"<<std::endl;
    return this;
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
    if(setting.size()<6)
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
    else if(message[0]=='s')
        startgame();
    this->flush();
}
void RoomHandler::startgame(){
    game=new Game(users,setting);//传递应该有的信息
    game->run();//TODO
    delete game;
}
