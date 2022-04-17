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
#include <map>
//1、定义结构体tPOS
struct POS
{
    int t_nRow;
    int t_nCol;
    ChessPiece::CHESS_TYPE t_emType;
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

std::map<ChessPiece::CHESS_TYPE,int> valueMap = {
    {ChessPiece::CHE,700},
    {ChessPiece::MA,500},
    {ChessPiece::PAO,400},
    {ChessPiece::XIANG,300},
    {ChessPiece::SHI,300},
    {ChessPiece::JIANG,7000},
    {ChessPiece::BING,200},
};


ChessPiece::ChessPiece()
{
}

ChessPiece::~ChessPiece()
{
}

bool selectPiece(ChessPiece* pi){
    //helper function to choose pieces to start with
    return true;
}

//初始化  对每一个棋子进行检验判断而后赋相应的值
void ChessPiece::init(int id)
{
    if(id <16)
    {
        row = tPos[id].t_nRow;
        col = tPos[id].t_nCol;
        type = tPos[id].t_emType;
        this->id = id;
        isRed = false;
    }
    else
    {
        row = 9-tPos[id-16].t_nRow;
        col = 8-tPos[id-16].t_nCol;
        type = tPos[id-16].t_emType;
        this->id = id;
        isRed = true;
    }

    if(selectPiece(this)){
       isDead = false;
    }
}

QString ChessPiece::getnName(bool isRedSide)
{
    if(isRedSide){
        switch (type) {
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
        switch (type) {
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

int ChessPiece::value(){
    if(this->isDead){
        return 0;
    }
    return valueMap.at(this->type);
}
