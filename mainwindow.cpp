#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsItem>
#include <QMessageBox>
#include <QColorDialog>
#include <QTimer>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QStack>
#include <QQueue>
#include <synchapi.h>
#include <qt_windows.h>
#include <Windows.h>
//#include <QMediaPlayer>
#pragma execution_character_set("utf-8")
const static double PI=3.1415926;
int visited[max];
int visited1[max];
int temp_visited_2[MAX];
QString temp_direction;
QString Graph_name;
QString temp_direction_DFS_2018;

//QString stack_state;
//int stack_in;
//int stack_out;

QGraphicsScene *scene;
QGraphicsView *view;

int *visitedline;
int num_visited;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);


    music();
    initMenuBar();
    initStatusBar();
    myConnect();

}
void MainWindow::on_actionQt_triggered()
{
    QMessageBox::aboutQt(this,tr("关于Qt"));
}
void MainWindow::on_actionAuthor_triggered()
{
    QMessageBox box;
    box.setWindowTitle(tr("About the author"));
    box.setIcon(QMessageBox::Information);
    box.setText(tr("Author:1652262\n"
                   "School:TJ\n"
                   "Major:Computer Science \n"
                   "Emai:2458048592@qq.com \n"));
    box.addButton(tr("确定"),QMessageBox::AcceptRole);
    if(box.exec() == QMessageBox::Accepted)
        box.close();
}
void MainWindow::initMenuBar()
{
    QMenuBar *menuB = menuBar() ;//添加菜单
    QMenu *pfile = menuB->addMenu("Address");
    menuB->addMenu("Help");
    menuB->addMenu("About the author");

}
void MainWindow::music()
{
    player = new QMediaPlayer;
    connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    player->setMedia(QUrl::fromLocalFile("D:/360zip/QTproject/untitled1/image/a.mp3"));
    player->setVolume(30);
    player->play();
}
void MainWindow::myConnect()
{

    connect(ui->textBrowser_3, SIGNAL(cursorPositionChanged()), this, SLOT(autoScroll()));
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpdate()));
    timer->start(1000);
}
void MainWindow::autoScroll() {
    //QTextCursor cursor= ui-&gt;textBrowser_3-&gt;textCursor();
    //cursor.movePosition(QTextCursor::End);
    //ui-&gt;textBrowser_3-&gt;setTextCursor(cursor);
}
void sleep(unsigned int msec)
{
    QTime reachTime=QTime::currentTime().addMSecs(msec);
    while(QTime::currentTime()<reachTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
}
void MainWindow::timerUpdate()
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd");
    statusLabel2->setText(str);
}
void MainWindow::initStatusBar()
{
    QStatusBar* bar = ui->statusBar;
    statusLabel1=new QLabel;
    statusLabel1->setMinimumSize(200,10);
    statusLabel1->setFrameShape(QFrame::Box);
    statusLabel1->setFrameShadow(QFrame::Sunken);

    statusLabel2 = new QLabel;
    statusLabel2->setMinimumSize(200,10);
    statusLabel2->setFrameShape(QFrame::Box);
    statusLabel2->setFrameShadow(QFrame::Sunken);

    statusLabel3 = new QLabel;
    statusLabel3->setMinimumSize(200,10);
    statusLabel3->setFrameShape(QFrame::Box);
    statusLabel3->setFrameShadow(QFrame::Sunken);

    bar->addWidget(statusLabel1);
    bar->addWidget(statusLabel2);
    bar->addWidget(statusLabel3);
    statusLabel1->setText(tr("Student ID:1652262"));
    statusLabel2->setText(tr("0000-00-00 00:00::00 week"));
    statusLabel3->setText(tr("CopyRight@Yuanpeng Tu2018"));
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd");
    statusLabel2->setText(str);
}
MainWindow::~MainWindow()
{
    delete ui;
}

//----------------------------第一部分判断输入部分函数------------------
int turn_valueSTR(QCharRef a)
{
   if(a=='0')return 0;
   else if(a=='1')return 1;
   else if(a=='2')return 2;
   else if(a=='3')return 3;
   else if(a=='4')return 4;
   else if(a=='5')return 5;
   else if(a=='6')return 6;
   else if(a=='7')return 7;
   else if(a=='8')return 8;
   else if(a=='9')return 9;
   else return false;
}

