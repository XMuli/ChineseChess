// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2019-2025 XMuli & Contributors
// SPDX-GitHub: https://github.com/XMuli/ChineseChess
// SPDX-Author: XMuli <xmulitech@gmail.com>

#ifndef CHESSSTEP_H
#define CHESSSTEP_H

#include <QObject>

class ChessStep : public QObject
{
    Q_OBJECT
public:
    explicit ChessStep(QObject *parent = 0);
    ~ChessStep();

    int m_nMoveID;   // 移动棋子ID
    int m_nKillID;   // 将要被击杀的棋子ID
    int m_nRowFrom;  // 原位置的行
    int m_nColFrom;  // 原位置的列
    int m_nRowTo;    // 目的位置的行
    int m_nnColTo;   // 目的位置的列
};

#endif // CHESSSTEP_H
