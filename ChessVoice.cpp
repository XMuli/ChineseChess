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
