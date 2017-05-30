#ifndef WAITROOM_H
#define WAITROOM_H

#include <QDialog>
#include "eventhandler.h"
#include <QCloseEvent>
#include "mainwindowplay.h"
#include <QLabel>

namespace Ui {
class waitroom;
}

class waitroom : public QDialog, public EventHandler
{
    Q_OBJECT

public:
    explicit waitroom(ClientNetworkInterface*, QWidget *parent = 0);
    ~waitroom();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_commandLinkButton_clicked();

    void on_pushButton_3_clicked();

    void start();

signals:
    void onclose();
private:
    Ui::waitroom *ui;
    void handle(QString s);
    bool canHandle(QString s);
    EventHandler* selectHandler(QString s);
    void closeEvent(QCloseEvent*);
    MainWindowplay *p;
};

#endif // WAITROOM_H
