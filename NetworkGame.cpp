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
#include <QHostAddress>
#include <QStringList>
#include <algorithm>

namespace {
struct IpCandidate {
    QString ip;
    QString label;
    int priority = 2;
};

bool isInterfaceUsable(const QNetworkInterface& iface)
{
    if (!iface.isValid())
        return false;
    const auto flags = iface.flags();
    if (!(flags & QNetworkInterface::IsUp) || !(flags & QNetworkInterface::IsRunning))
        return false;
    if (flags & QNetworkInterface::IsLoopBack)
        return false;
    return true;
}

int interfacePriority(const QNetworkInterface& iface)
{
    const QString human = iface.humanReadableName().toLower();
    const QString raw = iface.name().toLower();
    auto containsAny = [&](const QStringList& keys) {
        for (const QString& key : keys) {
            if (human.contains(key) || raw.contains(key))
                return true;
        }
        return false;
    };

    if (containsAny({"wlan", "wifi", "wi-fi", "wireless", "wl"}))
        return 0; // Wi-Fi
    if (containsAny({"eth", "en", "lan"}))
        return 1; // Ethernet
    return 2;      // Others
}

QString interfaceLabel(int priority)
{
    switch (priority) {
    case 0: return QObject::tr("Wi-Fi");
    case 1: return QObject::tr("Ethernet");
    default: return QObject::tr("Other");
    }
}

QList<IpCandidate> collectIpCandidates()
{
    QList<IpCandidate> result;
    const auto interfaces = QNetworkInterface::allInterfaces();

    for (const QNetworkInterface& iface : interfaces) {
        if (!isInterfaceUsable(iface))
            continue;

        const int priority = interfacePriority(iface);
        const QString tag = interfaceLabel(priority);
        for (const QNetworkAddressEntry& entry : iface.addressEntries()) {
            const QHostAddress addr = entry.ip();
            if (addr.protocol() != QAbstractSocket::IPv4Protocol)
                continue;

            const QString ip = addr.toString();
            const bool duplicate = std::any_of(result.cbegin(), result.cend(), [&](const IpCandidate& candidate) {
                return candidate.ip == ip;
            });
            if (duplicate)
                continue;

            IpCandidate candidate;
            candidate.ip = ip;
            candidate.priority = priority;
            candidate.label = QStringLiteral("%1  (%2 · %3)").arg(ip, tag, iface.humanReadableName());
            result.append(candidate);
        }
    }

    std::sort(result.begin(), result.end(), [](const IpCandidate& lhs, const IpCandidate& rhs) {
        if (lhs.priority != rhs.priority)
            return lhs.priority < rhs.priority;
        return lhs.ip < rhs.ip;
    });

    return result;
}
} // namespace

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
    const QString preservedIp = currentIpText();
    QString port = ui->sbPort->text();
    populateLocalIpChoices(m_bIsTcpServer ? QString() : preservedIp);

    if(m_bIsTcpServer)  {  //作为服务器端
        ui->networkGroup->setTitle("服务器-红方的IP和Port");
        ui->btnTcpConnect->setText("监听");
        ui->comboIp->setEditable(false);
        ui->sbPort->setValue(port.toLong());
    } else {
        ui->networkGroup->setTitle("请输入[服务器]的IP和Port");
        ui->btnTcpConnect->setText("连接");
        ui->btnTcpConnect->show();
        ui->comboIp->setEditable(true);
        if (!preservedIp.isEmpty()) {
            ui->comboIp->setEditText(preservedIp);
        }
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
    const QString ipText = currentIpText();
    if (ipText.isEmpty() || ui->sbPort->text().isEmpty()) {
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
        const QString& ip = ipText;
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

void NetworkGame::populateLocalIpChoices(const QString& preferredIp)
{
    auto combo = ChessBoard::ui->comboIp;
    if (!combo)
        return;

    const QList<IpCandidate> candidates = collectIpCandidates();
    const QString targetIp = preferredIp.trimmed();

    combo->blockSignals(true);
    combo->clear();
    for (const auto& candidate : candidates) {
        combo->addItem(candidate.label, candidate.ip);
    }
    if (!targetIp.isEmpty() && combo->findData(targetIp) == -1) {
        combo->addItem(targetIp, targetIp);
    }

    int index = -1;
    if (!targetIp.isEmpty()) {
        index = combo->findData(targetIp);
    }
    if (index < 0 && !candidates.isEmpty()) {
        index = 0;
    }

    if (index >= 0) {
        combo->setCurrentIndex(index);
    } else {
        combo->setEditText(targetIp.isEmpty() ? QStringLiteral("127.0.0.1") : targetIp);
    }

    combo->blockSignals(false);
}

QString NetworkGame::currentIpText() const
{
    const auto combo = ChessBoard::ui->comboIp;
    if (!combo)
        return {};

    QString ip = combo->currentData().toString();
    if (ip.isEmpty())
        ip = combo->currentText();
    return ip.trimmed();
}
