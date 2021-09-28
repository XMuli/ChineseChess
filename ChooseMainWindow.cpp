/*
 * Copyright (C)  2019~2020  偕臧  All rights reserved.
 *
 * Author:  xmuli(偕臧) xmulitech@gmail.com
 *
 * github:  https://github.com/xmuli
 * blogs:   https://ifmet.cn
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
        m_p1 = new ChessBoard();
        m_p1->setWindowTitle("玩家自己对战");
        m_p1->show();

        //返回主窗口
        connect(m_p1,&ChessBoard::toMenu,[=](){
            m_p1->close();
            this->show();
        });
    });

    /*游戏方式二: 自己和电脑下棋【同一台PC机器】*/
    connect(m_buttons[1], &QPushButton::clicked,[=](){
        this->hide();

        m_p2 = new MachineGame();
        m_p2->setWindowTitle("玩家和AI对战");
        m_p2->show();

        //返回主窗口
        connect(m_p2,&ChessBoard::toMenu,[=](){
            m_p2->close();
            this->show();
        });
    });

    /*游戏方式三: 双人局域网下棋【可在局域网下不同台PC机器】*/
    connect(m_buttons[2], &QPushButton::clicked,[=](){
        this->hide();

        QMessageBox::StandardButtons ret = QMessageBox::question(NULL, "提示", "是否作为服务器启动[选择红方]?");

        bool bServer = false;
        if(ret == QMessageBox::Yes)
            bServer = true;

        m_p3 = new NetworkGame(bServer);
        m_p3->setWindowTitle("双人网络对战");
        m_p3->show();

        //返回主窗口
        connect(m_p3,&ChessBoard::toMenu,[=](){
            m_p3->close();
            this->show();
        });
    });





}

ChooseMainWindow::~ChooseMainWindow()
{

}

