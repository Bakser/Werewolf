#Werewolf

## <red>Deadline 2017/05/31</red>

## [Last Update 2017/05/23 19:15]

### Server-Client用法

1. 首先运行Server程序。
2. 打开Client程序（可以多开看看效果），可以发现上边有状态栏提示当前状态，以及用户名、要说的话两个文本框，同时还有Login，Say，Exit三个按钮。
3. 在用户名栏输入一个用户名，单击Login按钮。
4. 登陆成功后，状态栏提示登陆成功，此时Say按钮可用，在say一栏写下要说的话单击say按钮。
5. 说话的人以及说的话可以在服务器的运行栏中的```3 Application Output```中看到。（这之中同时也保留了一些通信细节）

### 使用Server部分代码

在```main.cpp```中修改```ServerNetworkInterface```的```mainHandler```指针，从现在的```NaiveHandler```换为之前实现的```ServerCenter```。

可以参考```NaiveHandler```的实现。

### 使用Client部分代码

只需注意```main.qml```的用法。在其中无须注意```clientNetworkInterface```内部函数的实现。

使用```clientNetworkInterface.addString(string s)```来给服务器传送信息。比如```main.qml```第$96$行。

重点实现```function clientHandle(message)```，表示接收到服务器一条信息```message```之后要做出什么反应。可以参考```main.qml```从$122$行开始的此函数。

### To Do List

1. 用户登录时相同用户名的用户已经存在设定为无法登陆（使say按钮激活），但是没有明显提示信息。
2. 客户端从服务器断开时，服务器端的某些内存没有释放，且没有提示此用户已断开连接。
3. 客户端GUI的可变控件（比如数量不定的按钮）暂时还未考虑。







