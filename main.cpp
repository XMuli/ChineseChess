#include "ChessBoard.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChessBoard w;
    w.show();

    return a.exec();
}
