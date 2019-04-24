#-------------------------------------------------
#
# Project created by QtCreator 2019-01-22T19:52:58
#
#
#关于作者:
#光谷北斗国际学院 2015级软件工程(1)班 张XX
#作品完成时间:2019-2-1
#作品用途: 毕业设计作品
#其他:如果觉得该作品对你有用，或者有疑惑或者感谢，可以联系作者或者打赏。待毕业设计完成后，会将源码和思路开源公布于我的github和博客，供大家学习参考
#
#联系作者:
#QQ:252311126
#github: https://github.com/touwoyimuli/Qt_ChinessChess/releases
#Twitter: touwoyimuli
#Facebook: touwoyimuli
#Telegram: https://t.me/joinchat/AAAAAEsU6akLiS41OXPzPQ
#QQ GMAILE: 252311126@qq.com
#GOOGLE GMAILE: 252311126@gmial.com
#Personal Blog: 愿以百年挽朝夕的博客
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


RC_ICONS = ./images/qaz.ico

DISTFILES += \
    ChessRunIcon.rc \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

RC_FILE = \
    ChessRunIcon.rc

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android


