#-------------------------------------------------
# Project created by QtCreator 2019-01-22T19:52:58
#
# 关于作者:
# 与子偕臧 xmulitech@gmail.com
# 项目完成时间:2019-02-01
# 其他:如果觉得该作品对你有用，或者有疑惑或者感谢，可以联系作者或者打赏;
#     对我的 star 和 fork 是最大鼓励；当然有人欢迎你提交在 github 提交 pr,
#     已将源码和思路开源公布于我的github和博客，供大家学习参考
#
# 联系作者:
# GitHub:        https://github.com/XMuli
# Telegram:      https://t.me/xmuli
# CSDN Bolg:     https://blog.csdn.net/qq_33154343
# My Blog:       https://ifmet.cn
#-------------------------------------------------

QT       += core gui network multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChineseChess
TEMPLATE = app


SOURCES += main.cpp\
    ChessBoard.cpp \
    ChessPieces.cpp \
    ChessStep.cpp \
    ChessVoice.cpp \
    MachineGame.cpp \
    NetworkGame.cpp \
    ChooseMainWindow.cpp \
    AboutAuthor.cpp

HEADERS  += ChessBoard.h \
    ChessPieces.h \
    ChessStep.h \
    ChessVoice.h \
    MachineGame.h \
    NetworkGame.h \
    ChooseMainWindow.h \
    AboutAuthor.h

FORMS    += ChessBoard.ui \
    AboutAuthor.ui

RESOURCES += \
    chooseresource.qrc

RC_FILE = res.rc

