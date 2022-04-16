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
#ifndef CHESSSTEP_H
#define CHESSSTEP_H

#include "QString"
#include "QStringBuilder"
#include "ChessPieces.h"
using namespace std;

class ChessStep
{

public:
    explicit ChessStep();
    ~ChessStep();
    ChessStep(ChessPiece const &piece){
        this->moveId = piece.id;
        this->fromCol = piece.col;
        this->fromRow = piece.row;
    }

    int moveId;   //移动棋子ID
    int killId;   //将要被击杀的棋子ID
    int fromRow;  //原位置的行
    int fromCol;  //原位置的列
    int toRow;    //目的位置的行
    int toCol;   //目的位置的列

    std::string toString(){
        return QString("%1d %2d %3d %4d %5d %6d")
                .arg(moveId,fromRow,toRow,fromCol,toCol)
                .toStdString();
    }
};

#endif // CHESSSTEP_H
