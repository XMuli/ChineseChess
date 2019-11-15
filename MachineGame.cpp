#include "MachineGame.h"

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
                    {
                        saveStep(id, i, row, col, steps);
                    }
                }


            }
        }
    }


}



void MachineGame::mousePressEvent(QMouseEvent *ev)
{

    if(ev->button() != Qt::LeftButton) return;

    int row, col;
    if(!isChecked(ev->pos(), row, col))  return;

    m_nCheckedID = -1;

    int i =0;
    for( ; i < 32; i++)
    {
        if(m_ChessPieces[i].m_nRow == row && m_ChessPieces[i].m_nCol == col && m_ChessPieces[i].m_bDead == false)
            break;
    }

    if(0<=i && i<32)
        m_nCheckedID = i;


    clickPieces(m_nCheckedID, row, col);


    if(m_bIsRed) //红方玩家时间
    {
        chooseOrMovePieces(i, row, col);

        if(!m_bIsRed) //黑方紧接着进行游戏
        {
            machineChooseAndMovePieces();
            //ToDo: 机器 黑方时间
        }
    }



}

void MachineGame::clickPieces(int checkedID, int &row, int &col)
{
    if(m_bIsRed) //红方玩家时间
    {
        chooseOrMovePieces(checkedID, row, col);

        if(!m_bIsRed) //黑方紧接着进行游戏
        {
            machineChooseAndMovePieces();
            //ToDo: 机器 黑方时间
        }
    }
}



//假装移动棋子
void MachineGame::fakeMove(ChessStep *step)
{
     if(step->m_nKillID != -1)
     {
         m_ChessPieces[step->m_nKillID].m_bDead = true;
     }


     m_ChessPieces[step->m_nMoveID].m_nRow = step->m_nRowTo;
     m_ChessPieces[step->m_nMoveID].m_nCol = step->m_nnColTo;
     m_bIsRed = !m_bIsRed;


}


//撤回先前假装移动棋子的步骤
void MachineGame::unFakeMove(ChessStep *step)
{
    if(step->m_nKillID != -1)
    {
        m_ChessPieces[step->m_nKillID].m_bDead = false;
    }

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
ChessStep* MachineGame::getBestMove()
{
    // 1.看看有那些步骤可以走
    QVector<ChessStep*> steps;
    getAllPossibleMoveStep(steps);   // 黑棋吃红棋的所有可能的步骤

    int maxScore = -10000;
    ChessStep* retStep;
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



    //4.取最好的结果作为参考
    return retStep;
}

void MachineGame::machineChooseAndMovePieces()
{
    ChessStep* step = getBestMove();

    m_ChessPieces[step->m_nKillID].m_bDead = true;
    m_ChessPieces[step->m_nMoveID].m_nRow = m_ChessPieces[step->m_nKillID].m_nRow;
    m_ChessPieces[step->m_nMoveID].m_nCol = m_ChessPieces[step->m_nKillID].m_nCol;

    m_nSelectID = -1;
    m_bIsRed = !m_bIsRed;


}