int graph_nodirection_nopower_judge(int graph_style,int **&link_matrix,QString valueSTR,int &length_link)
{
    if(graph_style==1)//无权无向图输入正确性判断
    {
        int linenum=0;
        int queue=0;
        for(int i=0;i<valueSTR.length();i++)
        {
           if(valueSTR[i]=='0'||valueSTR[i]=='1')
           {
               linenum++;//计算输入数字个数判断是否为完全平方数
               if(i+1<valueSTR.length())
               {
                   if(valueSTR[i+1]==' '||valueSTR[i+1]=='\n')
                       ;
                   else
                      return false;

               }
           }
           else if(valueSTR[i]==' '||valueSTR[i]=='\n')
               ;
           else
               return false;
        }
        if(linenum!=int(sqrt(linenum))*int(sqrt(linenum)))
            return false;
        link_matrix=new int*[int(sqrt(linenum))];
        for(int i=0;i<int(sqrt(linenum));i++)
            link_matrix[i]=new int[int(sqrt(linenum))];

        for(int i=0;i<valueSTR.length();i++)
        {
           if(valueSTR[i]=='0'||valueSTR[i]=='1')
           {

               link_matrix[int(queue/int(sqrt(linenum)))][queue%int(sqrt(linenum))]=turn_valueSTR(valueSTR[i]);
               queue++;
           }
        }
        for(int i=0;i<int(sqrt(linenum));i++)
            for(int j=0;j<int(sqrt(linenum));j++)
                if(link_matrix[i][j]!=link_matrix[j][i]||link_matrix[i][i]==1)
                {
                    for(int i=0;i<int(sqrt(linenum));i++)
                        delete link_matrix[i];
                    delete link_matrix;
                    return false;
                }
        length_link=int(sqrt(linenum));
        return true;
    }
    else if(graph_style==2)//无权有向图输入正确性判断
    {

        int linenum=0;
        for(int i=0;i<valueSTR.length();i++)
        {
           if(valueSTR[i]=='0')
           {
               linenum++;//计算输入数字个数判断是否为完全平方数

           }
           else if(valueSTR[i]=='1')
           {
               linenum++;
           }
           else if(valueSTR[i]==' '||valueSTR[i]=='\n')
               ;
           else return false;
        }
        if(linenum!=int(sqrt(linenum))*int(sqrt(linenum)))
            return false;

        link_matrix=new int*[int(sqrt(linenum))];
        for(int i=0;i<int(sqrt(linenum));i++)
            link_matrix[i]=new int[int(sqrt(linenum))];


        int link_place=0;
        for(int i=0;i<valueSTR.length();i++)
        {
          if(valueSTR[i]=='0'||valueSTR[i]=='1')
          {
              link_matrix[link_place/int(sqrt(linenum))][link_place%int(sqrt(linenum))]=turn_valueSTR(valueSTR[i]);
              link_place++;
          }
//          if(valueSTR[i]>='0'&&valueSTR[i]<='9')
//          {
//            int j;
//            int count;
//            int num=0;
//            for(j=i;j<valueSTR.length()&&(valueSTR[j]>='0'&&valueSTR[j]<='9');j++);

//            for(count=j-1;count>=i;count--)
//            {
//                int data=turn_valueSTR(valueSTR[count]);
//                num= num+data*pow(10,count-j+1);
//            }
//            i=j;
//            link_matrix[link_place/int(sqrt(linenum))][link_place%int(sqrt(linenum))]=num;
//            link_place++;
//          }
        }
        for(int i=0;i<int(sqrt(linenum));i++)
            if(link_matrix[i][i]==1)
                return false;
        length_link=int(sqrt(linenum));

        return true;
    }
    else if(graph_style==3)//有权无向图输入正确性判断
    {
        int linenum=0;
        for(int i=0;i<valueSTR.length();i++)
        {
           if(valueSTR[i]=='0')
           {
               linenum++;//计算输入数字个数判断是否为完全平方数

           }
           else if(valueSTR[i]>='1'&&valueSTR[i]<='9')
           {
               int j;
               for(j=i;j<valueSTR.length()&&(valueSTR[j]>='1'&&valueSTR[j]<='9');j++);
               linenum++;
               i=j;
           }
           else if(valueSTR[i]==' '||valueSTR[i]=='\n')
               ;
           else return false;
        }
        if(linenum!=int(sqrt(linenum))*int(sqrt(linenum)))
            return false;

        link_matrix=new int*[int(sqrt(linenum))];
        for(int i=0;i<int(sqrt(linenum));i++)
            link_matrix[i]=new int[int(sqrt(linenum))];


        int link_place=0;
        for(int i=0;i<valueSTR.length();i++)
        {
          if(valueSTR[i]>='0'&&valueSTR[i]<='9')
          {
            int j;
            int count;
            int num=0;
            for(j=i;j<valueSTR.length()&&(valueSTR[j]>='0'&&valueSTR[j]<='9');j++);

            for(count=j-1;count>=i;count--)
            {
                int data=turn_valueSTR(valueSTR[count]);
                num= num+data*pow(10,count-j+1);
            }
            i=j;
            link_matrix[link_place/int(sqrt(linenum))][link_place%int(sqrt(linenum))]=num;
            link_place++;
          }
        }
        for(int i=0;i<int(sqrt(linenum));i++)
            for(int j=0;j<int(sqrt(linenum));j++)
                if(link_matrix[i][j]!=link_matrix[j][i]||link_matrix[i][i]>0)
                {
                    for(int i=0;i<int(sqrt(linenum));i++)
                        delete link_matrix[i];
                    delete link_matrix;
                    return false;
                }
        length_link=int(sqrt(linenum));
        return true;
    }
    else if(graph_style==4)//有权有向图输入正确性性判断
    {
        int linenum=0;
        for(int i=0;i<valueSTR.length();i++)
        {
           if(valueSTR[i]=='0')
           {
               linenum++;//计算输入数字个数判断是否为完全平方数

           }
           else if(valueSTR[i]>='1'&&valueSTR[i]<='9')
           {
               int j;
               for(j=i;j<valueSTR.length()&&(valueSTR[j]>='1'&&valueSTR[j]<='9');j++);
               linenum++;
               i=j;
           }
           else if(valueSTR[i]==' '||valueSTR[i]=='\n')
               ;
           else return false;
        }
        if(linenum!=int(sqrt(linenum))*int(sqrt(linenum)))
            return false;

        link_matrix=new int*[int(sqrt(linenum))];
        for(int i=0;i<int(sqrt(linenum));i++)
            link_matrix[i]=new int[int(sqrt(linenum))];


        int link_place=0;
        for(int i=0;i<valueSTR.length();i++)
        {
          if(valueSTR[i]>='0'&&valueSTR[i]<='9')
          {
            int j;
            int count;
            int num=0;
            for(j=i;j<valueSTR.length()&&(valueSTR[j]>='0'&&valueSTR[j]<='9');j++);

            for(count=j-1;count>=i;count--)
            {
                int data=turn_valueSTR(valueSTR[count]);
                num= num+data*pow(10,count-j+1);
            }
            i=j;
            link_matrix[link_place/int(sqrt(linenum))][link_place%int(sqrt(linenum))]=num;
            link_place++;
          }
        }
        for(int i=0;i<int(sqrt(linenum));i++)
            if(link_matrix[i][i]>0)
                return false;
        length_link=int(sqrt(linenum));
        return true;
    }
    return true;
}
void MainWindow::on_countBtn_clicked()
{
    QString tempStr;
    QString valueStr=ui->textEdit->toPlainText();
    int **link_matrix;//存储图矩阵信息的二维数组
    int graph_style;//图的类型 1代表无权无向图 2代表无权有向图 3代表有权无向图 4代表有权有向图
    ui->pushButton->setText("Ensure");
    ui->textEdit_2->setText("");
    if(ui->radioButton_4->isChecked())
    {
    graph_style=1;
    }
    else if(ui->radioButton_3->isChecked())
    {
    graph_style=2;
    }
    else if(ui->radioButton_2->isChecked())
    {
    graph_style=3;
    }
    else if(ui->radioButton->isChecked())
    {
    graph_style=4;
    }
    int length_link;
    bool flag_input=graph_nodirection_nopower_judge(graph_style,link_matrix,valueStr,length_link);

    if(graph_style==1&&flag_input)
    {
        //ui->textBrowser->setText(QString::number(length_link,10));
        QString linklist="";
        link_matrix_store=link_matrix;
        vexnum=length_link;
        for(int i=0;i<length_link;i++)
        {
            linklist+=QString::number(i,10)+":";
            for(int j=0;j<length_link;j++)
            {
                if(link_matrix[i][j]==1)
                {
                    linklist+=QString::number(j,10)+"->";

                }
            }
            linklist+="END\n";

        }
        //ui->countBtn->setText(QString::number(valueStr.length(),10));
        ui->textBrowser->setText(linklist);
    }
    else if(graph_style==2&&flag_input)
    {
        QString linklist="";
        link_matrix_store=link_matrix;
        for(int i=0;i<length_link;i++)
        {
            linklist+=QString::number(i,10)+":";
            for(int j=0;j<length_link;j++)
            {
                //link_matrix_store[i][j]=link_matrix[i][j];
                if(link_matrix[i][j]==1)
                {
                    linklist+=QString::number(j,10)+"->";

                }
            }
            linklist+="END\n";

        }
        vexnum=length_link;
        //ui->countBtn->setText(QString::number(vexnum,10));
        ui->textBrowser->setText(linklist);
    }
    else if(graph_style==3&&flag_input)
    {
        QString linklist="";
        vexnum=length_link;
        link_matrix_store=new int*[vexnum];
        for(int i=0;i<vexnum;i++)
            link_matrix_store[i]=new int[vexnum];
        for(int i=0;i<length_link;i++)
        {
            linklist+=QString::number(i,10)+":";
            for(int j=0;j<length_link;j++)
            {
                link_matrix_store[i][j]=link_matrix[i][j];
                if(link_matrix[i][j]>0)
                {
                    linklist+=QString::number(j,10)+"(power:"+QString::number(link_matrix[i][j],10)+")"+"->";

                }
            }
            linklist+="END\n";

        }
        ui->textBrowser->setText(linklist);
    }
    else if(graph_style==4&&flag_input)
    {
        QString linklist="";
        vexnum=length_link;
        link_matrix_store=new int*[vexnum];
        for(int i=0;i<vexnum;i++)
            link_matrix_store[i]=new int[vexnum];
        for(int i=0;i<length_link;i++)
        {
            linklist+=QString::number(i,10)+":";
            for(int j=0;j<length_link;j++)
            {
                link_matrix_store[i][j]=link_matrix[i][j];
                if(link_matrix[i][j]>0)
                {
                    linklist+=QString::number(j,10)+"(power:"+QString::number(link_matrix[i][j],10)+")"+"->";

                }

            }
            linklist+="END\n";

        }
        ui->textBrowser->setText(linklist);
    }
    else
    {
        ui->textBrowser->setText("Input error and do not conform to the features of the selected graph,please input again!");
    }
}


