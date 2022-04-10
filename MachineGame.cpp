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
            if(m_ChessPieces[m_nCheckedID].m_bRed)
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
            m_ChessPieces[m_nSelectID].m_nRow = row;
            m_ChessPieces[m_nSelectID].m_nCol = col;
            if(m_nCheckedID != -1)
                m_ChessPieces[m_nCheckedID].m_bDead = true;

            m_nSelectID = -1;
            m_bIsRed = !m_bIsRed;
        }
    }

    whoWin();
    update();
}

void MachineGame::saveStep(int selectID, int checkedID, int row, int col, QVector<ChessStep *> &steps)
{
    ChessStep* step = new ChessStep;
    step->m_nRowFrom = m_ChessPieces[selectID].m_nRow;
    step->m_nColFrom = m_ChessPieces[selectID].m_nCol;
    step->m_nRowTo = row;
    step->m_nnColTo = col;
    step->m_nMoveID = selectID;
    step->m_nKillID = checkedID;

    steps.append(step);
}

void MachineGame::getAllPossibleMoveStep(QVector<ChessStep *> &steps)
{
    for(int id = 0; id<16; id++)   //存在的黑棋， 能否走到这些盘棋盘里面的格子
    {
        if(m_ChessPieces[id].m_bDead)
            continue;

        for(int row=0; row<10; row++)
        {
            for(int col=0; col<9; col++)
            {
                int i = 16;
                for( ; i <= 31; i++)
                {
                    if(m_ChessPieces[i].m_nRow == row && m_ChessPieces[i].m_nCol == col && m_ChessPieces[i].m_bDead == false)
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

void MachineGame::getAllPossibleMoveStepAndNoKill(QVector<ChessStep *> &steps)
{
    for(int id = 0; id<16; id++)   //存在的黑棋， 能否走到这些盘棋盘里面的格子
    {
        if(m_ChessPieces[id].m_bDead)
            continue;

        for(int row=0; row<10; row++)
        {
            for(int col=0; col<9; col++)
            {

                int i = 0;
                for(; i <= 31; i++)
                {
                    if(m_ChessPieces[i].m_nRow == row && m_ChessPieces[i].m_nCol == col && m_ChessPieces[i].m_bDead == false)
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
        if(m_ChessPieces[i].m_nRow == row && m_ChessPieces[i].m_nCol == col && m_ChessPieces[i].m_bDead == false)
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
            //ToDo: 机器 黑方时间
    }
}

//假装移动棋子
void MachineGame::fakeMove(ChessStep *step)
{
     if(step->m_nKillID != -1)
         m_ChessPieces[step->m_nKillID].m_bDead = true;

     m_ChessPieces[step->m_nMoveID].m_nRow = step->m_nRowTo;
     m_ChessPieces[step->m_nMoveID].m_nCol = step->m_nnColTo;
     m_bIsRed = !m_bIsRed;
}

//撤回先前假装移动棋子的步骤
void MachineGame::unFakeMove(ChessStep *step)
{
    if(step->m_nKillID != -1)
        m_ChessPieces[step->m_nKillID].m_bDead = false;

    m_ChessPieces[step->m_nMoveID].m_nRow = step->m_nRowFrom;
    m_ChessPieces[step->m_nMoveID].m_nCol = step->m_nColFrom;
    m_bIsRed = !m_bIsRed;
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
        if(m_ChessPieces[i].m_bDead)
            continue;
        blackGrossScore += chessScore[m_ChessPieces[i].m_emType];
    }

    for(int i=16; i<32; i++)
    {
        if(m_ChessPieces[i].m_bDead)
            continue;
        redGrossScore += chessScore[m_ChessPieces[i].m_emType];
    }

    return (blackGrossScore - redGrossScore);
}


//获得最好的移动步骤
//第一此玩了一把，发现我居然下不赢自己写的算法。哭了哭了哭了555555........
ChessStep* MachineGame::getBestMove()
{
    int maxScore = -10000;
    ChessStep* retStep = NULL;

    //------------------------
    //有可击杀的红棋子就走击杀红棋子最优的一步
    // 1.看看有那些步骤可以走
    QVector<ChessStep*> steps;
    getAllPossibleMoveStep(steps);   // 黑棋吃红棋的所有可能的步骤

    //------------------------
    //没有可击杀的红棋子就走最后的一步
    QVector<ChessStep*> stepsAndNoKill;
    getAllPossibleMoveStepAndNoKill(stepsAndNoKill);   // 黑棋移动所有可能的步骤(不吃红棋子)

    //2.试着走一下
    for(QVector<ChessStep*>::iterator it = steps.begin(); it!=steps.end(); it++)
    {
        ChessStep* step = *it;
        fakeMove(step);
        int score = calcScore();   //3.计算最好的局面分
        unFakeMove(step);

        if(score > maxScore)
        {
            maxScore = score;
            retStep = step;
        }
    }

    if(retStep != NULL)
        return retStep;

    //2.试着走一下
    //从这种不击杀红棋子，只是单纯移动黑棋steps里面，随机抽选一种进行下棋
    int nStepsCount = stepsAndNoKill.count();
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime())); //随机数种子, 0~MAX
    int temp =qrand()% nStepsCount;
    QVector<ChessStep*>::iterator it = stepsAndNoKill.begin();
    retStep = it[temp];

    if(retStep == NULL)
        whoWin();

    //4.取最好的结果作为参考
    return retStep;
}

void MachineGame::machineChooseAndMovePieces()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    ChessStep* step = getBestMove();
    move(step);
}

void MachineGame::move(ChessStep* step){
    if(step->m_nKillID == -1)  //黑棋没有可以击杀的红棋子，只好走能够走的过程中最后一步棋
    {
        m_ChessPieces[step->m_nMoveID].m_nRow = step->m_nRowTo;
        m_ChessPieces[step->m_nMoveID].m_nCol = step->m_nnColTo;

    }
    else //黑棋有可以击杀的红棋子，故击杀红棋子
    {
        m_ChessPieces[step->m_nKillID].m_bDead = true;
        m_ChessPieces[step->m_nMoveID].m_nRow = m_ChessPieces[step->m_nKillID].m_nRow;
        m_ChessPieces[step->m_nMoveID].m_nCol = m_ChessPieces[step->m_nKillID].m_nCol;
        m_nSelectID = -1;
    }

    m_bIsRed = !m_bIsRed;
}


