#ifndef LEVELWINDOW_H
#define LEVELWINDOW_H

#include <QMainWindow>
#include "mycoin.h"

class levelWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit levelWindow(int level,QWidget *parent = nullptr);

    void paintEvent(QPaintEvent*);
    int levelindex;

    MyCoin* coinVertex[4][4];

    int score;//分数，为16时通关
signals:
    void backBtnSignal();
    void succeed();
};

#endif // LEVELWINDOW_H
