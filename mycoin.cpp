#include "mycoin.h"

// MyCoin::MyCoin(QWidget *parent)
//     : QWidget{parent}
// {}

MyCoin::MyCoin(QString imgPath)
{
    QPixmap pix;
    bool ret = pix.load(imgPath);

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

    //初始化定时器
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);

    this->minImg = 1;
    this->maxImg = 8;

    //监听定时器
    connect(timer1,&QTimer::timeout,this,[=](){
        QString imgPath = QString(":/res/Coin000%1.png").arg(this->minImg++);
        QPixmap pix;

        bool ret = pix.load(imgPath);

        if(ret == 0)
        {
            qDebug()<<"金币翻转绘制错误";
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

        if(this->minImg > this->maxImg)
        {
            this->minImg = 1;
            timer1->stop();
        }
    });

    connect(timer2,&QTimer::timeout,this,[=](){
        QString imgPath = QString(":/res/Coin000%1.png").arg(this->maxImg--);
        QPixmap pix;

        bool ret = pix.load(imgPath);

        if(ret == 0)
        {
            qDebug()<<"金币翻转绘制错误";
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

        if(this->maxImg < this->minImg)
        {
            this->maxImg = 8;
            timer2->stop();
        }
    });
}

void MyCoin::statusChange()
{
    if(this->flag)
    {
        //金币翻银币
        timer1->start(30);
        this->flag = 0;
    }
    else
    {
        //银币翻金币
        timer2->start(30);
        this->flag = 1;
    }
}
