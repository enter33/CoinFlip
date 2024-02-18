#include "mypushbutton.h"
#include <QPainter>
#include <QPropertyAnimation>

// MyPushButton::MyPushButton(QWidget *parent)
//     : QWidget{parent}
// {}

MyPushButton::MyPushButton(QString startImg,QString endImg,QWidget *parent)
{
    this->startImg = startImg;
    this->endImg = startImg;
    this->setParent(parent);

    QPixmap pix;
    bool ret = pix.load(startImg);

    if(ret == 0)
    {
        qDebug()<<"开始按钮绘制错误";
        return;
    }

    //设置图片固定大小
    this->setFixedSize(pix.width(), pix.height());

    //设置不规则图片的样式
    this->setStyleSheet("QPushButton{border:0px}");

    //设置图标
    this->setIcon(pix);

    //设置图标大小
    this->setIconSize(QSize(pix.width(), pix.height()));
}


void MyPushButton::move_up()
{
    //创建动画
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    //设置动画时间间隔
    animation->setDuration(100);
    //起始位置
    animation->setStartValue(QRect(this->x(), this->y()+10, this->width(), this->height()));
    //结束位置
    animation->setEndValue(QRect(this->x(), this->y(), this->width(), this->height()));
    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start();
}

void MyPushButton::move_down()
{
    //创建动画
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    //设置动画时间间隔
    animation->setDuration(100);
    //起始位置
    animation->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));
    //结束位置
    animation->setEndValue(QRect(this->x(), this->y()+10, this->width(), this->height()));
    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start();
}

void MyPushButton::mousePressEvent(QMouseEvent* e)
{
    if(!this->endImg.isEmpty())
    {
        QPixmap pix;
        bool ret = pix.load(endImg);

        if(ret == 0)
        {
            qDebug()<<"开始按钮绘制错误";
            return;
        }

        //设置图片固定大小
        this->setFixedSize(pix.width(), pix.height());

        //设置不规则图片的样式
        this->setStyleSheet("QPushButton{border:0px}");

        //设置图标
        this->setIcon(pix);

        //设置图标大小
        this->setIconSize(QSize(pix.width(), pix.height()));
    }

    //让父类执行其他内容
    return QPushButton::mousePressEvent(e);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent* e)
{
    if(!this->endImg.isEmpty())
    {
        QPixmap pix;
        bool ret = pix.load(startImg);

        if(ret == 0)
        {
            qDebug()<<"开始按钮绘制错误";
            return;
        }

        //设置图片固定大小
        this->setFixedSize(pix.width(), pix.height());

        //设置不规则图片的样式
        this->setStyleSheet("QPushButton{border:0px}");

        //设置图标
        this->setIcon(pix);

        //设置图标大小
        this->setIconSize(QSize(pix.width(), pix.height()));
    }

    //让父类执行其他内容
    return QPushButton::mouseReleaseEvent(e);
}

