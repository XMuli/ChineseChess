#-------------------------------------------------
#
# Project created by QtCreator 2019-01-22T19:52:58
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChineseChess
TEMPLATE = app


SOURCES += main.cpp\
        ChessBoard.cpp \
    ChessPieces.cpp \
    ChessStep.cpp \
    MachineGame.cpp \
    NetworkGame.cpp

HEADERS  += ChessBoard.h \
    ChessPieces.h \
    ChessStep.h \
    MachineGame.h \
    NetworkGame.h

FORMS    += chessboard.ui
