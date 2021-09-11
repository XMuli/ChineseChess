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
 * along with this program.  If not, see <https://touwoyimuli.github.io/>.
 */
#ifndef CHESSVOICE_H
#define CHESSVOICE_H

#include <QObject>
#include <QSound>

class ChessVoice : public QObject
{
    Q_OBJECT
public:
    explicit ChessVoice(QObject *parent = nullptr);
    ~ChessVoice();

    QSound *m_win =new QSound(":/sound/WinSound.wav",this);
    QSound *m_select =new QSound(":/sound/selectChess.wav",this);
    QSound *m_move =new QSound(":/sound/moveChess.wav",this);
    QSound *m_eat =new QSound(":/sound/eatChess.wav",this);

    void voiceWin();    //胜利音效
    void voiceSelect(); //选棋音效
    void voiceMove();   //移动音效
    void voiceEat();    //吃子音效
	
};

#endif // CHESSVOICE_H
