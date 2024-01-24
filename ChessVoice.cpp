// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2019-2024 XMuli & Contributors
// SPDX-GitHub: https://github.com/XMuli/ChineseChess
// SPDX-Author: XMuli <xmulitech@gmail.com>

#include "ChessVoice.h"

ChessVoice::ChessVoice(QObject *parent) : QObject(parent)
{

}
ChessVoice:: ~ChessVoice()
{

}

void ChessVoice:: voiceWin()
{
    if(m_win!= nullptr)
        this->m_win->play();
}

void ChessVoice::voiceSelect()
{
    if(m_select!= nullptr)
        this->m_select->play();
}

void ChessVoice:: voiceMove()
{
    if(m_move!= nullptr)
        this->m_move->play();
}

void ChessVoice:: voiceEat()
{
    if(m_eat!= nullptr)
        this->m_eat->play();
}

void ChessVoice:: voiceBack()
{
    if(m_back!= nullptr)
        this->m_back->play();
}

void ChessVoice:: voiceGeneral()
{
    if(m_general!= nullptr)
        this->m_general->play();
}
