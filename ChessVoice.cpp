#include "ChessVoice.h"



ChessVoice::ChessVoice(QObject *parent) : QObject(parent)
{

}
ChessVoice:: ~ChessVoice()
{

}



void ChessVoice:: voiceWin()
{
    if(win!= nullptr)
        this->win->play();
}

void ChessVoice::voiceSelect()
{
    if(select!= nullptr)
        this->select->play();
}

void ChessVoice:: voiceMove()
{
    if(move!= nullptr)
        this->move->play();
}

void ChessVoice:: voiceEat()
{
    if(eat!= nullptr)
        this->eat->play();
}
