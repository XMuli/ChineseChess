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
#include "ChessPieces.h"

//1、定义结构体tPOS
struct POS
{
    int t_nRow;
    int t_nCol;
    ChessPiece::m_emTYPE t_emType;
};

//定义基础的16棋子[预定作为上方使用，黑棋使用]
POS tPos[16]= {
              {0, 0, ChessPiece::CHE},
              {0, 1, ChessPiece::MA},
              {0, 2, ChessPiece::XIANG},
              {0, 3, ChessPiece::SHI},
              {0, 4, ChessPiece::JIANG},
              {0, 5, ChessPiece::SHI},
              {0, 6, ChessPiece::XIANG},
              {0, 7, ChessPiece::MA},
              {0, 8, ChessPiece::CHE},

              {2, 1, ChessPiece::PAO},
              {2, 7, ChessPiece::PAO},
              {3, 0, ChessPiece::BING},
              {3, 2, ChessPiece::BING},
              {3, 4, ChessPiece::BING},
              {3, 6, ChessPiece::BING},
              {3, 8, ChessPiece::BING}
              };

ChessPiece::ChessPiece()
{
}

ChessPiece::~ChessPiece()
{
}

//初始化  对每一个棋子进行检验判断而后赋相应的值
void ChessPiece::init(int id)
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

QString ChessPiece::getnName(bool isRedSide)
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
