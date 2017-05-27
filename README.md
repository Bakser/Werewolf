# Werewolf
## Deadline 2017/05/31
## [Last Update 2017/05/27 16:23]

### Client接收包方法

引用```clientnetworkinterface.h/cpp```，在类中进行初始化

```c++
ClientNetworkInterface *clientNetworkInterface = new ClientNetworkInterface();
```

在你的类中进行连接:

```C++
connect(clientNetworkInterface, SIGNAL(ReceiveCommand(QString)),
        this, SLOT(handle(QString)));
```

你的类需要实现```void handler(QString message)```，也即网络接口接收到一条来自服务器的指令```message```会调用这个函数。

给服务器发送消息，调用函数```clientNetworkInterface->addString(message)```，其中```message```类型为```QString```。

### Server-Client用法

1. 首先运行Server程序。
2. 打开Client程序（可以多开看看效果），可以发现上边有状态栏提示当前状态，以及用户名、要说的话两个文本框，同时还有Login，Say，Exit三个按钮。
3. 在用户名栏输入一个用户名，单击Login按钮。
4. 登陆成功后，状态栏提示登陆成功，此时Say按钮可用，在say一栏写下要说的话单击say按钮。
5. 说话的人以及说的话可以在服务器的运行栏中的```3 Application Output```中看到。（这之中同时也保留了一些通信细节）

### Features

1. 成熟的服务器端实现，无需指定ip地址，充分利用异步机制，可以无阻塞地在服务器上同时运行多局游戏。（可以对中途离线有基本处理）
2. 美观的GUI
3. 可复用、易拓展的代码。



