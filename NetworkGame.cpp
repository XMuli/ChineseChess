// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2019-2026 XMuli & Contributors
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
#include <QSignalBlocker>
#include <QComboBox>
#include <QSpinBox>
#include <algorithm>
#include <iterator>

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
    case 0: return QStringLiteral("Wi-Fi");
    case 1: return QStringLiteral("Ethernet");
    default: return QStringLiteral("Other");
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
    setPerspectiveFlipped(!isServer);
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
    connect(ChessBoard::ui->comboIp, &QComboBox::currentTextChanged, this, &NetworkGame::handleServerEndpointChange);
    connect(ChessBoard::ui->sbPort, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &NetworkGame::handleServerEndpointChange);
}

void NetworkGame::initUI()
{
    auto& ui = ChessBoard::ui;
    const QString preservedIp = currentIpText();
    const int preservedPort = ui->sbPort->value();

    if(m_bIsTcpServer)  {  //作为服务器端
        ui->networkGroup->setTitle("服务器-红方的IP和Port");
        ui->btnTcpConnect->setText("监听");
        const QList<IpCandidate> candidates = collectIpCandidates();
        QStringList ipList;
        std::transform(candidates.cbegin(), candidates.cend(), std::back_inserter(ipList), [](const IpCandidate& c){ return c.ip; });
        populateLocalIpChoices(ipList, ipList.isEmpty() ? QStringLiteral("127.0.0.1") : ipList.first());
        ui->comboIp->setEditable(false);
        ui->comboIp->setEnabled(true);
        ui->comboIp->setStyleSheet(QString());
        {
            QSignalBlocker blocker(ui->sbPort);
            ui->sbPort->setValue(preservedPort);
        }
    } else {
        ui->networkGroup->setTitle("请输入[服务器]的IP和Port");
        ui->btnTcpConnect->setText("连接");
        ui->btnTcpConnect->show();
        ui->comboIp->clear();
        ui->comboIp->setEditable(true);
        ui->comboIp->setEnabled(true);
        ui->comboIp->setStyleSheet(QStringLiteral(
            "QComboBox::drop-down { width: 0px; border: none; }\n"
            "QComboBox::down-arrow { image: none; }"
        ));
        ui->comboIp->setEditText(preservedIp);
        {
            QSignalBlocker blocker(ui->sbPort);
            ui->sbPort->setValue(preservedPort);
        }
    }
}

void NetworkGame::clickPieces(int checkedID, int &row, int &col)
{
    // 本地只能选中己方棋子，禁止移动对手棋子
    if (m_nSelectID == -1 && checkedID >= 0 && checkedID < 32) {
        if (m_ChessPieces[checkedID].m_bRed != m_bIsTcpServer)
            return;
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

    // 悔棋命令：0xFE 标记
    if (static_cast<unsigned char>(arry[0]) == 0xFE) {
        ChessBoard::back();
        update();
        return;
    }

    int nCheckedID = arry[0];
    int nRow = arry[1];
    int nCol = arry[2];

    //qDebug()<<nCheckedID<<"   "<<nRow<<"   "<<nCol<<"   ";
    ChessBoard::clickPieces(nCheckedID, nRow, nCol);
    update();   // Force repaint so the last-move trail & text stay in sync on both peers
}

void NetworkGame::back()
{
    // 只允许悔自己刚走的棋（当前轮到对方，说明自己刚走完）
    if (m_ChessSteps.size() == 0 || m_bIsOver)
        return;

    bool currentTurnIsMyColor = (m_bIsRed == m_bIsTcpServer);
    if (currentTurnIsMyColor) {
        // 当前轮到自己，说明对方刚走完，不能悔对方的棋
        return;
    }

    // 发送悔棋命令到对端
    char arry[3];
    arry[0] = static_cast<char>(0xFE);
    arry[1] = 0;
    arry[2] = 0;
    if (m_tcpSocket)
        m_tcpSocket->write(arry, 3);

    // 本地执行悔棋
    ChessBoard::back();
    update();
}

void NetworkGame::onBtnTryConnect()
{
    auto& ui = ChessBoard::ui;
    QString text;
    const QString ipText = currentIpText();
    const QString portText = ui->sbPort->text();
    if ((m_bIsTcpServer && ipText.isEmpty()) || portText.isEmpty()) {
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

        QHostAddress bindAddress;
        if (!bindAddress.setAddress(ipText)) {
            text = QString("Invalid server IP: %1").arg(ipText);
            ui->labConnectStatus->setText(text);
            qDebug() << text;
            return;
        }

        const quint16 portValue = static_cast<quint16>(ui->sbPort->value());
        // 监听指定地址和端口
        if (m_tcpServer->listen(bindAddress, portValue)) {
            text = QString("Server is listening on \"%1\" port \"%2\"").arg(bindAddress.toString()).arg(portValue);
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

void NetworkGame::handleServerEndpointChange()
{
    if (m_bIsTcpServer) {
        onBtnTryConnect();
    }
}

void NetworkGame::populateLocalIpChoices(const QStringList& candidates, const QString& preferredIp)
{
    auto combo = ChessBoard::ui->comboIp;
    if (!combo)
        return;

    const QString targetIp = preferredIp.trimmed();

    combo->blockSignals(true);
    combo->clear();
    for (const QString& ip : candidates) {
        combo->addItem(ip, ip);
    }
    if (!targetIp.isEmpty() && combo->findData(targetIp) == -1) {
        combo->addItem(targetIp, targetIp);
    }

    if (!targetIp.isEmpty()) {
        const int index = combo->findData(targetIp);
        if (index >= 0) {
            combo->setCurrentIndex(index);
        } else {
            combo->setEditText(targetIp);
        }
    } else if (combo->count() > 0) {
        combo->setCurrentIndex(0);
    } else {
        combo->setEditText(QStringLiteral("127.0.0.1"));
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
