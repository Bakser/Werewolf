#ifndef MAINWINDOWPLAY_H
#define MAINWINDOWPLAY_H

#include <QMainWindow>

namespace Ui {
class MainWindowplay;
}

class MainWindowplay : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowplay(QWidget *parent = 0);
    ~MainWindowplay();

private:
    Ui::MainWindowplay *ui;
};

#endif // MAINWINDOWPLAY_H
