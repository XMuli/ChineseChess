#include <QApplication>

#include "SelectGameMode.h"
#include "ChooseMainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SelectGameMode dlg;
    dlg.setWindowTitle("选择游戏方式");
    dlg.setFixedSize(200,120);
    if(dlg.exec() != QDialog::Accepted)
    {
        return 0;
    }

    ChooseMainWindow wnd(dlg.m_nSelect);


    return a.exec();
}
