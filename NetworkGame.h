/*
 * Copyright (C)  2019 ~ 2019 touwoyimuli.  All rights reserved.
 *
 * Author:  touwoyimuli <touwoyimuli@gmai.com>
 *
 * github:  https://github.com/touwoyimuli
 * blogs:   https://touwoyimuli.github.io/
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
 * along with this program.  If not, see <https://touwoyimuli.github.io/>.
 */
#ifndef NETWORKGAME_H
#define NETWORKGAME_H

#include "ChessBoard.h"
#include <QTcpServer>
#include <QTcpSocket>

//定义协议：
//第一个字节：表示点击的棋子ID；第二个字节：表示点击的行row，第三个字节：表示点击的列col

class NetworkGame : public ChessBoard
{
    Q_OBJECT

public:
    NetworkGame(bool isServer);
    ~NetworkGame();



    QTcpServer* m_tcpServer;
    QTcpSocket* m_tcpSocket;

    //virtual void mousePressEvent(QMouseEvent *);    //鼠标点击事件
    virtual void clickPieces(int checkedID, int& row, int& col);


public slots:
    void slotNewConnection();
    void slotRecv();
};

#endif // NETWORKGAME_H
