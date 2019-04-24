#ifndef CHESSBOARD_H
#define CHESSBOARD_H

/***
 *      ┌─┐       ┌─┐ + +
 *   ┌──┘ ┴───────┘ ┴──┐++
 *   │                 │
 *   │       ───       │++ + + +
 *   ███████───███████ │+
 *   │                 │+
 *   │       ─┴─       │
 *   │                 │
 *   └───┐         ┌───┘
 *       │         │
 *       │         │   + +
 *       │         │
 *       │         └──────────────┐
 *       │                        │
 *       │                        ├─┐
 *       │                        ┌─┘
 *       │                        │
 *       └─┐  ┐  ┌───────┬──┐  ┌──┘  + + + +
 *         │ ─┤ ─┤       │ ─┤ ─┤
 *         └──┴──┘       └──┴──┘  + + + +
 *                神兽保佑
 *               代码无BUG!
 */


#include <QWidget>
#include "ChessPieces.h"
#include <QPainter>
#include <QPoint>
#include <QMouseEvent>
#include <QTimer>
#include <QTime>
#include <QMessageBox>
#include "AboutAuthor.h"

namespace Ui {
class ChessBoard;
}

class ChessBoard : public QWidget
{
    Q_OBJECT

public:
    explicit ChessBoard(QWidget *parent = 0);
    ~ChessBoard();


    bool isDead(int id);
    int getStoneId(int row, int col);
    int  getStoneCountAtLine(int row1, int col1, int row2, int col2);  //车 炮 的功能辅助函数   判断两个点是否在一个直线上面,且返回直线之间的棋子个数
    void whoWin();  //谁胜谁负
    bool isChecked(QPoint pt, int& row, int& col);   //是否选中该枚棋子。pt为输入参数; row， col为输出参数


public:
    QPoint center(int row, int col);         //象棋的棋盘的坐标转换成界面坐标
    QPoint center(int id);
    virtual void paintEvent(QPaintEvent *);      //绘画棋盘
    void drawChessPieces(QPainter& painter, int id);  //绘画单个具体的棋子

    virtual void mousePressEvent(QMouseEvent *);    //鼠标点击事件
    virtual void clickPieces(int checkedID, int& row, int& col);

    //象棋移动的规则[将  士  象  马  车  炮  兵]
    bool canMove(int moveId, int killId, int row, int col);
    bool canMoveJIANG(int moveId, int killId, int row, int col);
    bool canMoveSHI(int moveId, int killId, int row, int col);
    bool canMoveXIANG(int moveId, int killId, int row, int col);
    bool canMoveMA(int moveId, int killId, int row, int col);
    bool canMoveCHE(int moveId, int killId, int row, int col);
    bool canMovePAO(int moveId, int killId, int row, int col);
    bool canMoveBING(int moveId, int killId, int row, int col);


    ChessPieces m_ChessPieces[32];  //所有棋子
    int m_nR;          //棋子半径
    int m_nOffSet;     //距离界面的边距
    int m_nD;          //间距为50px
    int m_nSelectID;   //选中棋子[-1:选棋子 || 非-1:走棋子]
    int m_nCheckedID;    //将要被击杀的棋子ID
    bool m_bIsRed;     //是否是红棋
    bool m_bIsTcpServer;



private slots:
    void updateTime();   //刷新时间槽函数
    void on_pushButton_start_clicked();   //开始、暂停计时槽函数
    void on_pushButton_reset_clicked();   //计时清零重置槽函数
    void on_pushButton_about_clicked();   //关于作者槽函数

private:
    Ui::ChessBoard *ui;

    QTimer * m_timer;      //定时器 每秒更新时间
    QTime * m_timeRecord;  //记录时间
    bool m_bIsStart;        //记录是否已经开始计时

    AboutAuthor* m_pAbout;


};

#endif // CHESSBOARD_H
