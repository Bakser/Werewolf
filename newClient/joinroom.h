#ifndef JOINROOM_H
#define JOINROOM_H

#include <QDialog>
#include "globals.h"
#include "eventhandler.h"
#include "waitroom.h"
#include "newroom.h"

namespace Ui {
class joinroom;
}

class joinroom : public QDialog, public EventHandler
{
    Q_OBJECT

public:
    explicit joinroom(ClientNetworkInterface*, QWidget *parent = 0);
    ~joinroom();

private slots:
    void on_pushButton_clicked();
    void success();
    void full();
    void owner();

    //void on_lineEdit_editingFinished();

private:
    Ui::joinroom *ui;
    void handle(QString s);
    bool canHandle(QString s);
    EventHandler* selectHandler(QString s);
    waitroom *dr;
};

#endif // JOINROOM_H
