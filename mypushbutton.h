#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    // explicit MyPushButton(QWidget *parent = nullptr);
    MyPushButton(QString startImg,QString endImg = "",QWidget *parent = nullptr);

    QString startImg;
    QString endImg;

    void move_up();
    void move_down();

    void mousePressEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);
signals:
};

#endif // MYPUSHBUTTON_H