void MainWindow::on_radioButton_3_clicked()//图类型选择radio button
{
    ui->radioButton_3->setChecked(true);
}

void MainWindow::on_radioButton_2_clicked()//图类型选择radio button
{
     ui->radioButton_2->setChecked(true);
}

void MainWindow::on_radioButton_clicked()//图类型选择radio button
{
     ui->radioButton->setChecked(true);
}

void MainWindow::on_radioButton_4_clicked()//图类型选择radio button
{
     ui->radioButton_4->setChecked(true);
}

//----------------------------第一部分判断输入部分函数------------------










//----------------------------第二部分BFS，DFS等各类操作函数----------------------------
//无向图BFS各类操作函数定义开始
int QueueEmpty(LinkQueue Q){    //无向图广度优先遍历判断队空操作
    if(Q.front==Q.rear)
        return 1;
    else
        return 0;
}
int InitQueue(LinkQueue &Q){    //无向图广度优先遍历初始化队列
    Q.front=Q.rear=(QueuePtr)malloc(sizeof(QNode));
    if(!Q.front)
        exit(0);
    Q.front->next=NULL;
    return 1;
}
int EnQueue(LinkQueue &Q,int e){    //无向图广度优先遍历入队操作
    QueuePtr p;
    p=(QueuePtr)malloc(sizeof(QNode));
    if(!p) exit(0);
    p->data=e;
    p->next=NULL;
    Q.rear->next=p;
    Q.rear=p;
    return 1;
}
int DeQueue(LinkQueue &Q,int &e){    //无向图广度优先遍历出队操作
    QueuePtr p;
    if(Q.front==Q.rear)
        return 0;
    p=Q.front->next;
    e=p->data;
    Q.front->next=p->next;
    if(Q.rear==p)
        Q.rear=Q.front;
    free(p);
    return 1;
}

