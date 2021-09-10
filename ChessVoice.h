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

    QSound *win =new QSound(":/sound/WinSound.wav",this);
    QSound *select =new QSound(":/sound/selectChess.wav",this);
    QSound *move =new QSound(":/sound/moveChess.wav",this);
    QSound *eat =new QSound(":/sound/eatChess.mp3",this);

    void voiceWin();    //胜利音效
    void voiceSelect(); //选棋音效
    void voiceMove();   //移动音效
    void voiceEat();    //吃子音效


signals:

};

#endif // CHESSVOICE_H
