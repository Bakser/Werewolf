/********************************************************************************
** Form generated from reading UI file 'newroom.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWROOM_H
#define UI_NEWROOM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_newroom
{
public:
    QLabel *label;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QSpinBox *spinBox;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QSpinBox *spinBox_3;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_4;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_5;
    QPushButton *pushButton;
    QLabel *label_3;

    void setupUi(QDialog *newroom)
    {
        if (newroom->objectName().isEmpty())
            newroom->setObjectName(QStringLiteral("newroom"));
        newroom->resize(400, 300);
        label = new QLabel(newroom);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(130, 70, 101, 16));
        horizontalLayoutWidget = new QWidget(newroom);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(30, 110, 111, 31));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(horizontalLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        spinBox = new QSpinBox(horizontalLayoutWidget);
        spinBox->setObjectName(QStringLiteral("spinBox"));

        horizontalLayout->addWidget(spinBox);

        horizontalLayoutWidget_3 = new QWidget(newroom);
        horizontalLayoutWidget_3->setObjectName(QStringLiteral("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(30, 160, 111, 31));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(horizontalLayoutWidget_3);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_3->addWidget(label_4);

        spinBox_3 = new QSpinBox(horizontalLayoutWidget_3);
        spinBox_3->setObjectName(QStringLiteral("spinBox_3"));

        horizontalLayout_3->addWidget(spinBox_3);

        verticalLayoutWidget = new QWidget(newroom);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(210, 100, 101, 131));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        checkBox = new QCheckBox(verticalLayoutWidget);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        verticalLayout->addWidget(checkBox);

        checkBox_2 = new QCheckBox(verticalLayoutWidget);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));

        verticalLayout->addWidget(checkBox_2);

        checkBox_4 = new QCheckBox(verticalLayoutWidget);
        checkBox_4->setObjectName(QStringLiteral("checkBox_4"));

        verticalLayout->addWidget(checkBox_4);

        checkBox_3 = new QCheckBox(verticalLayoutWidget);
        checkBox_3->setObjectName(QStringLiteral("checkBox_3"));

        verticalLayout->addWidget(checkBox_3);

        checkBox_5 = new QCheckBox(verticalLayoutWidget);
        checkBox_5->setObjectName(QStringLiteral("checkBox_5"));

        verticalLayout->addWidget(checkBox_5);

        pushButton = new QPushButton(newroom);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(120, 240, 113, 32));
        label_3 = new QLabel(newroom);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(40, 260, 321, 16));

        retranslateUi(newroom);

        QMetaObject::connectSlotsByName(newroom);
    } // setupUi

    void retranslateUi(QDialog *newroom)
    {
        newroom->setWindowTitle(QApplication::translate("newroom", "CreateNewRoom", 0));
        label->setText(QApplication::translate("newroom", "\351\200\211\346\213\251\345\220\204\350\247\222\350\211\262\344\272\272\346\225\260", 0));
        label_2->setText(QApplication::translate("newroom", "\346\235\221\346\260\221", 0));
        label_4->setText(QApplication::translate("newroom", "\347\213\274\344\272\272", 0));
        checkBox->setText(QApplication::translate("newroom", "\345\245\263\345\267\253", 0));
        checkBox_2->setText(QApplication::translate("newroom", "\347\214\216\344\272\272", 0));
        checkBox_4->setText(QApplication::translate("newroom", "\351\242\204\350\250\200\345\256\266", 0));
        checkBox_3->setText(QApplication::translate("newroom", "\345\256\210\345\215\253", 0));
        checkBox_5->setText(QApplication::translate("newroom", "\350\255\246\351\225\277", 0));
        pushButton->setText(QApplication::translate("newroom", "\345\274\200\345\247\213\346\270\270\346\210\217", 0));
        label_3->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class newroom: public Ui_newroom {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWROOM_H