void MainWindow::BfsTraverse(QString graph_name,QString &BFS_nodirection_line_line,int **link_matrix_store,int vexnum){
    //无向图广度优先遍历
    int visited3[max];
    int v,u,w;
    LinkQueue Q;
    BFS_nodirection_line_line="The obtained sequence is:";
    for(v=0;v<vexnum;v++)
        visited3[v]=0;
    InitQueue(Q);

    QString queue_all="";
    QString Null="";
    for(v=0;v<vexnum;v++)
        if(!visited3[v]){
            visited3[v]=1;
            visitedline[num_visited]=v;
            num_visited++;
            BFS_nodirection_line_line+=graph_name[v]+"->";
            EnQueue(Q,v);
            ui->label_7->setText(QString(graph_name[v]));
            queue_all+=graph_name[v]+" ";
            sleep(400);
            ui->label_9->setText(queue_all);
            sleep(400);
            while(!QueueEmpty(Q)){
                DeQueue(Q,u);
                ui->label_6->setText(QString(graph_name[u]));
                for(int z=0;z<queue_all.length();z++)
                {
                    if(queue_all[z]==graph_name[u])
                    {
                        queue_all[z]=Null[0];
                        queue_all[z+1]=Null[0];
                    }
                }
                sleep(400);
                ui->label_9->setText(queue_all);
                sleep(400);
                for(w=0;w<vexnum;w++)
                    if(!visited3[w]&&link_matrix_store[u][w]!=0){
                        visited3[w]=1;
                        visitedline[num_visited]=w;
                        num_visited++;
                        //BFS_nodirection_line_line+=QString::number(w,10)+"->";
                        BFS_nodirection_line_line+=graph_name[w]+"->";
                        EnQueue(Q,w);
                        ui->label_7->setText(QString(graph_name[w]));
                        sleep(400);
                        queue_all+=graph_name[w]+" ";
                        sleep(400);
                        ui->label_9->setText(queue_all);
                        sleep(400);
                    }
            }
        }
    BFS_nodirection_line_line+="END\n";
}
//无向图BFS各类操作函数定义结束






//----------------------栈相关函数开始----------
int FirstAdj(int **G,int vexnum,int i){
    int j;

    for(j = 0; j < vexnum; j++){
        if(G[i][j])
            return j;
    }

    return -1;
}

