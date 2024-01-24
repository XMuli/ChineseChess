// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2019-2024 XMuli & Contributors
// SPDX-GitHub: https://github.com/XMuli/ChineseChess
// SPDX-Author: XMuli <xmulitech@gmail.com>

#ifndef CHESSPIECES_H
#define CHESSPIECES_H

#include <QString>

class ChessPieces
{
public:
    ChessPieces();
    ~ChessPieces();

    void init(int id);                   //初始化
    QString getnName(bool isRedSide);    //棋子对应的汉字
    QString getColText(int col);
    QString getRowText(int rowTo);
    QString getMoveText(int rowFrom, int rowTo);

    enum m_emTYPE{JIANG, SHI, XIANG, MA, CHE, PAO, BING};

    int  m_nRow;        // 行
    int  m_nCol;        // 列
    int  m_nID;         // ID号
    bool m_bDead;       // 死亡状态
    bool m_bRed;        // 是否是红方
    m_emTYPE m_emType;  // 具体哪一个棋子

    QString colTextRed[9]={"九", "八", "七", "六", "五", "四", "三", "二", "一"};
    QString colTextBlack[9]={"1", "2", "3", "4", "5", "6", "7", "8", "9"};
    QString colTextRedTurn[9]={"一", "二", "三", "四", "五", "六", "七", "八", "九"};
};

#endif // CHESSPIECES_H
