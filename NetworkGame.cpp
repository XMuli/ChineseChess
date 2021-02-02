/*
 * Copyright (C)  2019~2020  偕臧  All rights reserved.
 *
 * Author:  xmuli(偕臧) xmulitech@gmail.com
 *
 * github:  https://github.com/xmuli
 * blogs:   https://xmuli.tech
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
#include "NetworkGame.h"
#include "ui_ChessBoard.h"
#include <QDebug>
#include <QHostInfo>
#include <QNetworkAddressEntry>

NetworkGame::NetworkGame(bool isServer)
{
    m_tcpServer = NULL;
    m_tcpSocket = NULL;

    connect(ui->btnApply, &QPushButton::clicked, this, &NetworkGame::onClicked);

    if(isServer) //作为服务器端
    {
        m_bIsTcpServer = true;

        m_tcpServer = new QTcpServer(this);

        bool ok = false;
        int prot = ui->lineEditProt->text().toInt(&ok);
        m_tcpServer->listen(QHostAddress::Any, prot);

        connect(m_tcpServer, SIGNAL(newConnection()),this, SLOT(slotNewConnection()));
    }
    else   //作为客户端
    {
        m_bIsTcpServer = false;
        QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();
        if (list.isEmpty())
            return;

        if (list.isEmpty())
        {
            ui->lineEditIp->setText("127.0.0.1");
        }
        else
        {
            foreach (QNetworkInterface var, list) {
                if (!var.isValid())
                    continue;

                if (var.humanReadableName() == "eno1") {
                    QList<QNetworkAddressEntry> entry = var.addressEntries();
                    foreach (QNetworkAddressEntry ent, entry) {
                        if (ent.ip().protocol() == QAbstractSocket::IPv4Protocol)
                            ui->lineEditIp->setText(ent.ip().toString());
                    }
                }
            }
        }

        ui->lineEditProt->setText("9999");

        m_tcpSocket = new QTcpSocket(this);
        QString clientIp = ui->lineEditIp->text();
        bool ok = false;
        int prot = ui->lineEditProt->text().toInt(&ok);
        m_tcpSocket->connectToHost(QHostAddress(clientIp), prot);

        connect(m_tcpSocket, SIGNAL(readyRead()), this, SLOT(slotRecv()));
    }
}

NetworkGame::~NetworkGame()
{
}


//void NetworkGame::mousePressEvent(QMouseEvent *ev)
//{
//    QPoint pt = ev->pos();
//    //将pt转化成棋盘的像行列值
//    //判断这个行列值上面有没有棋子
//    int row, col;

//    //点击棋盘外面就不做处理
//    if(!isChecked(pt, row, col))
//        return;

//    //判断是哪一个棋子被选中，根据ID（这里的局部i）来记录下来
//    int i;
//    m_nCheckedID = -1;

//    for(i = 0; i <= 31; i++)
//    {
//        if(m_ChessPieces[i].m_nRow == row && m_ChessPieces[i].m_nCol == col && m_ChessPieces[i].m_bDead == false)
//            break;
//    }

//    if(0<=i && i<32)
//        m_nCheckedID = i;  //选中的棋子的ID

//    clickPieces(m_nCheckedID, row, col);

//    update();
//}


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
