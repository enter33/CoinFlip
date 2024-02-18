#include "levelwindow.h"
#include "mypushbutton.h"
#include <QMenuBar>
#include <QPainter>
#include <QLabel>
#include "mycoin.h"
#include "dataconfig.h"
#include <QTimer>
#include <QPropertyAnimation>
#include <QMessageBox>

levelWindow::levelWindow(int level,QWidget *parent)
    : QMainWindow{parent}
{
    this->levelindex = level;
    this->score = 0;
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

    //添加退出按钮
    MyPushButton* backBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(), this->height()-backBtn->height());

    connect(backBtn,&QPushButton::clicked,[=](){
        emit this->backBtnSignal();
    });

    //创建显示关卡的文本
    QLabel *label = new QLabel;
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    QString str1 = QString("Level: %1").arg(this->levelindex);
    label->setParent(this);
    label->setFont(font);
    label->setText(str1);
    label->setGeometry(30, this->height()-50, 130, 50);

    //加载胜利的图片
    QLabel* succeedLabel = new QLabel();
    QPixmap pix;
    pix.load(":/res/LevelCompletedDialogBg.png");
    succeedLabel->setPixmap(pix);
    succeedLabel->setParent(this);
    succeedLabel->setGeometry(0,0,pix.width(),pix.height());
    succeedLabel->move((this->width()-pix.width())*0.5, -pix.height());
    //获取配置文件
    dataconfig conf(this);

    //关卡绘制
    for(int i = 0;i<4;i++)
    {
        for(int j = 0;j<4;j++)
        {
            //创建背景
            QLabel *bglabel = new QLabel;
            QPixmap pix;
            pix.load(":/res/BoardNode.png");
            bglabel->setPixmap(pix);
            bglabel->setParent(this);
            bglabel->setGeometry(0,0,pix.width(),pix.height());
            bglabel->move(57+i*pix.width(),200+j*pix.height());

            //创建硬币按钮
            QString imgPath;
            if(conf.mData[this->levelindex][i][j] == 1)
            {
                imgPath = ":/res/Coin0001.png";
            }
            else
            {
                imgPath = ":/res/Coin0008.png";
            }

            MyCoin* mycoin = new MyCoin(imgPath);
            mycoin->flag = conf.mData[this->levelindex][i][j];
            mycoin->xpos = i;
            mycoin->ypos = j;
            mycoin->setParent(this);

            this->score += conf.mData[this->levelindex][i][j];

            //硬币按钮移至背景中间
            mycoin->move(bglabel->x()+(bglabel->width()-mycoin->width())*0.5,bglabel->y()+(bglabel->height()-mycoin->height())*0.5);

            coinVertex[i][j] = mycoin;

            //监听硬币按钮
            connect(mycoin,&QPushButton::clicked,[=](){
                mycoin->statusChange();
                if(mycoin->flag == 0)
                {
                    this->score --;
                }
                else
                {
                    this->score ++;
                }
                //设定延迟
                QTimer::singleShot(200,[=](){
                    //设置周围硬币一同翻转
                    if(mycoin->xpos+1<4)
                    {
                        // qDebug()<<"aaa";
                        coinVertex[mycoin->xpos+1][mycoin->ypos]->statusChange();
                        if(coinVertex[mycoin->xpos+1][mycoin->ypos]->flag == 0)
                        {
                            this->score --;
                        }
                        else
                        {
                            this->score ++;
                        }
                    }
                    if(mycoin->xpos-1>-1)
                    {
                        coinVertex[mycoin->xpos-1][mycoin->ypos]->statusChange();
                        if(coinVertex[mycoin->xpos-1][mycoin->ypos]->flag == 0)
                        {
                            this->score --;
                        }
                        else
                        {
                            this->score ++;
                        }
                    }
                    if(mycoin->ypos+1<4)
                    {
                        coinVertex[mycoin->xpos][mycoin->ypos+1]->statusChange();
                        if(coinVertex[mycoin->xpos][mycoin->ypos+1]->flag == 0)
                        {
                            this->score --;
                        }
                        else
                        {
                            this->score ++;
                        }
                    }
                    if(mycoin->ypos-1>-1)
                    {
                        coinVertex[mycoin->xpos][mycoin->ypos-1]->statusChange();
                        if(coinVertex[mycoin->xpos][mycoin->ypos-1]->flag == 0)
                        {
                            this->score --;
                        }
                        else
                        {
                            this->score ++;
                        }
                    }

                    //计算是否通关
                    if(this->score == 16)
                    {
                        // qDebug()<<"succeed";

                        //将胜利的图片降下来
                        QPropertyAnimation *animation = new QPropertyAnimation(succeedLabel, "geometry");
                        //设置动画时间间隔
                        animation->setDuration(1000);
                        //起始位置
                        animation->setStartValue(QRect(succeedLabel->x(), succeedLabel->y(), succeedLabel->width(), succeedLabel->height()));
                        //结束位置
                        animation->setEndValue(QRect(succeedLabel->x(), succeedLabel->y()+110, succeedLabel->width(), succeedLabel->height()));
                        //设置缓和曲线
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        //执行动画
                        animation->start();

                        QTimer::singleShot(500,[=](){
                            QMessageBox::warning(this,"succeed","恭喜过关");
                            emit this->backBtnSignal();
                        });
                    }
                });
            });
        }
    }

    // //监听succeed信号
    // connect(this,&levelWindow::succeed,this,[=](){


    // });
}

//重写绘图事件
void levelWindow::paintEvent(QPaintEvent*)
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
