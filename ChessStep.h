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

using namespace std;

class ChessStep
{

public:
    explicit ChessStep();
    ~ChessStep();

    int m_nMoveID;   //移动棋子ID
    int m_nKillID;   //将要被击杀的棋子ID
    int m_nRowFrom;  //原位置的行
    int m_nColFrom;  //原位置的列
    int m_nRowTo;    //目的位置的行
    int m_nnColTo;   //目的位置的列

    std::string toString(){
        return QString("%1d %2d %3d %4d %5d %6d")
                .arg(m_nMoveID,m_nRowFrom,m_nRowTo,m_nColFrom,m_nnColTo)
                .toStdString();
    }
};

#endif // CHESSSTEP_H
