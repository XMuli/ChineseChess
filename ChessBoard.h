// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2019-2025 XMuli & Contributors
// SPDX-GitHub: https://github.com/XMuli/ChineseChess
// SPDX-Author: XMuli <xmulitech@gmail.com>

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

#include <QMainWindow>
#include <QFrame>
#include <QPainter>
#include <QPoint>
#include <QMouseEvent>
#include <QTimer>
#include <QTime>
#include <QMessageBox>
#include <QtGlobal>
#include "ChessPieces.h"
#include "AboutAuthor.h"
#include "ChessVoice.h"
#include "ChessStep.h"

namespace Ui {
class ChessBoard;
}

class ChessBoard : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChessBoard(QWidget *parent = 0);
    ~ChessBoard();

    bool isRed(int id);
    bool isDead(int id);
    void killStone(int id);                                  // 吃子
    void reliveStone(int id);                                // 死者苏生
    void moveStone(int moveid, int row, int col);            // 移动棋子
    bool sameColor(int moveId, int killId);                  // 棋子是否同色
    int getStoneId(int row, int col);
    // 车、炮的功能辅助函数   判断两个点是否在一个直线上面,且返回直线之间的棋子个数
    int  getStoneCountAtLine(int row1, int col1, int row2, int col2);
    void whoWin();                                           // 谁胜谁负
    bool isChecked(QPointF pt, int& row, int& col);           // 是否选中该枚棋子。pt为输入参数; row， col为输出参数
    int relation(int row1, int col1, int row2, int col2);    // 计算选中的棋子的位置和要移动的位置之间的位置关系
    QPointF getRealPoint(QPointF pt);                          // 使mouseMoveEvent取得的坐标同Painter的坐标一致
    bool isGeneral();                                        // 校验将移动后位置是否将死
    void showNetworkGui(const bool& show = false);

private:
    bool hongMenFeast();                                     // 鸿门宴：对将
    bool havePieces(int row, int col);                       // 判断某一格子，是否有棋子
    void reset();                                            // 胜负已分，重置
    void winMessageBox(QString title, QString msg);
    void startGameTimer();
    void pauseGameTimer();
    void autoStartTimerIfNeeded();

public:
    //视图相关
    QPointF center(int row, int col);                                    // 象棋的棋盘的坐标转换成界面坐标
    QPointF center(int id);
    virtual void paintEvent(QPaintEvent *);                             // 绘画棋盘
    void drawChessPieces(QPainter& painter, int id);                    // 绘画单个具体的棋子
    void drawLastStep(QPainter &painter, QVector<ChessStep*>& steps);   // 绘制上次移动棋子的起止位置
    void drawTextStep();                                                // 绘制文本棋谱
//    virtual void mousePressEvent(QMouseEvent *);                      // 鼠标点击事件
//    virtual void clickPieces(int checkedID, int& row, int& col);
    bool boardTransform(QPointF& origin, qreal& side) const;            // 计算棋盘绘制和点击的起点与边长

    // 象棋移动的规则[将  士  象  马  车  炮  兵]
    bool canMove(int moveId, int killId, int row, int col);
    bool canMoveJIANG(int moveId, int killId, int row, int col);
    bool canMoveSHI(int moveId, int killId, int row, int col);
    bool canMoveXIANG(int moveId, int killId, int row, int col);
    bool canMoveMA(int moveId, int killId, int row, int col);
    bool canMoveCHE(int moveId, int killId, int row, int col);
    bool canMovePAO(int moveId, int killId, int row, int col);
    bool canMoveBING(int moveId, int killId, int row, int col);
    bool canSelect(int id);
    void init();

    //移动相关
    virtual void mouseReleaseEvent(QMouseEvent *ev);                                        // 鼠标释放事件
    void click(QPointF pt);                                                                  // 点击转换像素
    virtual void clickPieces(int id, int& row, int& col);                                   // 点击选棋
    void trySelectStone(int id);                                                            // 尝试选棋
    void tryMoveStone(int killid, int row, int col);                                        // 尝试移动
    void doMoveStone(int moveid, int killid, int row, int col);                             // 执行移动棋子
    void saveStep(int moveid, int killid, int row, int col, QVector<ChessStep*>& steps);    // 保存步数
    QString textStep(int moveid, int row, int col);                                         // 文本棋谱

    void backOne();                        // 悔棋一子
    void back(ChessStep* step);            // 悔棋到指定步数
    virtual void back();                   // 悔棋

    ChessPieces m_ChessPieces[32];         // 所有棋子
    QVector<ChessStep*> m_ChessSteps;      // 悔棋步数
    ChessVoice m_Chessvoice;               // 下棋音效
    qreal m_nR;                              // 棋子半径
    qreal m_nOffSet;                         // 距离界面的边距
    qreal m_nD;                              // 间距为50px
    int m_nSelectID;                       // 选中棋子[-1:选棋子 || 非-1:走棋子]
    int m_nCheckedID;                      // 将要被击杀的棋子ID
    bool m_bIsRed;                         // 是否是红方回合
    bool m_bIsTcpServer;
    bool m_bIsOver;                        // 是否已经游戏结束
    bool m_bIsShowStep;                    // 是否显示步数
    QString textStepRecord;                // 文本棋谱字符串

signals:
    void toMenu();

private slots:
    void updateTime();
    void on_pushButton_start_clicked();
    void on_pushButton_reset_clicked();
    void on_pushButton_about_clicked();
    void on_pushButton_restart_clicked();
    void on_pushButton_back_clicked();
    void on_pushButton_showStep_clicked();
    void on_pushButton_toMenu_clicked();

protected:
    Ui::ChessBoard *ui;

private:
    QTimer*      m_timer;                  // 定时器 每秒更新时间
    QTime*       m_timeRecord;             // 记录时间
    bool         m_bIsStart;               // 记录是否已经开始计时
    AboutAuthor* m_pAbout;
    bool         m_bTimerAutoStarted;
};

#endif // CHESSBOARD_H
