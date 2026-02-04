// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2019-2026 XMuli & Contributors
// SPDX-GitHub: https://github.com/XMuli/ChineseChess
// SPDX-Author: XMuli <xmulitech@gmail.com>

#include "ChessPieces.h"

//1、定义结构体tPOS
struct POS
{
    int t_nRow;
    int t_nCol;
    ChessPieces::m_emTYPE t_emType;
};

//定义基础的16棋子[预定作为上方使用，黑棋使用]
POS tPos[16]= {
              {0, 0, ChessPieces::CHE},
              {0, 1, ChessPieces::MA},
              {0, 2, ChessPieces::XIANG},
              {0, 3, ChessPieces::SHI},
              {0, 4, ChessPieces::JIANG},
              {0, 5, ChessPieces::SHI},
              {0, 6, ChessPieces::XIANG},
              {0, 7, ChessPieces::MA},
              {0, 8, ChessPieces::CHE},

              {2, 1, ChessPieces::PAO},
              {2, 7, ChessPieces::PAO},
              {3, 0, ChessPieces::BING},
              {3, 2, ChessPieces::BING},
              {3, 4, ChessPieces::BING},
              {3, 6, ChessPieces::BING},
              {3, 8, ChessPieces::BING}
              };

ChessPieces::ChessPieces()
{
}

ChessPieces::~ChessPieces()
{
}

//初始化  对每一个棋子进行检验判断而后赋相应的值
void ChessPieces::init(int id)
{
    if(id <16)
    {
        m_nRow = tPos[id].t_nRow;
        m_nCol = tPos[id].t_nCol;
        m_emType = tPos[id].t_emType;
        m_bRed = false;
    }
    else
    {
        m_nRow = 9-tPos[id-16].t_nRow;
        m_nCol = 8-tPos[id-16].t_nCol;
        m_emType = tPos[id-16].t_emType;
        m_bRed = true;
    }

    m_bDead = false;
}

QString ChessPieces::getnName(bool isRedSide)
{
    if(isRedSide){
        switch (m_emType) {
        case CHE:
            return "俥";
        case MA:
            return "傌";
        case PAO:
            return "炮";
        case BING:
            return "兵";
        case JIANG:
            return "帥";
        case SHI:
            return "仕";
        case XIANG:
            return "相";
        default:
            return "null";
        }
    }
    else{
        switch (m_emType) {
        case CHE:
            return "車";
        case MA:
            return "馬";
        case PAO:
            return "砲";
        case BING:
            return "卒";
        case JIANG:
            return "將";
        case SHI:
            return "士";
        case XIANG:
            return "象";
        default:
            return "null";
        }
    }
    return "ERROR";
}

/**
 * @brief 获取棋子所在列 返回文本棋谱
 * @return QString
 */
QString ChessPieces::getColText(int col)
{
    QString colText;
    if(m_bRed)
    {
        colText= colTextRed[col];
    }
    else
    {
        colText= colTextBlack[col];
    }
    return colText;
}

/**
 * @brief 获取棋子所在行 返回文本棋谱
 * @param rowTo
 * @return QString
 */
QString ChessPieces::getRowText(int rowTo)
{
    QString temp="";
    if(m_nRow== rowTo)
    {
        temp.append("平");
        return temp;
    }
    if(m_nRow> rowTo)
    {
        if(m_bRed){
            temp.append("进");
        }
        else
        {
            temp.append("退");
        }
    }
    else
    {
        if(m_bRed){
            temp.append("退");
        }
        else
        {
            temp.append("进");
        }
    }
    return temp;
}

/**
 * @brief 获取棋子移动的格数 返回文本棋谱
 * @param rowFrom
 * @param rowTo
 * @return QString
 */
QString ChessPieces::getMoveText(int rowFrom, int rowTo)
{
    QString temp="";
    if(m_bRed)
    {
        temp.append(colTextRedTurn[abs(rowFrom-rowTo) -1]);
    }
    else
    {
        temp.append(colTextBlack[abs(rowFrom-rowTo) -1]);
    }
    return temp;
}
