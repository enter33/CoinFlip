#ifndef CHOOSEWINDOW_H
#define CHOOSEWINDOW_H

#include <QMainWindow>

class chooseWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit chooseWindow(QWidget *parent = nullptr);

    //重写绘图事件
    void paintEvent(QPaintEvent*);

signals:
    void backBtnSignal();
};

#endif // CHOOSEWINDOW_H
