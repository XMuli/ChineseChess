#ifndef NETWORKGAME_H
#define NETWORKGAME_H

#include "ChessBoard.h"
#include <QTcpServer>
#include <QTcpSocket>

//定义协议：
//第一个字节：表示点击的棋子ID；第二个字节：表示点击的行row，第三个字节：表示点击的列col

class NetworkGame : public ChessBoard
{
    Q_OBJECT

public:
    NetworkGame(bool isServer);
    ~NetworkGame();



    QTcpServer* m_tcpServer;
    QTcpSocket* m_tcpSocket;

    //virtual void mousePressEvent(QMouseEvent *);    //鼠标点击事件
    virtual void clickPieces(int checkedID, int& row, int& col);


public slots:
    void slotNewConnection();
    void slotRecv();
};

#endif // NETWORKGAME_H
