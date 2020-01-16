#-------------------------------------------------
#
# Project created by QtCreator 2019-01-22T19:52:58
#
#
#关于作者:
#touwoyimuli@gmail.com
#项目完成时间:2019-02-01
#其他:如果觉得该作品对你有用，或者有疑惑或者感谢，可以联系作者或者打赏。已将源码和思路开源公布于我的github和博客，供大家学习参考
#
#联系作者:
#GitHub:        https://github.com/touwoyimuli
#Telegram:      https://t.me/touwoyimuli
#CSDN Bolg:     https://blog.csdn.net/qq_33154343
#GitHub.io Blog:https://touwoyimuli.github.io
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
    NetworkGame.cpp \
    ChooseMainWindow.cpp \
    SelectGameMode.cpp \
    AboutAuthor.cpp

HEADERS  += ChessBoard.h \
    ChessPieces.h \
    ChessStep.h \
    MachineGame.h \
    NetworkGame.h \
    ChooseMainWindow.h \
    SelectGameMode.h \
    AboutAuthor.h

FORMS    += ChessBoard.ui \
    AboutAuthor.ui

RESOURCES += \
    chooseresource.qrc


