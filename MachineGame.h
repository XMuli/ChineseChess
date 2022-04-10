/*
 * Copyright (C)  2019~2020  偕臧  All rights reserved.
 *
 * Author:  xmuli(偕臧) xmulitech@gmail.com
 *
 * github:  https://github.com/xmuli
 * blogs:   https://ifmet.cn
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/gpl-3.0.html>.
 */
#ifndef MACHINEGAME_H
#define MACHINEGAME_H

#include "ChessBoard.h"
#include "ChessStep.h"
#include <QVector>
#include "ChessState.h"

class MachineGame : public ChessBoard
{
public:
    MachineGame();
    ~MachineGame();

    void chooseOrMovePieces(int tempID, int& row, int& col); //辅助函： 选棋或移动棋子

    void saveStep(int moveID, int checkedID, int row, int col, QVector<ChessStep*>& steps);  //保存棋子步骤
    void getAllPossibleMoveStep(QVector<ChessStep*>& steps);  //获得所有可能的移动步骤(击杀)
    void getAllPossibleMoveStepAndNoKill(QVector<ChessStep*>& steps);  //获得所有可能的移动步骤(不击杀)

    virtual void mousePressEvent(QMouseEvent *);    //鼠标点击事件
    void clickPieces(int checkedID, int& row, int& col);

    int calcScore();
    ChessStep* getBestMove();   //获得最好的移动步骤


    void machineChooseAndMovePieces(); //机器 黑方时间: 进行选棋+下棋

private:
    void move(ChessStep* step);
    ChessStep* getStepFromState(ChessState state);
};

#endif // MACHINEGAME_H
