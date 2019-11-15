#ifndef MACHINEGAME_H
#define MACHINEGAME_H

#include "ChessBoard.h"
#include "ChessStep.h"
#include <QVector>

class MachineGame : public ChessBoard
{
public:
    MachineGame();
    ~MachineGame();


    void chooseOrMovePieces(int tempID, int& row, int& col); //辅助函： 选棋或移动棋子




    void saveStep(int moveID, int checkedID, int row, int col, QVector<ChessStep*>& steps);
    void getAllPossibleMoveStep(QVector<ChessStep*>& steps);  //获得所有可能的移动步骤


    virtual void mousePressEvent(QMouseEvent *);    //鼠标点击事件

    void fakeMove(ChessStep* step);  //假装移动棋子
    void unFakeMove(ChessStep* step);  //撤回先前假装移动棋子的步骤
    int calcScore();  //计算最好的局面分
    ChessStep* getBestMove();   //获得最好的移动步骤

    void machineChooseAndMovePieces(); //机器 黑方时间: 进行选棋+下棋

};

#endif // MACHINEGAME_H
