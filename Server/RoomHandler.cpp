#include "RoomHandler.h"
RoomHandler::RoomHandler(ServerNetworkInterface* _networkInterface){
    this->networkInterface=_networkInterface;
    readycnt=0;
    gamestarted=0;
}
bool RoomHandler::canHandle(QString message){
    qDebug()<<"RoomMLGBD";
    return message[0]=='j'||message[0]=='b'||message[0]=='l'||message[0]=='u'||message[0]=='d'||message[0]=='s'||message[0]=='r';
}
EventHandler* RoomHandler::selectHandler(QString message){
    qDebug()<<"SelectMLGBD";
    if(!gamestarted)
        qDebug()<<"Yao Shou la";
    return game;
}
bool RoomHandler::EnterRoom(QString username){
    qDebug()<<"Entered";
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
                tmp*=(c.toLatin1()-'0');//to be
        }
    if(setting.size()<7)
        setting.push_back(tmp);
}
void RoomHandler::handle(QString username,QString message){
    this->broadcast(QString("room handler handle:Gamestarted"));
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
    if(setting.size())
           this->flush();
}
void RoomHandler::startgame(){
    gamestarted=1;
    //this->broadcast(QString("Gamestarted"));
    game=new Game(users,setting,networkInterface,this);//传递应该有的信息
    this->broadcast(QString("Gamestarted"));
    game->run();//TODO
    delete game;
}

void RoomHandler::sendMessage(QString username, QString message)
{
    networkInterface->sendMessage(username, message);
}
