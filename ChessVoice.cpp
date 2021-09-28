/*
 * Author:  kirayamato
 * mail:    kirawhile1@gmail.com
 * github:  https://github.com/kira-yamatoo
 * blogs:   http://www.kirayamato.fun/
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
