#include "ChessBoard.h"
#include "ui_ChessBoard.h"

ChessBoard::ChessBoard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChessBoard)
{
    ui->setupUi(this);
}

ChessBoard::~ChessBoard()
{
    delete ui;
}
