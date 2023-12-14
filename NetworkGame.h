/*
 * Copyright (C)  2019~2024  偕臧  All rights reserved.
 *
 * Author:  xmuli(偕臧) xmulitech@gmail.com
 *
 * GitHub:  https://github.com/XMuli/ChineseChess
 * Blogs:   https://xmuli.tech
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
    ~NetworkGame() = default;
    void initUI();
    void clickPieces(int checkedID, int& row, int& col) override;

public slots:
    void slotNewConnection();
    void slotRecv();
    void onBtnTryConnect();

private:
    QTcpServer* m_tcpServer;
    QTcpSocket* m_tcpSocket;
};

#endif // NETWORKGAME_H
