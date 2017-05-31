/********************************************************************************
** Form generated from reading UI file 'drawcard.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DRAWCARD_H
#define UI_DRAWCARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCommandLinkButton>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_drawcard
{
public:
    QPushButton *pushButton;
    QFrame *frame;
    QCommandLinkButton *commandLinkButton;

    void setupUi(QDialog *drawcard)
    {
        if (drawcard->objectName().isEmpty())
            drawcard->setObjectName(QStringLiteral("drawcard"));
        drawcard->resize(400, 300);
        pushButton = new QPushButton(drawcard);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(140, 20, 113, 32));
        frame = new QFrame(drawcard);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(80, 70, 221, 211));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        commandLinkButton = new QCommandLinkButton(drawcard);
        commandLinkButton->setObjectName(QStringLiteral("commandLinkButton"));
        commandLinkButton->setGeometry(QRect(320, 230, 61, 41));

        retranslateUi(drawcard);

        QMetaObject::connectSlotsByName(drawcard);
    } // setupUi

    void retranslateUi(QDialog *drawcard)
    {
        drawcard->setWindowTitle(QApplication::translate("drawcard", "DrawCard", 0));
        pushButton->setText(QApplication::translate("drawcard", "\346\212\275\345\217\226\345\215\241\347\211\214", 0));
        commandLinkButton->setText(QApplication::translate("drawcard", "\345\274\200\345\247\213", 0));
    } // retranslateUi

};

namespace Ui {
    class drawcard: public Ui_drawcard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DRAWCARD_H
