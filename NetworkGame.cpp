/*
 * Copyright (C)  2019~2020  偕臧  All rights reserved.
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
#include "NetworkGame.h"
#include <QDebug>
#include <QNetworkProxyFactory>

NetworkGame::NetworkGame(bool isServer)
{
    m_tcpServer = NULL;
    m_tcpSocket = NULL;
    m_ip = "192.168.31.90"; // "127.0.0.1" "192.168.31.132";
    m_port = "9999";

    QNetworkProxyFactory::setUseSystemConfiguration(false);


    if(isServer) //作为服务器端
    {
        m_bIsTcpServer = true;
        m_tcpServer = new QTcpServer(this);
        setNetworkGroupText("设置服务器的port号:", m_port, "监听", "状态结果:监听中");

        // 监听指定地址和端口
        if (m_tcpServer->listen(QHostAddress::Any, m_port.toInt())) {
            qDebug() << "Server is listening on" << m_tcpServer->serverAddress().toString()
                     << "port" << m_tcpServer->serverPort();
        } else {
            qDebug() << "Server failed to start: " << m_tcpServer->errorString();
        }

        connect(m_tcpServer, SIGNAL(newConnection()),this, SLOT(slotNewConnection()));
    }
    else   //作为客户端
    {
        m_bIsTcpServer = false;
        setNetworkGroupText("将接服务器的 ip 和 port:", m_ip + ":" + m_port, "连接", "状态结果:待操作");
        m_tcpSocket = new QTcpSocket(this);
        m_tcpSocket->connectToHost(QHostAddress(m_ip), m_port.toInt());
        connect(m_tcpSocket, SIGNAL(readyRead()), this, SLOT(slotRecv()));

        // 等待连接成功或失败
        if (m_tcpSocket->waitForConnected()) {
            qDebug() << "Connected to the server!";
        } else {
            qDebug() << "Connection failed: " << m_tcpSocket->errorString();
        }

    }

    connect(this, &NetworkGame::sigLineEditTextChanged, this, &NetworkGame::onLineEditTextChanged);
    connect(this, &NetworkGame::sigBtnTcpConnectReleased, this, &NetworkGame::onBtnTcpConnectReleased);
}

void NetworkGame::clickPieces(int checkedID, int &row, int &col)
{
    //不能够替对方选棋和下棋
    if(m_bIsTcpServer) //作为服务器一方  不能替黑棋下棋
    {
        //选棋[非下棋]这一步过程，使得其无法选择中黑棋
        if(m_nSelectID == -1 && m_nCheckedID != -1 )
        {
            if(m_bIsTcpServer != m_ChessPieces[checkedID].m_bRed )
                return ;
        }
    }
    else  //作为客户端一方  不能替红棋下棋
    {
        //选棋[非下棋]这一步过程，使得其无法选择中红棋
        if(m_nSelectID == -1 && m_nCheckedID != -1)
        {
            if(m_bIsTcpServer != m_ChessPieces[checkedID].m_bRed )
                return ;
        }
    }

    whoWin();

    ChessBoard::clickPieces(checkedID, row, col);
    char arry[3];
    arry[0] = checkedID;
    arry[1] = row;
    arry[2] = col;
    m_tcpSocket->write(arry, 3);
}

void NetworkGame::slotNewConnection()
{
    if(m_tcpSocket)
        return;

    m_tcpSocket = m_tcpServer->nextPendingConnection();
    connect(m_tcpSocket, SIGNAL(readyRead()), this, SLOT(slotRecv()));
}

void NetworkGame::slotRecv()
{
    QByteArray arry = m_tcpSocket->readAll();

    int nCheckedID = arry[0];
    int nRow = arry[1];
    int nCol = arry[2];

    //qDebug()<<nCheckedID<<"   "<<nRow<<"   "<<nCol<<"   ";
    ChessBoard::clickPieces(nCheckedID, nRow, nCol);
}

void NetworkGame::onLineEditTextChanged(const QString &arg1)
{

}

void NetworkGame::onBtnTcpConnectReleased()
{

}
