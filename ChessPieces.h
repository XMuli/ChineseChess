﻿/*
 * Copyright (C)  2019~2020  偕臧  All rights reserved.
 *
 * Author:  xmuli(偕臧) xmulitech@gmail.com
 *
 * GitHub:  https://github.com/XMuli
 * Blogs:   https://ifmet.cn
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
#ifndef CHESSPIECES_H
#define CHESSPIECES_H

#include <QString>

class ChessPieces
{
public:
    ChessPieces();
    ~ChessPieces();

    void init(int id);  //初始化
    QString getnName(bool isRedSide);    //棋子对应的汉字
    QString getColText(int col);
    QString getRowText(int rowTo);
    QString getMoveText(int rowFrom, int rowTo);

    enum m_emTYPE{JIANG, SHI, XIANG, MA, CHE, PAO, BING};

    int  m_nRow;   //行
    int  m_nCol;   //列
    int  m_nID;    //ID号
    bool m_bDead;  //死亡状态
    bool m_bRed;   //是否是红方
    m_emTYPE m_emType;  //具体哪一个棋子

    QString colTextRed[9]={"九", "八", "七", "六", "五", "四", "三", "二", "一"};
    QString colTextBlack[9]={"1", "2", "3", "4", "5", "6", "7", "8", "9"};
    QString colTextRedTurn[9]={"一", "二", "三", "四", "五", "六", "七", "八", "九"};
};

#endif // CHESSPIECES_H
