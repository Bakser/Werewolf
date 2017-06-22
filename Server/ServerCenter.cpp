/*
名称：ServerCenter.cpp
作者：计62 王晓智 2016011257
时间：2017.5.30
内容：实现服务中心类
版权：全部自行完成
*/
#include "ServerCenter.h"

QString IntToStr(int x){//数转换成QString
    return QString::number(x);
}
QString nameform(QString x){//将用户ID转换成包中的姓名格式
    if(x[0]=='@')return x;
    return QString("@")+x+QString("\n");
}
ServerCenter::ServerCenter(ServerNetworkInterface* _networkInterface){
    this->networkInterface=_networkInterface;
}
bool ServerCenter::canHandle(QString message){//只能处理加入房间，世界频道聊天两种请求
    if(!message.length())return 1;
    return message[0]=='j'||(message[0]=='w'&&message[2]=='r');
}
void ServerCenter::handle(QString username,QString message){
    if(!message.length())return;
    if(message[0]=='j'){
        int roomnumber=parseToInt(message);
        //qDebug()<<roomnumber;
        if(!this->Rooms.count(roomnumber))//如果没有这个房间号对应的房间，新建一个
            this->Rooms[roomnumber]=new RoomHandler(this->networkInterface);//TODO
        //qDebug()<<"To Enter"<<this->Rooms[roomnumber];
        this->Rooms[roomnumber]->tryHandle(username,message);//加入该房间过程交给房间类处理
    }
    else if(message[0]=='w'&&message[2]=='r'){//世界喊话，对每个房间都广播一遍
        for(auto i:Rooms)
            i.second->broadcast(message);
    }
}
EventHandler* ServerCenter::selectHandler(QString message){
    return this->Rooms[parseToInt(message)];
}
