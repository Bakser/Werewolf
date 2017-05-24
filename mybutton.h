#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QObject>
#include <QPushButton>

class MyButton:public QPushButton
{
    Q_OBJECT
public:
    MyButton(QWidget *parent=0);
    MyButton(QString & path, QString text, QWidget *parent=0);
    ~MyButton();
    enum BtnStatus{NORMAL,PRESSED,HOVER};
protected:
    void paintEvent(QPaintEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    //
private:
    BtnStatus m_status;
    QPixmap Img;
    QString txt;
};

#endif // MYBUTTON_H
