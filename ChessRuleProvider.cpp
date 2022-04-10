#include "ChessRuleProvider.h"
#include <stdexcept>
#include "myLog.h"
//using namespace myLog;


ChessRuleProvider::ChessRuleProvider(ChessPieces pieces[])
{
    for(int i = 0; i<32 ;i++){
        this->m_ChessPieces[i] = pieces[i];
    }
}

ChessRuleProvider::ChessRuleProvider(std::vector<ChessPieces> pieces)
{
    if(pieces.size()<32){
        throw std::invalid_argument( "not enough pieces");
    }
    for(int i = 0; i<32 ;i++){
        this->m_ChessPieces[i] = pieces.at(i);
    }
}

void ChessRuleProvider::getAllPossibleSteps(QVector<ChessStep>& steps){
    getAllPossibleMoveStepAndKill(steps);
    getAllPossibleMoveStepAndNoKill(steps);
}

void ChessRuleProvider::getAllPossibleMoveStepAndKill(QVector<ChessStep> &steps)
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

void ChessRuleProvider::getAllPossibleMoveStepAndNoKill(QVector<ChessStep> &steps)
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




//总的移动规则
bool ChessRuleProvider::canMove(int moveId, int killId, int row, int col)
{
    //选棋id和吃棋id同色，则选择其它棋子并返回
    if(sameColor(moveId,killId))
    {
        return false;
    }

    switch (m_ChessPieces[moveId].m_emType)
    {
    case ChessPieces::JIANG:
        return canMoveJIANG(moveId, killId, row, col);

    case ChessPieces::SHI:
        return canMoveSHI(moveId, killId, row, col);

    case ChessPieces::XIANG:
        return canMoveXIANG(moveId, killId, row, col);

    case ChessPieces::MA:
        return canMoveMA(moveId, killId, row, col);

    case ChessPieces::CHE:
        return canMoveCHE(moveId, killId, row, col);

    case ChessPieces::PAO:
        return canMovePAO(moveId, killId, row, col);

    case ChessPieces::BING:
        return canMoveBING(moveId, killId, row, col);

    default: break;
    }

    return true;
}

bool ChessRuleProvider::canMoveJIANG(int moveId, int killId, int row, int col)
{
    //对将的情况
    if (killId != -1 && m_ChessPieces[killId].m_emType == m_ChessPieces->JIANG)
        return canMoveCHE(moveId, killId, row, col );

    if(isRed(moveId)) //红 将
    {
        if(row < 7 || col < 3 || col > 5) return false;
    }
    else  //黑 将
    {
        if(row > 2 || col < 3 || col > 5) return false;
    }

    int d=relation(m_ChessPieces[moveId].m_nRow, m_ChessPieces[moveId].m_nCol, row, col);
    if(d == 1 || d == 10)
        return true;

    return false;
}

bool ChessRuleProvider::canMoveSHI(int moveId, int killId, int row, int col)
{
    Q_UNUSED(killId);
    if(isRed(moveId)) //红 士
    {
        if(row < 7 || col < 3 || col > 5) return false;
    }
    else  //黑 士
    {
        if(row > 2 || col < 3 || col > 5) return false;
    }

    int d=relation(m_ChessPieces[moveId].m_nRow, m_ChessPieces[moveId].m_nCol, row, col);
    if(d == 11)
        return true;

    return false;
}

bool ChessRuleProvider::canMoveXIANG(int moveId, int killId, int row, int col)
{
    Q_UNUSED(killId);
    int d=relation(m_ChessPieces[moveId].m_nRow, m_ChessPieces[moveId].m_nCol, row, col);
    if(d!= 22)
        return false;

    int row_eye= (m_ChessPieces[moveId].m_nRow+ row)/ 2;
    int col_eye= (m_ChessPieces[moveId].m_nCol+ col)/ 2;

    //堵象眼
    if(getStoneId(row_eye,col_eye)!= -1)
        return false;

    //象不可过河
    if(isRed(moveId))   //红
    {
        if(row< 4)
            return false;
    }
    else    //黑
    {
        if(row> 5)
            return false;
    }

    return true;
}

