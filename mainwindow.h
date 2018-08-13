#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <Windows.h>
#include <QMainWindow>
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsView>
#include<QtMultimedia/QMediaPlayer>
#include <QMediaPlayer>
#define M 10000
#pragma execution_character_set("utf-8")
#define max 100//最大顶点数

/*无向图BFS队列节点*/
typedef struct QNode{
    int data;
    struct QNode *next;
}QNode,*QueuePtr;
typedef struct{
    QueuePtr front;
    QueuePtr rear;
}LinkQueue;
/*无向图BFS队列节点定义结束*/


#define MAX 100

typedef struct
{
    int n;
    int vex[MAX];
    int edge[MAX][MAX];

}LJJZ;
//---栈定义----

typedef struct{
    int *base;
    int top;
    int stacksize;
}SqStack;

//---栈定义----
typedef struct
{
    int e[MAX][MAX];
    int edge;//边
    int ves;//顶点
    int book[MAX];//判断标志是否是被访问
}MGraph;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    QString graph_name;
    QString BFS_nodirection_line;
    QString DFS_norecusion_line;
    QString DFS_recusion_line;

    QString BFS_nodirection_line_direction;
    QString DFS_norecusion_line_direction;
    QString DFS_recusion_line_direction;
    int **link_matrix_store;
    int vexnum;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void display();
    void autoScroll();


    void BfsTraverse(QString graph_name,QString &BFS_nodirection_line_line,int **link_matrix_store,int vexnum);
    void DFS2(QString &DFS_norecusion,QString vex,int **graph_vex, int i,int vexnum);
    void DFSTraverse2(QString &DFS_norecusion,QString vex,int **graph_vex,int vexnum);
    void bfs(LJJZ m, int v);
    void dfs_no(MGraph* G,int ves);
    void music();
    void initMenuBar();
    //friend int QueueEmpty(LinkQueue Q);
    //friend int InitQueue(LinkQueue &Q);
    //friend int EnQueue(LinkQueue &Q,int e);
    //friend int DeQueue(LinkQueue &Q,int &e);
    //friend void BfsTraverse(QString BFS_nodirection_line_line,int **link_matrix_store,int vexnum);

private slots:
    void on_countBtn_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_clicked();

    void on_radioButton_4_clicked();

    void on_radioButton_5_clicked();

    void on_radioButton_6_clicked();

    void on_radioButton_7_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();
    void timerUpdate();
    void on_pushButton_3_clicked();
    void on_actionAuthor_triggered();
    void on_actionQt_triggered();
private:
    Ui::MainWindow *ui;
private:
    QLabel* statusLabel1, *statusLabel2, *statusLabel3;
    QMediaPlayer *player;
    QMediaPlaylist *playlist;
    //void myConnect();
    void initStatusBar();
    void myConnect();
    //void timerUpdate();
protected:
    QGraphicsScene *scene;

};

#endif // MAINWINDOW_H
