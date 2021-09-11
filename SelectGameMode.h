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
#ifndef SELECTGAMEMODE_H
#define SELECTGAMEMODE_H

#include <QDialog>
#include <QPushButton>

class SelectGameMode : public QDialog
{
    Q_OBJECT
public:
    explicit SelectGameMode(QWidget *parent = 0);
    ~SelectGameMode();

    QPushButton* m_buttons[4];
    int m_nSelect;

public slots:
    void slotClicked();
};

#endif // SELECTGAMEMODE_H
