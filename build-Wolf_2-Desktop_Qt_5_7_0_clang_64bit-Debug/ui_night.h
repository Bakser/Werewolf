/********************************************************************************
** Form generated from reading UI file 'night.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NIGHT_H
#define UI_NIGHT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_night
{
public:
    QLabel *label;

    void setupUi(QDialog *night)
    {
        if (night->objectName().isEmpty())
            night->setObjectName(QStringLiteral("night"));
        night->resize(400, 300);
        label = new QLabel(night);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 0, 401, 301));

        retranslateUi(night);

        QMetaObject::connectSlotsByName(night);
    } // setupUi

    void retranslateUi(QDialog *night)
    {
        night->setWindowTitle(QApplication::translate("night", "\345\244\251\351\273\221\350\257\267\351\227\255\347\234\274", 0));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class night: public Ui_night {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NIGHT_H
