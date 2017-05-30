/********************************************************************************
** Form generated from reading UI file 'joinroom.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_JOINROOM_H
#define UI_JOINROOM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_joinroom
{
public:
    QLineEdit *lineEdit;
    QLabel *label;
    QPushButton *pushButton;
    QLabel *label_2;

    void setupUi(QDialog *joinroom)
    {
        if (joinroom->objectName().isEmpty())
            joinroom->setObjectName(QStringLiteral("joinroom"));
        joinroom->resize(400, 300);
        lineEdit = new QLineEdit(joinroom);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(70, 160, 113, 21));
        label = new QLabel(joinroom);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(40, 80, 311, 20));
        pushButton = new QPushButton(joinroom);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(230, 150, 81, 41));
        label_2 = new QLabel(joinroom);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(140, 230, 111, 16));

        retranslateUi(joinroom);

        QMetaObject::connectSlotsByName(joinroom);
    } // setupUi

    void retranslateUi(QDialog *joinroom)
    {
        joinroom->setWindowTitle(QApplication::translate("joinroom", "JoinRoom", 0));
        label->setText(QApplication::translate("joinroom", "\350\257\267\350\276\223\345\205\245\346\210\277\351\227\264\345\217\267\357\274\210\345\246\202\346\236\234\346\210\277\351\227\264\346\262\241\346\234\211\344\272\272\347\232\204\350\257\235\344\274\232\350\207\252\345\212\250\346\226\260\345\273\272\346\210\277\351\227\264\357\274\211", 0));
        pushButton->setText(QApplication::translate("joinroom", "\345\212\240\345\205\245\346\210\277\351\227\264", 0));
        label_2->setText(QApplication::translate("joinroom", "Oops\357\274\214\346\210\277\351\227\264\345\267\262\346\273\241", 0));
    } // retranslateUi

};

namespace Ui {
    class joinroom: public Ui_joinroom {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JOINROOM_H
