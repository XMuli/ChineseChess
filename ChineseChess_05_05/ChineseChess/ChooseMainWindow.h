#ifndef CHOOSEMAINWINDOW_H
#define CHOOSEMAINWINDOW_H

#include <QWidget>
#include "ChessBoard.h"
#include "MachineGame.h"
#include "NetworkGame.h"


class ChooseMainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ChooseMainWindow(int nChooseGame, QWidget *parent = 0);
    ~ChooseMainWindow();

    int m_nChooseGame;
    ChessBoard* m_p1;
    MachineGame* m_p2;
    NetworkGame* m_p3;

};

#endif // CHOOSEMAINWINDOW_H
