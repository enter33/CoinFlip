#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include <QTimer>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    // explicit MyCoin(QWidget *parent = nullptr);
    MyCoin(QString imgPath);

    bool flag;//正反 1正 0反
    int xpos;//x坐标
    int ypos;//y坐标

    QTimer* timer1;
    QTimer* timer2;
    void statusChange();

    int minImg;
    int maxImg;


signals:
};

#endif // MYCOIN_H