int NextAdj(int **G,int vexnum,int i, int j){
    for(j = j + 1; j < vexnum; j ++){
        if(G[i][j])
            return j;
    }

    return -1;
}
void InitStack(SqStack &S){
    S.base = (int *)malloc(sizeof(int) * max);

    if(!S.base)
        return ;

    S.top = 0;
    S.stacksize = max;
}

void Push(SqStack &S, char ch){
    if(S.top>= S.stacksize){
        S.base=(int *)realloc(S.base,(S.stacksize+max)*sizeof(int));

        if(!S.base)
            return ;

        S.stacksize+=max;
    }

    S.base[S.top++]=ch;
}

int StackEmpty(SqStack S){
    if(!S.top)
        return 1;

    return 0;
}

void Pop(SqStack &S, int &i){
    if(!S.top)
        return ;

    i = S.base[--S.top];
}

void GetTop(SqStack S, int &i){
    i = S.base[S.top - 1];
}
//----------------------栈相关函数结束----------




//---------------------深度优先搜索递归形式---------
void DFS(QString &DFS_recusion,QString vex,int **graph_vex,int i,int vexnum){
    int j;

    visited1[i] = 1;
    //visitedline[]
    visitedline[num_visited]=i;
    num_visited++;
    DFS_recusion+=vex[i]+"->";
    for(j=FirstAdj(graph_vex,vexnum,i); j>=0; j=NextAdj(graph_vex,vexnum,i,j)){
        if(!visited1[j])
            DFS(DFS_recusion,vex,graph_vex,j,vexnum);
    }

}

void DFSTraverse1(QString &DFS_recusion,QString vex,int **graph_vex,int vexnum){
    int i;
    DFS_recusion="The obtained sequence is:";
    for(i = 0; i<vexnum; i++)
        visited1[i] = 0;

    for(i = 0;i<vexnum; i++){
        if(!visited1[i])
            DFS(DFS_recusion,vex,graph_vex,i,vexnum);
    }
    DFS_recusion+="END\n";
}
//---------------------深度优先搜索递归形式---------




//---------------------深度优先搜索非递归形式---------
void MainWindow::DFS2(QString &DFS_norecusion,QString vex,int **graph_vex, int i,int vexnum){
    QString stack_all="";
    QString Null="";

    int j,k;
    SqStack S;
    InitStack(S);
    Push(S,i);
    sleep(400);
    ui->label_7->setText(QString(graph_name[i]));
    sleep(400);
    stack_all+=graph_name[i]+" ";
    ui->label_9->setText(stack_all);
    sleep(400);

    DFS_norecusion+=vex[i]+"->";
    visited[i] = 1;
    visitedline[num_visited]=i;
    num_visited++;
    while(!StackEmpty(S)){

        GetTop(S,i);

        for(j = 0; j < vexnum; j ++){
            if(graph_vex[i][j] && !visited[j]){
                Push(S,j);
                sleep(400);
                ui->label_7->setText(QString(graph_name[j]));
                sleep(400);
                stack_all+=graph_name[j]+" ";
                ui->label_9->setText(stack_all);
                sleep(400);

                DFS_norecusion+=vex[j]+"->";
                visited[j] = 1;
                visitedline[num_visited]=j;
                num_visited++;
                i = j;
                j = 0;
            }
        }

        if(!StackEmpty(S)){
            Pop(S,k);
            ui->label_6->setText(QString(graph_name[k]));
            sleep(400);
            for(int i=0;i<stack_all.length();i++)
            {
                if(stack_all[i]==graph_name[k])
                {
                    stack_all[i]=Null[0];
                    stack_all[i+1]=Null[0];
                }
            }
            ui->label_9->setText(stack_all);
            sleep(400);
        }
    }
    DFS_norecusion+="END\n";
}

void MainWindow::DFSTraverse2(QString &DFS_norecusion,QString vex,int **graph_vex,int vexnum){
    int i;
    DFS_norecusion+="The obtained sequence is:";
    for(i = 0; i < vexnum; i++)
        visited[i] = 0;

    for(i = 0; i < vexnum; i++){
        if(!visited[i])
            DFS2(DFS_norecusion,vex,graph_vex,i,vexnum);
    }
}
//---------------------深度优先搜索非递归形式---------

//---------------------无向图函数部分结束-------------

//---------------------有向图函数部分开始-------------

void dfs(LJJZ m, int v)
{
    temp_visited_2[v] = 1;
    visitedline[num_visited]=v;
    num_visited++;
    int j;
    //cout << m.vex[v] << " ";
    temp_direction+=Graph_name[m.vex[v]]+"->";
    for (j = 0; j<m.n; j++)
    {
        if (m.edge[v][j] == 1 && temp_visited_2[j] == 0)
            dfs(m, j);
    }

}

