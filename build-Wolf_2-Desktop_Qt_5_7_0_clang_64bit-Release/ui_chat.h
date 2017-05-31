/********************************************************************************
** Form generated from reading UI file 'chat.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHAT_H
#define UI_CHAT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_chat
{
public:
    QWidget *centralwidget;
    QLineEdit *werewolfMessageEdit;
    QLineEdit *roomMessageEdit;
    QListWidget *roomMessage;
    QPushButton *werewolfSend;
    QPushButton *roomSend;
    QLabel *label;
    QLabel *label_2;
    QListWidget *werewolfMessage;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *chat)
    {
        if (chat->objectName().isEmpty())
            chat->setObjectName(QStringLiteral("chat"));
        chat->resize(328, 540);
        centralwidget = new QWidget(chat);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        werewolfMessageEdit = new QLineEdit(centralwidget);
        werewolfMessageEdit->setObjectName(QStringLiteral("werewolfMessageEdit"));
        werewolfMessageEdit->setGeometry(QRect(20, 170, 281, 31));
        roomMessageEdit = new QLineEdit(centralwidget);
        roomMessageEdit->setObjectName(QStringLiteral("roomMessageEdit"));
        roomMessageEdit->setGeometry(QRect(20, 410, 281, 31));
        roomMessage = new QListWidget(centralwidget);
        roomMessage->setObjectName(QStringLiteral("roomMessage"));
        roomMessage->setGeometry(QRect(20, 250, 281, 151));
        werewolfSend = new QPushButton(centralwidget);
        werewolfSend->setObjectName(QStringLiteral("werewolfSend"));
        werewolfSend->setGeometry(QRect(180, 210, 113, 31));
        roomSend = new QPushButton(centralwidget);
        roomSend->setObjectName(QStringLiteral("roomSend"));
        roomSend->setGeometry(QRect(190, 450, 113, 32));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 210, 71, 21));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(30, 450, 91, 21));
        werewolfMessage = new QListWidget(centralwidget);
        werewolfMessage->setObjectName(QStringLiteral("werewolfMessage"));
        werewolfMessage->setGeometry(QRect(20, 0, 271, 151));
        chat->setCentralWidget(centralwidget);
        menubar = new QMenuBar(chat);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 328, 22));
        chat->setMenuBar(menubar);
        statusbar = new QStatusBar(chat);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        chat->setStatusBar(statusbar);

        retranslateUi(chat);

        QMetaObject::connectSlotsByName(chat);
    } // setupUi

    void retranslateUi(QMainWindow *chat)
    {
        chat->setWindowTitle(QApplication::translate("chat", "MainWindow", 0));
        werewolfSend->setText(QApplication::translate("chat", "\345\217\221\351\200\201", 0));
        roomSend->setText(QApplication::translate("chat", "\345\217\221\351\200\201", 0));
        label->setText(QApplication::translate("chat", "<html><head/><body><p><span style=\" font-size:18pt;\">\347\213\274\344\272\272\351\242\221\351\201\223</span></p></body></html>", 0));
        label_2->setText(QApplication::translate("chat", "<html><head/><body><p><span style=\" font-size:18pt;\">\346\210\277\351\227\264\351\242\221\351\201\223</span></p></body></html>", 0));
    } // retranslateUi

};

namespace Ui {
    class chat: public Ui_chat {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHAT_H
