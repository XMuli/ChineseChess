// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2019-2025 XMuli & Contributors
// SPDX-GitHub: https://github.com/XMuli/ChineseChess
// SPDX-Author: XMuli <xmulitech@gmail.com>

#include "NetworkGame.h"
#include <mutex>
#include "ui_ChessBoard.h"
#include <QCoreApplication>
#include <QNetworkInterface>
#include <QDebug>
#include <QNetworkProxyFactory>

NetworkGame::NetworkGame(bool isServer)
{
    m_bIsTcpServer = isServer;
    m_tcpServer = NULL;
    m_tcpSocket = NULL;

    QNetworkProxyFactory::setUseSystemConfiguration(false);

    initUI();

    if(m_bIsTcpServer) //作为服务器端
    {
        m_tcpServer = new QTcpServer(this);
        onBtnTryConnect();
        connect(m_tcpServer, SIGNAL(newConnection()),this, SLOT(slotNewConnection()));
    }
    else   //作为客户端
    {
        m_tcpSocket = new QTcpSocket(this);
        connect(m_tcpSocket, SIGNAL(readyRead()), this, SLOT(slotRecv()));
    }

    connect(ChessBoard::ui->btnTcpConnect, &QPushButton::released, this, &NetworkGame::onBtnTryConnect);
}

void NetworkGame::initUI()
{
    auto& ui = ChessBoard::ui;
    QString ip = ui->leIp->text();
    QString port = ui->sbPort->text();

    if(m_bIsTcpServer)  {  //作为服务器端
        QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();

        // 遍历每个接口
        foreach (QNetworkInterface interface, interfaces) {
            // 如果接口处于活动状态且不是回环接口
            if (interface.isValid() && interface.flags().testFlag(QNetworkInterface::IsUp) && !interface.flags().testFlag(QNetworkInterface::IsLoopBack)) {
                foreach (QNetworkAddressEntry entry, interface.addressEntries()) {
                    // 输出IPv4地址
                    if (entry.ip().protocol() == QAbstractSocket::IPv4Protocol) {
                        ip = entry.ip().toString();
                        qDebug() << "Interface:" << interface.humanReadableName() << "IPv4 Address:" << entry.ip().toString();
                        break;
                    }
                }
            }
        }

        ui->networkGroup->setTitle("服务器-红方的IP和Port");
        ui->btnTcpConnect->setText("监听");
        ui->leIp->setText(ip);
        ui->sbPort->setValue(port.toLong());
        ui->leIp->setReadOnly(true);
        ui->leIp->setDisabled(true);
//        ui->lePort->setReadOnly(true);
    } else {
        ui->networkGroup->setTitle("请输入[服务器]的IP和Port");
        ui->btnTcpConnect->setText("连接");
        ui->btnTcpConnect->show();
        ui->leIp->setText(ip);
        ui->sbPort->setValue(port.toLong());
    }
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

    if(m_tcpSocket)
        m_tcpSocket->write(arry, 3);
}

void NetworkGame::slotNewConnection()
{
    if(m_tcpSocket) return;

    static std::once_flag flag;
    std::call_once(flag, [&]() {
        QString text = QString("Client Connection Successful");
        ui->labConnectStatus->setText(text);
    });


    if (m_tcpServer) {
        m_tcpSocket = m_tcpServer->nextPendingConnection();
        connect(m_tcpSocket, SIGNAL(readyRead()), this, SLOT(slotRecv()));
    }
}

void NetworkGame::slotRecv()
{
    QByteArray arry = m_tcpSocket->readAll();

    int nCheckedID = arry[0];
    int nRow = arry[1];
    int nCol = arry[2];

    //qDebug()<<nCheckedID<<"   "<<nRow<<"   "<<nCol<<"   ";
    ChessBoard::clickPieces(nCheckedID, nRow, nCol);
    update();   // Force repaint so the last-move trail & text stay in sync on both peers
}

void NetworkGame::onBtnTryConnect()
{
    auto& ui = ChessBoard::ui;
    QString text;
    if (ui->leIp->text().isEmpty() || ui->sbPort->text().isEmpty()) {
        text = "IP或Port为空，请设置后重试";
        qDebug() << text;
        ui->labConnectStatus->setText(text);
        return;
    }

    if(m_bIsTcpServer) {  // 服务器-重设端口号
        if (!m_tcpServer) return;
        if (m_tcpServer->isListening()) {
            qDebug() << "Stopping server...";
            m_tcpServer->close();
        }

        // 监听指定地址和端口
        if (m_tcpServer->listen(QHostAddress::Any, ui->sbPort->text().toLong())) {
            text = QString("Server is listening on \"%1\" port \"%2\"").arg(m_tcpServer->serverAddress().toString()).arg(m_tcpServer->serverPort());
        } else {
            text = QString("Server failed to start: %1").arg(m_tcpServer->errorString());
        }

    } else {  // 客户端-输入IP+Port尝试连接服务器
        if (!m_tcpSocket) return;
        const QString& ip = ui->leIp->text();
        const QString& port = ui->sbPort->text();
        m_tcpSocket->connectToHost(QHostAddress(ip), port.toInt());
        // 等待连接成功或失败
        if (m_tcpSocket->waitForConnected()) {
            text = "Server Connection Successful： " + ip + ":" + port;
        } else {
            text = "Server connection failed: " + m_tcpSocket->errorString();
        }
    }

    qDebug() << text;
    ui->labConnectStatus->setText(text);

}
