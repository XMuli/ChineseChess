// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2019-2026 XMuli & Contributors
// SPDX-GitHub: https://github.com/XMuli/ChineseChess
// SPDX-Author: XMuli <xmulitech@gmail.com>

#include "MachineGame.h"
#include <QRandomGenerator>

MachineGame::MachineGame()
{
}

MachineGame::~MachineGame()
{
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

void MachineGame::mouseReleaseEvent(QMouseEvent *ev)
{
    const bool wasRedTurn = m_bIsRed;
    ChessBoard::mouseReleaseEvent(ev);

    if (!m_bIsOver && wasRedTurn && !m_bIsRed) {
        machineChooseAndMovePieces();
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
    // qsrand(QTime(0,0,0).secsTo(QTime::currentTime())); //随机数种子, 0~MAX
    // int temp =qrand()% nStepsCount;
    int temp = QRandomGenerator::global()->bounded(nStepsCount);
    QVector<ChessStep*>::iterator it = stepsAndNoKill.begin();
    retStep = it[temp];

    if(retStep == NULL)
        whoWin();

    //4.取最好的结果作为参考
    return retStep;
}

void MachineGame::machineChooseAndMovePieces()
{
    ChessStep* step = getBestMove();
    if (step == nullptr) {
        return;
    }

    doMoveStone(step->m_nMoveID, step->m_nKillID, step->m_nRowTo, step->m_nnColTo);
    m_nSelectID = -1;
    update();
}
