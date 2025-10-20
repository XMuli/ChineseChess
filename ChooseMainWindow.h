// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2019-2025 XMuli & Contributors
// SPDX-GitHub: https://github.com/XMuli/ChineseChess
// SPDX-Author: XMuli <xmulitech@gmail.com>

#ifndef CHOOSEMAINWINDOW_H
#define CHOOSEMAINWINDOW_H

#include <QWidget>
#include "ChessBoard.h"
#include "MachineGame.h"
#include "NetworkGame.h"
#include "ChessBoard.h"

class ChooseMainWindow : public QDialog
{
    Q_OBJECT
public:
    explicit ChooseMainWindow(QWidget *parent = nullptr);
    virtual ~ChooseMainWindow() = default;

private:
    QPushButton* m_buttons[3];
    ChessBoard*  m_pAgainstYourself;
    MachineGame* m_pMachineGame;
    NetworkGame* m_pNetworkGame;
};

#endif // CHOOSEMAINWINDOW_H
