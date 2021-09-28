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
//#include "SelectGameMode.h"
//#include <QVBoxLayout>

//SelectGameMode::SelectGameMode(QWidget *parent): QDialog(parent)
//{
//    QVBoxLayout* lay = new QVBoxLayout(this);

//    lay->addWidget(m_buttons[0] = new QPushButton("玩家自己对战"));
//    lay->addWidget(m_buttons[1] = new QPushButton("玩家和AI对战"));
//    lay->addWidget(m_buttons[2] = new QPushButton("双人网络对战"));

//    for(int i=0; i<3; i++)
//        connect(m_buttons[i], SIGNAL(clicked()), this, SLOT(slotClicked()));
//}

//SelectGameMode::~SelectGameMode()
//{
//}

//void SelectGameMode::slotClicked()
//{
//    QObject* s = sender();
//    for(int i=0; i<3; ++i)
//    {
//        if(m_buttons[i] == s)
//        {
//            this->m_nSelect = i;
//            break;
//        }
//    }

//    accept();
//}

