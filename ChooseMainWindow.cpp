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
#include "ChooseMainWindow.h"

#include <QApplication>
#include <QMessageBox>
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>

ChooseMainWindow::ChooseMainWindow(QWidget *parent) : QDialog(parent)

{
    this->setWindowTitle("选择游戏方式");
    this->setFixedSize(250,120);
    this->setWindowIcon(QIcon(":/images/chess.svg"));

    QVBoxLayout* lay = new QVBoxLayout(this);
    lay->addWidget(m_buttons[0] = new QPushButton("玩家自己对战"));
    lay->addWidget(m_buttons[1] = new QPushButton("玩家和AI对战"));
    lay->addWidget(m_buttons[2] = new QPushButton("双人网络对战"));

    /*游戏方式一: 自己和自己下棋【同一台PC机器】*/
    connect(m_buttons[0], &QPushButton::clicked,[=](){
        this->hide();
        m_pAgainstYourself = new ChessBoard();
        m_pAgainstYourself->setNetworkGroupShow(false);
        m_pAgainstYourself->setWindowTitle("玩家自己对战");
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
        m_pMachineGame->setNetworkGroupShow(false);
        m_pMachineGame->setWindowTitle("玩家和AI对战");
        m_pMachineGame->show();

        //返回主窗口
        connect(m_pMachineGame,&ChessBoard::toMenu,[=](){
            m_pMachineGame->close();
            this->show();
        });
    });

    /*游戏方式三: 双人局域网下棋【可在局域网下不同台PC机器】*/
    connect(m_buttons[2], &QPushButton::clicked,[=](){
        this->hide();

        QMessageBox::StandardButtons ret = QMessageBox::question(this, "提示", "是否作为[服务器 - 红方]启动?\n- Yes - 服务器,属红方\n- No - 客户端,属黑方");

        bool bServer = false;
        if(ret == QMessageBox::Yes)
            bServer = true;

        m_pNetworkGame = new NetworkGame(bServer);
        m_pNetworkGame->setNetworkGroupShow(true);
        const QString& title = QString("双人网络对战 [%1]").arg(bServer ? "服务器 - 红方" : "客户端 - 黑方") ;
        m_pNetworkGame->setWindowTitle(title);
        m_pNetworkGame->show();

        //返回主窗口
        connect(m_pNetworkGame,&ChessBoard::toMenu,[=](){
            m_pNetworkGame->close();
            this->show();
        });
    });
}

ChooseMainWindow::~ChooseMainWindow()
{

}

