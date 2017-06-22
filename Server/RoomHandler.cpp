/*
名称：RoomHandler.cpp
作者：计62 王晓智 2016011257
时间：2017.5.30
内容：实现房间类RoomHandler
版权：全部自行完成

每个函数的功能参见RoomHandler.h
*/
#include "RoomHandler.h"
RoomHandler::RoomHandler(ServerNetworkInterface* _networkInterface){
    this->networkInterface=_networkInterface;
    readycnt=0;
    gamestarted=0;
}
bool RoomHandler::canHandle(QString message){//根据客户端传来的包的格式判断能否处理这个包，格式规定见逻辑主文档
    return message[0]=='j'||message[0]=='b'||message[0]=='l'||message[0]=='u'||message[0]=='d'||message[0]=='s'||message[0]=='r';
}
EventHandler* RoomHandler::selectHandler(QString message){
    return game;
}
bool RoomHandler::EnterRoom(QString username){
    if(!users.size()){//如果房间之前没有人，这个用户就是房主
        owner=username;
        sendMessage(username,QString("Owner"));
    }
    else{
        if(users.size()+1>setting[0])
            sendMessage(username,QString("Full"));
        else sendMessage(username,QString("Success"));
    }
    users.push_back(username);
    ready[username]=0;
}
void RoomHandler::LeaveRoom(QString username){
    for(std::vector<QString>::iterator it=users.begin();it!=users.end();it++)
        if(*it==username){
            users.erase(it);
            sendMessage(username,QString("Success"));
            break;
        }
}
bool RoomHandler::canStart(){//房间内人数满足房主设定而且都准备好了
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
        res+=i+(ready[i]?" 1\n":" 0\n");
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
                tmp*=(c.toLatin1()-'0');
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
    else if(message[0]=='u'){//用户举手准备
        ready[username]=1;
        readycnt++;
    }
    else if(message[0]=='d'){//用户放下手，没准备好
        ready[username]=0;
        readycnt--;
    }
    else if(message[0]=='r'){//用户发送了房间聊天信息
        this->broadcast(message);//先向房间内所有用户广播该信息
        if(gamestarted)
            game->tryHandle(username,message);//如果游戏已经开始，roomchat涉及到游戏逻辑，交给Game处理
    }
    else if(message[0]=='s')
        startgame();
    if(setting.size()&&!gamestarted)
           this->flush();
}
void RoomHandler::startgame(){
    gamestarted=1;
    game=new Game(users,setting,networkInterface,this);
    this->broadcast(QString("Gamestarted"));
    game->run();//TODO
    //delete game;
}