void MainWindow::dfs_no(MGraph* G,int ves)
{
   QString stack_all="";
   QString Null="";
   QStack<int> s;//创建一个栈
   //cout<<ves;
   temp_direction_DFS_2018+=Graph_name[ves]+"->";
   G->book[ves] = 1;//已经访问过结点ves了
   s.push(ves);//入栈
   sleep(400);
   ui->label_7->setText(QString(Graph_name[ves]));
   sleep(400);
   stack_all+=Graph_name[ves]+" ";
   ui->label_9->setText(stack_all);
   sleep(400);


   visitedline[num_visited]=ves;
   num_visited++;
   while(!s.empty())
   {
       int data;
       int i;

       data =s.top();//取top的顶点
       for(i = 0; i < G->ves; i++)
       {
           if(G->e[data][i] != 0 && G->book[i] != 1)
       {
           //cout<<i ;//访问
           temp_direction_DFS_2018+=Graph_name[i]+"->";
           G->book[i] = 1;
           visitedline[num_visited]=i;
           num_visited++;
           s.push(i);
           ui->label_7->setText(QString(Graph_name[i]));
           sleep(400);
           stack_all+=Graph_name[i]+" ";
           ui->label_9->setText(stack_all);
           sleep(400);
           break;
       }
       }
       if(i == G->ves)//data相邻的结点都访问结束了，就弹出data
       {
           sleep(400);
           int mtop=s.top();
           ui->label_6->setText(QString(Graph_name[mtop]));
           sleep(400);
           for(int mlend=0;mlend<stack_all.length();mlend++)
           {
               if(stack_all[mlend]==Graph_name[mtop])
               {
                   stack_all[mlend]=Null[0];
                   stack_all[mlend+1]=Null[0];
               }
           }
           ui->label_9->setText(stack_all);
           sleep(400);
           s.pop();

       }
   }
}
//广度优先收索
void MainWindow::bfs(LJJZ m, int v)
{
    QQueue<int>q;
    QString queue_all="";
    QString Null="";

    visitedline[num_visited]=v;
    num_visited++;

    temp_visited_2[v] = 1;
    //cout << m.vex[v] << " ";
    temp_direction+=Graph_name[m.vex[v]]+"->";
    q.push_back(v);
    sleep(400);
    ui->label_7->setText(QString(Graph_name[v]));
    sleep(400);
    queue_all+=Graph_name[v]+" ";
    ui->label_9->setText(queue_all);

    while (!q.empty())
    {
        int x;
        sleep(400);
        x = q.front();
        //q.pop();
        q.pop_front();
        ui->label_6->setText(QString(Graph_name[x]));
        sleep(400);
        for(int i=0;i<queue_all.length();i++)
        {
            if(queue_all[i]==Graph_name[x])
            {
                queue_all[i]=Null[0];
                queue_all[i+1]=Null[0];
            }
        }

        sleep(400);
        queue_all+=Graph_name[v]+" ";
        ui->label_9->setText(queue_all);
        sleep(400);



        for (int j = 0; j<m.n; j++)
        {
            if (m.edge[x][j] == 1 && temp_visited_2[j] == 0)
            {
                temp_visited_2[j] = 1;
                visitedline[num_visited]=j;
                num_visited++;
                //cout << m.vex[j] << " ";
                temp_direction+=Graph_name[m.vex[j]]+"->";
                q.push_back(j);
                ui->label_7->setText(QString(Graph_name[j]));
                sleep(400);
                queue_all+=Graph_name[j]+" ";
                ui->label_9->setText(queue_all);
                sleep(400);
            }

        }

    }
    ui->label_9->setText("");
    temp_direction+="END\n";
}



//---------------------有向图函数部分结束-------------
void MainWindow::on_radioButton_5_clicked()//深度优先递归
{
    ui->radioButton_5->setChecked(true);
    ui->label_4->setText("Depth first traversal(recursion) final result:");
    ui->label_stackin->setText("Stack in:");
    ui->label_stackout->setText("Stack out:");
    ui->label_10->setText("Current stack member:");
    ui->label_6->setText("NULL");
    ui->label_7->setText("NULL");
    ui->label_9->setText("NULL");
}

void MainWindow::on_radioButton_6_clicked()//深度优先非递归
{
    ui->radioButton_6->setChecked(true);
    ui->label_4->setText("Depth first traversal(norecursion) final result:");
    ui->label_stackin->setText("Stack in:");
    ui->label_stackout->setText("Stack out:");
    ui->label_10->setText("Current stack member:");
}

void MainWindow::on_radioButton_7_clicked()//广度优先遍历
{
    ui->radioButton_7->setChecked(true);
    ui->label_4->setText("Breadth first traversal final result:");
    ui->label_stackin->setText("Queue in:");
    ui->label_stackout->setText("Queue out:");
    ui->label_10->setText("Current queue member:");
}