bool ChessRuleProvider::canMoveMA(int moveId, int killId, int row, int col)
{
    Q_UNUSED(killId);
    int d=relation(m_ChessPieces[moveId].m_nRow, m_ChessPieces[moveId].m_nCol, row, col);
    if(d!=12 && d!=21)
        return false;

    //蹩马脚
    if(d==12)
    {
        if(getStoneId(m_ChessPieces[moveId].m_nRow, (m_ChessPieces[moveId].m_nCol+ col) /2) != -1)
            return false;
    }
    else
    {
        if(getStoneId((m_ChessPieces[moveId].m_nRow+ row) /2 ,m_ChessPieces[moveId].m_nCol) != -1)
            return false;
    }

    return true;
}

bool ChessRuleProvider::canMoveCHE(int moveId, int killId, int row, int col)
{
    Q_UNUSED(killId);
    int ret = getStoneCountAtLine(m_ChessPieces[moveId].m_nRow, m_ChessPieces[moveId].m_nCol, row, col);
    if(ret == 0)
        return true;

    return false;
}

bool ChessRuleProvider::canMovePAO(int moveId, int killId, int row, int col)
{
    int ret = getStoneCountAtLine(row, col, m_ChessPieces[moveId].m_nRow, m_ChessPieces[moveId].m_nCol);
    if(killId != -1)
    {
        if(ret == 1)
            return true;
    }
    else
    {
        if(ret == 0)
            return true;
    }
    return false;
}

bool ChessRuleProvider::canMoveBING(int moveId, int killId, int row, int col)
{
    Q_UNUSED(killId);
    int d=relation(m_ChessPieces[moveId].m_nRow, m_ChessPieces[moveId].m_nCol, row, col);
    if(d!= 1 && d!= 10)
        return false;

    if(isRed(moveId))   //红
    {
        //兵卒不可后退
        if(row> m_ChessPieces[moveId].m_nRow)
            return false;

        //兵卒没过河不可横着走
        if(m_ChessPieces[moveId].m_nRow>= 5 && m_ChessPieces[moveId].m_nRow== row)
            return false;
    }
    else    //黑
    {
        if(row< m_ChessPieces[moveId].m_nRow)
            return false;
        if(m_ChessPieces[moveId].m_nRow<= 4 && m_ChessPieces[moveId].m_nRow== row)
            return false;
    }

    return true;
}

bool ChessRuleProvider::sameColor(int moveId,int killId)
{
    if(moveId== -1 || killId== -1)
        return false;

    return isRed(moveId)== isRed(killId);
}

bool ChessRuleProvider::isRed(int id)
{
    return m_ChessPieces[id].m_bRed;
}

int ChessRuleProvider:: relation(int row1,int col1,int row2,int col2)
{
    // 原坐标(row1,col1)与目标坐标(row2,col2)的关系
    // 使用原坐标与目标坐标的行相减的绝对值乘以10 加上原坐标与目标坐标的列相减的绝对值
    // 作为关系值
    // 关系值用于判断是否符合棋子移动规则
    return abs(row1-row2)*10+ abs(col1-col2);
}

int ChessRuleProvider::getStoneId(int row, int col)
{
    for(int i=0; i<32; ++i)
    {
        if(m_ChessPieces[i].m_nRow == row && m_ChessPieces[i].m_nCol == col && !isDead(i))
            return i;
    }

    return -1;
}

int ChessRuleProvider::getStoneCountAtLine(int row1, int col1, int row2, int col2)
{
    int ret = 0;
    if(row1 != row2 && col1 != col2)
        return -1;
    if(row1 == row2 && col1 == col2)
        return -1;

    if(row1 == row2)
    {
        int min  = col1 < col2 ? col1 : col2;
        int max = col1 < col2 ? col2 : col1;
        for(int col = min+1; col<max; ++col)
        {
            if(getStoneId(row1, col) != -1)
                ++ret;
        }
    }
    else
    {
        int min = row1 < row2 ? row1 : row2;
        int max = row1 < row2 ? row2 : row1;
        for(int row = min+1; row<max; ++row)
        {
            if(getStoneId(row, col1) != -1)
                ++ret;
        }
    }

    return ret;
}

bool ChessRuleProvider::isDead(int id)
{
    if(id == -1)
        return true;

    return m_ChessPieces[id].m_bDead;
}

void ChessRuleProvider::saveStep(int moveid, int killid, int row, int col, QVector<ChessStep>& steps)
{
    ChessStep step;
    step.m_nColFrom = m_ChessPieces[moveid].m_nCol;
    step.m_nnColTo = col;
    step.m_nRowFrom = m_ChessPieces[moveid].m_nRow;
    step.m_nRowTo = row;
    step.m_nMoveID = moveid;
    step.m_nKillID = killid;

    steps.append(step);
}

