#include "ChooseMainWindow.h"

#include <QApplication>
#include "ChessBoard.h"
#include "MachineGame.h"
#include "NetworkGame.h"
#include <QMessageBox>



ChooseMainWindow::ChooseMainWindow(int nChooseGame, QWidget *parent) : QWidget(parent)
{
    m_nChooseGame = nChooseGame;

    if(0 == m_nChooseGame)
    {
        /*游戏方式一: 自己和自己下棋【同一台PC机器】*/
        m_p1 = new ChessBoard();
        m_p1->show();

    }
    else if(1 == m_nChooseGame)
    {
        /*游戏方式二: 自己和电脑下棋【同一台PC机器】*/
        m_p2 = new MachineGame();
        m_p2->show();
    }
    else if(2 == m_nChooseGame)
    {
        /*游戏方式三: 双人下棋【可在局域网下不同台PC机器】*/
        QMessageBox::StandardButtons ret = QMessageBox::question(NULL, "提示", "是否作为服务器启动[选择红方]?");

        bool bServer = false;
        if(ret == QMessageBox::Yes)
        {
            bServer = true;
        }
        m_p3 = new NetworkGame(bServer);
        m_p3->show();
    }
    else
    {

    }


}

ChooseMainWindow::~ChooseMainWindow()
{

    if(0 == m_nChooseGame)
    {
        delete m_p1;
    }
    else if(1 == m_nChooseGame)
    {
        delete m_p2;
    }
    else if(2 == m_nChooseGame)
    {
        delete m_p3;
    }
    else
    {

    }
}

