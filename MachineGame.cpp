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
#include "MachineGame.h"
#include <QApplication>
#include <chrono>
#include <thread>
#include "Node.h"
#include "MonteCarloTree.h"
#include "ChessState.h"

namespace MachineGameHelper{
    bool isSamePieceAndDifferentPos(ChessPiece a,ChessPiece b){
        if ((a.type == b.type) && (a.isRed == b.isRed)){
            if(a.row != b.row || a.col!=b.col){
                return true;
            }
        }
        return false;
    }
}

MachineGame::MachineGame()
{
}

MachineGame::~MachineGame()
{
}

//辅助函: 选棋或移动棋子
void MachineGame::chooseOrMovePieces(int tempID, int& row, int& col)
{
    if(m_nSelectID == -1) //选择棋子
    {
        if(m_nCheckedID != -1)
        {
            if(m_ChessPieces[m_nCheckedID].isRed)
            {
                m_nSelectID = tempID;
            }
            else
            {
                m_nSelectID = -1;
                return;
            }
        }
    }
    else
    {
        if(canMove(m_nSelectID, m_nCheckedID, row, col ))
        {
            //_selectId为第一次点击选中的棋子，
            //_clickId为第二次点击||被杀的棋子ID，准备选中棋子下子的地方
            m_ChessPieces[m_nSelectID].row = row;
            m_ChessPieces[m_nSelectID].col = col;
            if(m_nCheckedID != -1)
                m_ChessPieces[m_nCheckedID].isDead = true;

            m_nSelectID = -1;
            m_bIsRed = !m_bIsRed;
        }
    }

    whoWin();
    update();
}

void MachineGame::saveStep(int selectID, int checkedID, int row, int col, QVector<ChessStep> &steps)
{
    ChessStep step;
    step.fromRow = m_ChessPieces[selectID].row;
    step.fromCol = m_ChessPieces[selectID].col;
    step.toRow = row;
    step.toCol = col;
    step.moveId = selectID;
    step.killId = checkedID;

    steps.append(step);
}

void MachineGame::getAllPossibleMoveStep(QVector<ChessStep> &steps)
{
    for(int id = 0; id<16; id++)   //存在的黑棋， 能否走到这些盘棋盘里面的格子
    {
        if(m_ChessPieces[id].isDead)
            continue;

        for(int row=0; row<10; row++)
        {
            for(int col=0; col<9; col++)
            {
                int i = 16;
                for( ; i <= 31; i++)
                {
                    if(m_ChessPieces[i].row == row && m_ChessPieces[i].col == col && m_ChessPieces[i].isDead == false)
                        break;
                }

                if(i!=32)
                {
                    if(canMove(id, i, row, col))
                        saveStep(id, i, row, col, steps);
                }
            }
        }
    }
}

void MachineGame::getAllPossibleMoveStepAndNoKill(QVector<ChessStep> &steps)
{
    for(int id = 0; id<16; id++)   //存在的黑棋， 能否走到这些盘棋盘里面的格子
    {
        if(m_ChessPieces[id].isDead)
            continue;

        for(int row=0; row<10; row++)
        {
            for(int col=0; col<9; col++)
            {

                int i = 0;
                for(; i <= 31; i++)
                {
                    if(m_ChessPieces[i].row == row && m_ChessPieces[i].col == col && m_ChessPieces[i].isDead == false)
                        break;
                }

                if(id < 16 && i == 32)
                {
                    if(canMove(id, -1, row, col))
                        saveStep(id, -1, row, col, steps);
                }
            }
        }
    }
}

void MachineGame::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button() != Qt::LeftButton)
        return;

    int row, col;
    if(!isSelected(ev->pos(), row, col))
        return;

    m_nCheckedID = -1;

    //TODO Fix (升级 Qt6): https://github.com/xmuli/chinessChess/issues/23
    int i =0;
    for( ; i < 32; i++)
    {
        if(m_ChessPieces[i].row == row && m_ChessPieces[i].col == col && m_ChessPieces[i].isDead == false)
            break;
    }

    if(0<=i && i<32)
        m_nCheckedID = i;

    clickPieces(m_nCheckedID, row, col);
}

void MachineGame::clickPieces(int checkedID, int &row, int &col)
{
    if(m_bIsRed) //红方玩家时间
    {
        chooseOrMovePieces(checkedID, row, col);
        qApp->processEvents();

        if(!m_bIsRed) //黑方紧接着进行游戏
            machineChooseAndMovePieces();
    }
}

ChessStep MachineGame::getStepFromState(ChessState state){
    ChessStep res;
    for(auto &pieceInState:state.getChessPieces()){
        for (int i = 0; i < 32; ++i) {
            auto pieceInGame = this->m_ChessPieces[i];
            bool flag = MachineGameHelper::isSamePieceAndDifferentPos(pieceInState,pieceInGame);
            if(flag){
                res.fromCol = pieceInGame.col;
                res.fromRow = pieceInGame.row;

                res.toCol = pieceInGame.col;
                res.toRow = pieceInGame.row;

                res.moveId = pieceInGame.id;

                //TODO: killID should be assigned if kill happend
//                res.m_nKillID =
            }


        }
    }
    return res;
}



//计算最好的局面分
int MachineGame::calcScore()
{
    //enum m_emTYPE{JIANG, SHI, XIANG, MA, CHE, PAO, BING};
    //黑棋分数 - 红旗分数
    int redGrossScore = 0;
    int blackGrossScore = 0;

    static int chessScore[]={200, 20, 40, 60, 100, 80, 10};

    for(int i=0; i<16; i++)
    {
        if(m_ChessPieces[i].isDead)
            continue;
        blackGrossScore += chessScore[m_ChessPieces[i].type];
    }

    for(int i=16; i<32; i++)
    {
        if(m_ChessPieces[i].isDead)
            continue;
        redGrossScore += chessScore[m_ChessPieces[i].type];
    }

    return (blackGrossScore - redGrossScore);
}


//获得最好的移动步骤
ChessStep MachineGame::getBestMove()
{
    std::vector<ChessPiece> vec;
    for(auto i = 0;i<32;++i){
        vec.push_back(m_ChessPieces[i]);
    }

    MonteCarloTree<ChessState> mct(vec);

    auto bestState = mct.search();

    return this->getStepFromState(bestState);
}

void MachineGame::machineChooseAndMovePieces()
{
    ChessStep step = getBestMove();
    move(step);
}

void MachineGame::move(ChessStep step){
    if(step.killId == -1)  //黑棋没有可以击杀的红棋子，只好走能够走的过程中最后一步棋
    {
        m_ChessPieces[step.moveId].row = step.toRow;
        m_ChessPieces[step.moveId].col = step.toCol;

    }
    else //黑棋有可以击杀的红棋子，故击杀红棋子
    {
        m_ChessPieces[step.killId].isDead = true;
        m_ChessPieces[step.moveId].row = m_ChessPieces[step.killId].row;
        m_ChessPieces[step.moveId].col = m_ChessPieces[step.killId].col;
        m_nSelectID = -1;
    }

    m_bIsRed = !m_bIsRed;
}


