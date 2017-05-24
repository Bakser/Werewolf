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
    random_shuffle(_roles);
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