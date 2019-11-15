#include "ChessBoard.h"
#include <QApplication>

#include "MachineGame.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    //ChessBoard w;
    MachineGame w;
    w.show();

    return a.exec();
}
