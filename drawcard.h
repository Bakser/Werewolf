#ifndef DRAWCARD_H
#define DRAWCARD_H

#include <QDialog>

namespace Ui {
class drawcard;
}

class drawcard : public QDialog
{
    Q_OBJECT

public:
    explicit drawcard(QWidget *parent = 0);
    ~drawcard();

private slots:
    void on_pushButton_clicked();

    void on_graphicsView_destroyed();

private:
    Ui::drawcard *ui;
};

#endif // DRAWCARD_H