void MainWindow::on_pushButton_2_clicked()//确定，开始遍历
{
    if(ui->radioButton_5->isChecked())//深度优先递归
    {
        if(ui->radioButton_4->isChecked()||ui->radioButton_2->isChecked())//无向图
        {

            visitedline=new int[vexnum];
            num_visited=0;
            DFSTraverse1(DFS_recusion_line,graph_name,link_matrix_store,vexnum);
            ui->textBrowser_2->setText(DFS_recusion_line);
        }
        else if(ui->radioButton->isChecked()||ui->radioButton_3->isChecked())
        {

            visitedline=new int[vexnum];
            num_visited=0;

            LJJZ m;
            temp_direction="The obtained sequence is:";
            Graph_name=graph_name;
            for (int i = 0; i<vexnum; i++)
                for (int j = 0; j<vexnum; j++)
                {
                    m.edge[i][j]=link_matrix_store[i][j];
                    m.vex[i] = i;
                }
            m.n=vexnum;
            for (int i = 0; i<vexnum; i++)
                temp_visited_2[i] = 0;
            for (int i = 0; i<m.n; i++)
            {
                if (temp_visited_2[i] == 0)
                    dfs(m, i);
            }
            temp_direction+="END\n";
            ui->textBrowser_2->setText(temp_direction);
        }
    }
    else if(ui->radioButton_6->isChecked())//深度优先非递归
    {
        if(ui->radioButton_4->isChecked()||ui->radioButton_2->isChecked())//无向图
        {

            visitedline=new int[vexnum];
            num_visited=0;

            DFSTraverse2(DFS_norecusion_line,graph_name,link_matrix_store,vexnum);
            ui->textBrowser_2->setText(DFS_norecusion_line);

        }
        else if(ui->radioButton->isChecked()||ui->radioButton_3->isChecked())
        {
            visitedline=new int[vexnum];
            num_visited=0;

            temp_direction_DFS_2018="The obtained sequence is:";
            MGraph m;
            m.ves=vexnum;
            Graph_name=graph_name;
            for(int i=0;i<vexnum;i++)
                m.book[i]=0;
            for(int i=0;i<vexnum;i++)
                for(int j=0;j<vexnum;j++)
                    m.e[i][j]=link_matrix_store[i][j];
            dfs_no(&m,0);
            temp_direction_DFS_2018+="END\n";
            ui->textBrowser_2->setText(temp_direction_DFS_2018);
        }

    }
    else if(ui->radioButton_7->isChecked())//广度优先遍历
    {
        if(ui->radioButton_4->isChecked()||ui->radioButton_2->isChecked())//无向图
        {

          visitedline=new int[vexnum];
          num_visited=0;

          BfsTraverse(graph_name,BFS_nodirection_line,link_matrix_store,vexnum);
          ui->textBrowser_2->setText(BFS_nodirection_line);
        }
        else if(ui->radioButton->isChecked()||ui->radioButton_3->isChecked())
        {
           visitedline=new int[vexnum];
           num_visited=0;
           LJJZ m;
           temp_direction="";
           Graph_name=graph_name;
           for (int i = 0; i<vexnum; i++)
               for (int j = 0; j<vexnum; j++)
               {
                   m.edge[i][j]=link_matrix_store[i][j];
                   m.vex[i] = i;
               }
           m.n=vexnum;
           for (int i = 0; i<vexnum; i++)
               temp_visited_2[i] = 0;
           temp_direction="";
           for (int i = 0; i<m.n; i++)
           {
               if (temp_visited_2[i] == 0)
                   bfs(m, i);
           }
           ui->textBrowser_2->setText(temp_direction);
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    QString input_name;
    int count=0;
    input_name=ui->textEdit_2->toPlainText();
    for(int i=0;i<input_name.length();i++)
    {
        if(input_name[i]!=' '&&input_name[i]!='\n')
          count++;

    }
    if(count>vexnum)
        ui->pushButton->setText("input exceed");
    else if(count<vexnum)
        ui->pushButton->setText("input lack");
    else
    {
        ui->pushButton->setText("input right");
        int count_char=0;
        for(int i=0;i<input_name.length();i++)
        {
            if(input_name[i]!=' '&&input_name[i]!='\n')
            {
                graph_name[count_char]=input_name[i];
                count_char++;
            }
        }
    }
}

void MainWindow::display()
{

    int *posx=new int[vexnum];
    int *posy=new int[vexnum];
    int round=15*vexnum;

    for(int i=0;i<vexnum;i++)
    {
        posx[i]=150-round*cos(i*2*PI/vexnum);
        posy[i]=150-round*sin(i*2*PI/vexnum);
    }
    QGraphicsScene *scene = new QGraphicsScene;
    QGraphicsView *view = new QGraphicsView(scene);
    view->setDragMode(QGraphicsView::ScrollHandDrag);
    view->setRenderHint(QPainter::Antialiasing);
    if(1)
    {
        QFont font;
           //设置文字字体
           font.setFamily("simsun");
           //设置文字大小为50像素
           font.setPixelSize(50);
           //设置文字为粗体
           font.setBold(true);             //封装的setWeight函数
           //设置文字为斜体
           font.setItalic(true);           //封装的setStyle函数
           //设置文字大小
           font.setPointSize(20);
           //设置文字倾斜
           font.setStyle(QFont::StyleItalic);
    }
    for(int i=0;i<vexnum;i++)
    {
        QGraphicsTextItem *txtitem=new QGraphicsTextItem(QString(graph_name[i]));
        txtitem->setPos(QPointF(posx[i],posy[i]));
        txtitem->setFont(font());
        scene->addItem(txtitem);
    }
    for(int i=0;i<vexnum;i++)
    {
        for(int j=0;j<vexnum;j++)
        {

            if(link_matrix_store[i][j]>0)
            {
                scene->addLine(posx[i],posy[i],posx[j],posy[j]);
            }
        }
    }
    view->resize(1000, 1000);
    view->setWindowTitle("auto-display");
    view->show();
    QGraphicsTextItem *txtitem1=new QGraphicsTextItem("The original graph listed as followed:");
    txtitem1->setFont(font());
    txtitem1->setPos(QPointF(50,50));
    scene->addItem(txtitem1);
    for(int i=0;i<vexnum;i++)
    {
        QGraphicsTextItem *txtitem=new QGraphicsTextItem(QString(graph_name[i]));
        txtitem->setPos(QPointF(posx[i],posy[i]-400));
        scene->addItem(txtitem);
    }
    for(int i=0;i<vexnum-1;i++)
    {
        sleep(2000);

        scene->addLine(posx[visitedline[i]],posy[visitedline[i]]-400,posx[visitedline[i+1]],posy[visitedline[i+1]]-400);
        if(i==vexnum-2)
        {
            sleep(2000);
            scene->addLine(posx[visitedline[i+1]],posy[visitedline[i+1]]-400,posx[visitedline[0]],posy[visitedline[0]]-400);

        }
    }
}


void MainWindow::on_pushButton_3_clicked()
{

    display();
    if(ui->radioButton_5->isChecked())//深度优先递归
    {
        if(ui->radioButton_4->isChecked()||ui->radioButton_2->isChecked())//无向图
        {
            DFSTraverse1(DFS_recusion_line,graph_name,link_matrix_store,vexnum);
        }
        else if(ui->radioButton->isChecked()||ui->radioButton_3->isChecked())
        {

            LJJZ m;
            temp_direction="";
            Graph_name=graph_name;
            for (int i = 0; i<vexnum; i++)
                for (int j = 0; j<vexnum; j++)
                {
                    m.edge[i][j]=link_matrix_store[i][j];
                    m.vex[i] = i;
                }
            m.n=vexnum;
            for (int i = 0; i<vexnum; i++)
                temp_visited_2[i] = 0;
            for (int i = 0; i<m.n; i++)
            {
                if (temp_visited_2[i] == 0)
                    dfs(m, i);
            }

        }
    }
    else if(ui->radioButton_6->isChecked())//深度优先非递归
    {
        if(ui->radioButton_4->isChecked()||ui->radioButton_2->isChecked())//无向图
        {
            DFSTraverse2(DFS_norecusion_line,graph_name,link_matrix_store,vexnum);


        }
        else if(ui->radioButton->isChecked()||ui->radioButton_3->isChecked())
        {
            temp_direction_DFS_2018="The obtained sequence is:";
            MGraph m;
            m.ves=vexnum;
            Graph_name=graph_name;
            for(int i=0;i<vexnum;i++)
                m.book[i]=0;
            for(int i=0;i<vexnum;i++)
                for(int j=0;j<vexnum;j++)
                    m.e[i][j]=link_matrix_store[i][j];
            dfs_no(&m,0);
        }

    }
    else if(ui->radioButton_7->isChecked())//广度优先遍历
    {
        if(ui->radioButton_4->isChecked()||ui->radioButton_2->isChecked())//无向图
        {
          //temp_direction="The obtained sequence is:";
          BfsTraverse(graph_name,BFS_nodirection_line,link_matrix_store,vexnum);

        }
        else if(ui->radioButton->isChecked()||ui->radioButton_3->isChecked())
        {
           LJJZ m;
           temp_direction="The obtained sequence is:";
           Graph_name=graph_name;
           for (int i = 0; i<vexnum; i++)
               for (int j = 0; j<vexnum; j++)
               {
                   m.edge[i][j]=link_matrix_store[i][j];
                   m.vex[i] = i;
               }
           m.n=vexnum;
           for (int i = 0; i<vexnum; i++)
               temp_visited_2[i] = 0;
           temp_direction="";
           for (int i = 0; i<m.n; i++)
           {
               if (temp_visited_2[i] == 0)
                   bfs(m, i);
           }
        }
    }
}
