#-------------------------------------------------
#
# Project created by QtCreator 2019-01-22T19:52:58
#
#
#关于作者:
#光谷北斗国际学院 2015级软件工程(1)班 张XX
#作品完成时间:2019-02-01
#作品用途: 毕业设计作品
#其他:如果觉得该作品对你有用，或者有疑惑或者感谢，可以联系作者或者打赏。待毕业设计完成后，会将源码和思路开源公布于我的github和博客，供大家学习参考
#
#联系作者:
#GitHub:        https://github.com/touwoyimuli
#Telegram:      https://t.me/touwoyimuli
#CSDN Bolg:     https://blog.csdn.net/qq_33154343
#Google Gmail:  touwoyimuli@gmail.com
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

FORMS    += chessboard.ui \
    AboutAuthor.ui

RESOURCES += \
    chooseresource.qrc


