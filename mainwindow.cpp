#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPainter>
#include "mypushbutton.h"
#include "choosewindow.h"
#include <QDebug>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //设置窗口大小
    this->setFixedSize(320,588);

    //设置窗口图标和title
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));
    this->setWindowTitle("翻金币");

    //添加菜单、菜单栏
    QMenuBar *mybar = menuBar();
    setMenuBar(mybar);
    QMenu *startMenu = mybar->addMenu("开始");//创建开始菜单
    QAction *quitAction = startMenu->addAction("退出"); //场景退出的菜单项
    connect(quitAction, &QAction::triggered, [=](){
        this->close();
    });

    //创建选择关卡界面
    chooseWindow* chooseScene = new chooseWindow(this);

    //接收回退信号并处理
    connect(chooseScene,&chooseWindow::backBtnSignal,[=](){
        chooseScene->hide();//隐藏关卡选择界面
        this->show();
    });

    //添加开始按钮
    MyPushButton* startbtn = new MyPushButton(":/res/MenuSceneStartButton.png","",this);
    startbtn->setParent(this);

    //移动开始按钮位置
    startbtn->move(this->width()*0.5 - startbtn->width()*0.5, this->height()*0.7);

    //设置槽函数
    connect(startbtn,&QPushButton::clicked,[=](){
        // qDebug()<<"按下了开始按钮";
        startbtn->move_down();
        startbtn->move_up();

        QTimer::singleShot(500,[=](){
            this->hide();
            chooseScene->show();
        });

    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

//重写绘图事件
void MainWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pix;
    //绘制底图
    pix.load(":/res/MenuSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
