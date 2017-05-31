/********************************************************************************
** Form generated from reading UI file 'waitroom.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WAITROOM_H
#define UI_WAITROOM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCommandLinkButton>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_waitroom
{
public:
    QLabel *label;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label_2;
    QLabel *label_3;
    QCommandLinkButton *commandLinkButton;
    QPushButton *pushButton_3;
    QLabel *statusLabel;

    void setupUi(QDialog *waitroom)
    {
        if (waitroom->objectName().isEmpty())
            waitroom->setObjectName(QStringLiteral("waitroom"));
        waitroom->resize(400, 300);
        label = new QLabel(waitroom);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(70, 130, 111, 16));
        pushButton = new QPushButton(waitroom);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(220, 100, 113, 32));
        pushButton->setStyleSheet(QStringLiteral("QPushButton { background-color: rgb(255, 132, 139); border-radius: 3px; color: rgb(255, 255, 255); } QPushButton:hover { background-color: rgb(245, 69, 234); }"));
        pushButton_2 = new QPushButton(waitroom);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(220, 140, 113, 32));
        pushButton_2->setStyleSheet(QStringLiteral("QPushButton { background-color: rgb(255, 132, 139); border-radius: 3px; color: rgb(255, 255, 255); } QPushButton:hover { background-color: rgb(245, 69, 234); }"));
        label_2 = new QLabel(waitroom);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(150, 200, 81, 16));
        label_3 = new QLabel(waitroom);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(150, 230, 101, 16));
        commandLinkButton = new QCommandLinkButton(waitroom);
        commandLinkButton->setObjectName(QStringLiteral("commandLinkButton"));
        commandLinkButton->setGeometry(QRect(310, 250, 81, 41));
        pushButton_3 = new QPushButton(waitroom);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(20, 210, 81, 71));
        statusLabel = new QLabel(waitroom);
        statusLabel->setObjectName(QStringLiteral("statusLabel"));
        statusLabel->setGeometry(QRect(40, 20, 331, 61));

        retranslateUi(waitroom);

        QMetaObject::connectSlotsByName(waitroom);
    } // setupUi

    void retranslateUi(QDialog *waitroom)
    {
        waitroom->setWindowTitle(QApplication::translate("waitroom", "Dialog", 0));
        label->setText(QApplication::translate("waitroom", "\345\207\206\345\244\207\345\245\275\344\272\206\350\257\267\344\270\276\346\211\213", 0));
        pushButton->setText(QApplication::translate("waitroom", "\360\237\231\213", 0));
        pushButton_2->setText(QApplication::translate("waitroom", "\360\237\230\224", 0));
        label_2->setText(QApplication::translate("waitroom", "\344\275\240\347\216\260\345\234\250\345\234\250\344\270\276\346\211\213", 0));
        label_3->setText(QApplication::translate("waitroom", "\344\275\240\347\216\260\345\234\250\346\224\276\344\270\213\344\272\206\346\211\213", 0));
        commandLinkButton->setText(QApplication::translate("waitroom", "\347\246\273\345\274\200\346\210\277\351\227\264", 0));
        pushButton_3->setText(QApplication::translate("waitroom", "\345\274\200\345\247\213\346\270\270\346\210\217", 0));
        statusLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class waitroom: public Ui_waitroom {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WAITROOM_H
