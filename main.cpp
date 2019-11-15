#include <QApplication>

#include "SelectGameMode.h"
#include "ChooseMainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SelectGameMode dlg;
    if(dlg.exec() != QDialog::Accepted)
    {
        return 0;
    }

    ChooseMainWindow wnd(dlg.m_nSelect);


    return a.exec();
}
