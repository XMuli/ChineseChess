#include "ChessBoard.h"
#include <QApplication>

#include "MachineGame.h"
#include "NetworkGame.h"
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*游戏方式一: 自己和自己下棋【同一台PC机器】*/
    ChessBoard w;


    /*游戏方式二: 自己和电脑下棋【同一台PC机器】*/
//    MachineGame w;


    /*游戏方式三: 双人下棋【可在局域网下不同台PC机器】*/
//    QMessageBox::StandardButtons ret = QMessageBox::question(NULL, "提示", "是否作为服务器启动[选择红方]?");

//    bool bServer = false;
//    if(ret == QMessageBox::Yes)
//    {
//        bServer = true;
//    }


//    NetworkGame w(bServer);
    w.show();

    return a.exec();
}
