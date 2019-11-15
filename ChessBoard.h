#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QWidget>
#include "ChessPieces.h"

namespace Ui {
class ChessBoard;
}

class ChessBoard : public QWidget
{
    Q_OBJECT

public:
    explicit ChessBoard(QWidget *parent = 0);
    ~ChessBoard();



private:
    bool isDead(int id);
    int getStoneId(int row, int col);
    //车 炮 的功能辅助函数   判断两个点是否在一个直线上面,且返回直线之间的棋子个数
    int  getStoneCountAtLine(int row1, int col1, int row2, int col2);

public:


    //绘画棋盘
    virtual void paintEvent(QPaintEvent *);
    //象棋的棋盘的坐标转换成界面坐标
    QPoint center(int row, int col);
    QPoint center(int id);
    //绘画单个具体的棋子
    void drawStone(QPainter& painter, int id);


    //界面坐标转换成棋盘的行列值[获取鼠标点击的像素坐标，是位于棋盘的哪一个行列值]
    bool getRowCol(QPoint pt, int& row, int& col);
    //鼠标点击事件
    virtual void mousePressEvent(QMouseEvent *);



    //象棋移动的规则[将  士  象  马  车  炮  兵]
    bool canMove(int moveId, int killId, int row, int col);
    bool canMoveJIANG(int moveId, int killId, int row, int col);
    bool canMoveSHI(int moveId, int killId, int row, int col);
    bool canMoveXIANG(int moveId, int killId, int row, int col);
    bool canMoveMA(int moveId, int killId, int row, int col);
    bool canMoveCHE(int moveId, int killId, int row, int col);
    bool canMovePAO(int moveId, int killId, int row, int col);
    bool canMoveBING(int moveId, int killId, int row, int col);







public:
    ChessPieces _ChessPieces[32];
    int _r;  //棋子半径
    int _offset;  //距离界面的边距
    int _d;  //间距为50px
    int _selectId;  //IS? 选中棋子[-1:选棋子 || 非-1:走棋子]
    int _clickId; //点击鼠标选中棋子的ID
    bool _bRedTrue;  //红棋先下标志





private:
    Ui::ChessBoard *ui;
};

#endif // CHESSBOARD_H
