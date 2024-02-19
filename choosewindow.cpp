#include "choosewindow.h"
#include <QPainter>
#include <QMenuBar>
#include "mypushbutton.h"
#include <QLabel>
#include "levelwindow.h"

chooseWindow::chooseWindow(QWidget *parent)
    : QMainWindow{parent}
{
    //设置窗口大小
    this->setFixedSize(320,588);

    //设置窗口图标和title
    this->setWindowIcon(QIcon(":/D:res/Coin0001.png"));
    this->setWindowTitle("翻金币");

    //添加菜单、菜单栏
    QMenuBar *mybar = menuBar();
    setMenuBar(mybar);
    QMenu *startMenu = mybar->addMenu("开始");//创建开始菜单
    QAction *quitAction = startMenu->addAction("退出"); //场景退出的菜单项
    connect(quitAction, &QAction::triggered, [=](){
        this->close();
    });

    //添加退出按钮
    MyPushButton* backBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(), this->height()-backBtn->height());

    connect(backBtn,&QPushButton::clicked,[=](){
        emit this->backBtnSignal();
    });

    //绘制关卡选择按钮
    for(int i = 0;i<20;i++)
    {
        //添加关卡选择按钮
        MyPushButton* levelBtn = new MyPushButton(":/res/LevelIcon.png");
        levelBtn->setParent(this);

        levelBtn->move(25+i%4*70, 130+i/4*70);

        //添加文本
        QLabel* label = new QLabel(QString::number(i+1),this);
        label->resize(QSize(levelBtn->width(),levelBtn->height()));
        //设置文本垂直水平居中
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        //设置label穿透，使点击操作到按钮上
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
        //移动文本到正确的位置上
        label->move(25+i%4*70, 130+i/4*70);

        connect(levelBtn,&QPushButton::clicked,[=](){
            //转到游戏界面
            levelWindow* levelScene = new levelWindow(i+1,this);
            this->hide();
            levelScene->show();
            connect(levelScene,&levelWindow::backBtnSignal,[=](){
                levelScene->close();
                delete levelScene;
                this->show();
            });
        });
    }
}


//重写绘图事件
void chooseWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pix;
    //绘制底图
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //绘制标题
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width()*0.5, pix.height()*0.5);//对图片进行缩放
    painter.drawPixmap(10,30,pix);
}
