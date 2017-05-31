/********************************************************************************
** Form generated from reading UI file 'vote.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VOTE_H
#define UI_VOTE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_vote
{
public:
    QListWidget *listWidget;
    QPushButton *pushButton;
    QLabel *label;
    QPushButton *yes;
    QPushButton *no;

    void setupUi(QDialog *vote)
    {
        if (vote->objectName().isEmpty())
            vote->setObjectName(QStringLiteral("vote"));
        vote->resize(413, 249);
        listWidget = new QListWidget(vote);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(10, 10, 381, 161));
        pushButton = new QPushButton(vote);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(270, 180, 113, 32));
        label = new QLabel(vote);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 190, 241, 16));
        yes = new QPushButton(vote);
        yes->setObjectName(QStringLiteral("yes"));
        yes->setGeometry(QRect(90, 220, 80, 24));
        no = new QPushButton(vote);
        no->setObjectName(QStringLiteral("no"));
        no->setGeometry(QRect(240, 220, 80, 24));

        retranslateUi(vote);

        QMetaObject::connectSlotsByName(vote);
    } // setupUi

    void retranslateUi(QDialog *vote)
    {
        vote->setWindowTitle(QApplication::translate("vote", "Dialog", 0));
        pushButton->setText(QApplication::translate("vote", "\346\212\225\347\245\250", 0));
        label->setText(QString());
        yes->setText(QApplication::translate("vote", "Yes", 0));
        no->setText(QApplication::translate("vote", "No", 0));
    } // retranslateUi

};

namespace Ui {
    class vote: public Ui_vote {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VOTE_H
