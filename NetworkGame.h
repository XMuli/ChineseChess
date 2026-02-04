// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2019-2026 XMuli & Contributors
// SPDX-GitHub: https://github.com/XMuli/ChineseChess
// SPDX-Author: XMuli <xmulitech@gmail.com>

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
    void handleServerEndpointChange();

private:
    void populateLocalIpChoices(const QStringList& candidates = QStringList(), const QString& preferredIp = QString());
    QString currentIpText() const;

    QTcpServer* m_tcpServer;
    QTcpSocket* m_tcpSocket;
};

#endif // NETWORKGAME_H
