#include "NetworkGame.h"
#include <QDebug>

NetworkGame::NetworkGame(bool isServer)
{
    m_tcpServer = NULL;
    m_tcpSocket = NULL;

    if(isServer) //作为服务器端
    {
        m_bIsTcpServer = true;

        m_tcpServer = new QTcpServer(this);
        m_tcpServer->listen(QHostAddress::Any, 9999);

        connect(m_tcpServer, SIGNAL(newConnection()),this, SLOT(slotNewConnection()));
    }
    else   //作为客户端
    {
        m_bIsTcpServer = false;

        m_tcpSocket = new QTcpSocket(this);
        m_tcpSocket->connectToHost(QHostAddress("127.0.0.1"), 9999);

        connect(m_tcpSocket, SIGNAL(readyRead()), this, SLOT(slotRecv()));
    }


}


NetworkGame::~NetworkGame()
{

}


void NetworkGame::clickPieces(int checkedID, int &row, int &col)
{
    //不能够替对方选棋和下棋
    if(m_bIsTcpServer) //作为服务器一方  不能替黑棋下棋
    {
        //选棋[非下棋]这一步过程，使得其无法选择中黑棋
        if(m_nSelectID == -1 && m_nCheckedID != -1 )
        {
            if(m_bIsTcpServer != m_ChessPieces[checkedID].m_bRed )
                return ;
        }
    }
    else  //作为客户端一方  不能替红棋下棋
    {
        //选棋[非下棋]这一步过程，使得其无法选择中红棋
        if(m_nSelectID == -1 && m_nCheckedID != -1)
        {
            if(m_bIsTcpServer != m_ChessPieces[checkedID].m_bRed )
                return ;
        }
    }

    whoWin();

    ChessBoard::clickPieces(checkedID, row, col);
    char arry[3];
    arry[0] = checkedID;
    arry[1] = row;
    arry[2] = col;
    m_tcpSocket->write(arry, 3);

}


void NetworkGame::slotNewConnection()
{
    if(m_tcpSocket)
        return;

    m_tcpSocket = m_tcpServer->nextPendingConnection();
    connect(m_tcpSocket, SIGNAL(readyRead()), this, SLOT(slotRecv()));


}


void NetworkGame::slotRecv()
{

    QByteArray arry = m_tcpSocket->readAll();
    int nCheckedID = arry[0];
    int nRow = arry[1];
    int nCol = arry[2];

    ChessBoard::clickPieces(nCheckedID, nRow, nCol);
}

