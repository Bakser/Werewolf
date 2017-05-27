#include "ServerCenter.h"

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
    qDebug()<<"MLGBD"<<message;
    return message[0]=='j'||(message[0]=='w'&&message[2]=='r');
}
void ServerCenter::handle(QString username,QString message){
    if(message[0]=='j'){
        int roomnumber=parseToInt(message);
        qDebug()<<roomnumber;
        if(!this->Rooms.count(roomnumber))
            this->Rooms[roomnumber]=new RoomHandler(this->networkInterface);//TODO
        qDebug()<<"To Enter"<<this->Rooms[roomnumber];
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
QString IntToStr(int x){
    return QString::number(x);
}
QString nameform(QString x){
    if(x[0]=='@')return x;
    return QString("@")+x+QString("\n");
}
