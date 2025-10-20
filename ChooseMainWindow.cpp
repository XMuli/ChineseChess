// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2019-2025 XMuli & Contributors
// SPDX-GitHub: https://github.com/XMuli/ChineseChess
// SPDX-Author: XMuli <xmulitech@gmail.com>

#include "ChooseMainWindow.h"

#include <QApplication>
#include <QMessageBox>
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>

ChooseMainWindow::ChooseMainWindow(QWidget *parent) : QDialog(parent)
{
    this->setWindowTitle(QString("选择游戏方式 %1").arg(XPROJECT_VERSION));
    this->setFixedSize(360, 160);
    this->setWindowIcon(QIcon(":/images/chess.svg"));

    QVBoxLayout* lay = new QVBoxLayout(this);
    lay->addWidget(m_buttons[0] = new QPushButton("玩家自己对战"));
    lay->addWidget(m_buttons[1] = new QPushButton("玩家和AI对战"));
    lay->addWidget(m_buttons[2] = new QPushButton("双人网络对战"));

    /*游戏方式一: 自己和自己下棋【同一台PC机器】*/
    connect(m_buttons[0], &QPushButton::clicked,[=](){
        this->hide();
        m_pAgainstYourself = new ChessBoard();
        m_pAgainstYourself->showNetworkGui(false);
        m_pAgainstYourself->setWindowTitle(QString("玩家自己对战 %1").arg(XPROJECT_VERSION));
        m_pAgainstYourself->show();

        //返回主窗口
        connect(m_pAgainstYourself,&ChessBoard::toMenu,[=](){
            m_pAgainstYourself->close();
            this->show();
        });
    });

    /*游戏方式二: 自己和电脑下棋【同一台PC机器】*/
    connect(m_buttons[1], &QPushButton::clicked,[=](){
        this->hide();

        m_pMachineGame = new MachineGame();
        m_pMachineGame->showNetworkGui(false);
        m_pMachineGame->setWindowTitle(QString("玩家和AI对战 %1").arg(XPROJECT_VERSION));
        m_pMachineGame->show();

        //返回主窗口
        connect(m_pMachineGame,&ChessBoard::toMenu,[=](){
            m_pMachineGame->close();
            this->show();
        });
    });

    /*游戏方式三: 双人网络对战下棋【可在局域网/广域网的不同台PC机器】
      - 一台实体主机: 一台主机，一台虚拟机，网络桥接模式
      - 两台实体主机: 同一局域网，或者都具有公网IP的广域网*/
    connect(m_buttons[2], &QPushButton::clicked,[=](){
        this->hide();
        QMessageBox::StandardButtons ret = QMessageBox::question(
            this,
            "提示",
            "是否作为[服务器]启动?<br>"
            "- Yes: 服务器, 属红方<br>"
            "- No: 客户端, 属黑方<br><br>"
            "<a href=\"https://github.com/XMuli/ChineseChess/wiki/%E7%BD%91%E7%BB%9C%E5%AF%B9%E6%88%98%E6%A8%A1%E5%BC%8F%E8%AE%BE%E7%BD%AE\">📢:  📖 Wiki</a>",
            QMessageBox::Yes | QMessageBox::No
            );

        const bool& bServer = ret == QMessageBox::Yes ? true : false;

        m_pNetworkGame = new NetworkGame(bServer);
        m_pNetworkGame->showNetworkGui(true);
        const QString& title = QString("双人网络对战 [%1] [%2]").arg(bServer ? "服务器 - 红方" : "客户端 - 黑方").arg(XPROJECT_VERSION) ;
        m_pNetworkGame->setWindowTitle(title);
        m_pNetworkGame->show();

        //返回主窗口
        connect(m_pNetworkGame,&ChessBoard::toMenu,[=](){
            m_pNetworkGame->close();
            this->show();
        });
    });
}


