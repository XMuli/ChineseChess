#ifndef NETWORKGAME_H
#define NETWORKGAME_H

#include "ChessBoard.h"
#include <QTcpServer>
#include <QTcpSocket>

//-----------------------------------------------------------------------
//定义传输协议：
//第一个字节：表示点击的棋子ID；第二个字节：表示点击的行row，第三个字节：表示点击的列col
//-----------------------------------------------------------------------

class NetworkGame : public ChessBoard
{
    Q_OBJECT

public:
    NetworkGame(bool isServer);
    ~NetworkGame();

    QTcpServer* m_tcpServer; //服务器
    QTcpSocket* m_tcpSocket; //套接字

    virtual void clickPieces(int checkedID, int& row, int& col);  //继承ChessBoard类的虚函数重写，是mousePressEvent()时间里面余下的部分

public slots:
    void slotNewConnection();
    void slotRecv();
};

#endif // NETWORKGAME_H
