#include "mainwindow.h"
#include <QApplication>
#include<QPushButton>
#include <QSplashScreen>
#include <QDesktopWidget>
#include <QWidget>
#include<QGraphicsScene>
#include<QGraphicsLineItem>
#include<QTimer>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QSplashScreen *splash=new QSplashScreen;
    QPixmap pix("D:/360zip/QTproject/Datastructure_linklist/icon/1.png");
    splash->showMessage("Waiting for loading....");
    splash->setPixmap(pix);
    for(qint64 i=666666;i>0;i--)
        splash->show();
    a.processEvents();//这样可以保证程序一直可以响应鼠标键盘上事件
    splash->finish(&w);//启动画面在窗口w创建完成以后结束



    QPixmap pixmap("D:/360zip/QTproject/untitled1/image/14.jpg");//设定图片
    QPalette palette;//创建一个调色板对象
    palette.setBrush(w.backgroundRole(),QBrush(pixmap));//用调色板的画笔把映射到pixmap上的图片画到frame.backgroundRole()这个背景上
   //palette.setColor(frame->backgroundRole(),QColor(192,253,123));
    w.setPalette(palette);//设置窗口调色板为palette，窗口和画笔相关联
    //w.setMask(pixmap.mask()); //可以将图片中透明部分显示为透明的
    w.setAutoFillBackground(true);//设置窗体自动填充背景

    w.setWindowTitle("DataStructure Course Design @TYP2018");
    w.show();
    return a.exec();
}
