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
# GitHub:        https://github.com/xmuli
# Telegram:      https://t.me/xmuli
# CSDN Bolg:     https://blog.csdn.net/qq_33154343
# My Blog:       https://ifmet.cn
#-------------------------------------------------

# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)
# 项目信息
project (chinessChess)

set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

# 需要配置环境变量QT5_DIR
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} $ENV{QT5_DIR})

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5Xml REQUIRED)
find_package(Qt5Svg REQUIRED)
find_package(Qt5Multimedia REQUIRED)

if (Qt5Core_FOUND AND Qt5Widgets_FOUND AND Qt5Gui_FOUND AND
        Qt5OpenGL_FOUND AND Qt5Network_FOUND AND Qt5Xml_FOUND AND Qt5Svg_FOUND)
    set(QT_INCLUDES ${QT_INCLUDES}
            ${Qt5Core_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS} ${Qt5OpenGL_INCLUDE_DIRS}
            ${Qt5Network_INCLUDE_DIRS} ${Qt5Xml_INCLUDE_DIRS} ${Qt5Svg_INCLUDE_DIRS})
    include_directories(${QT_INCLUDES})
endif()

qt5_wrap_cpp(MOC_SRCS ChessBoard.h
    ChessPieces.h
    ChessStep.h
    ChessVoice.h
    MachineGame.h
    NetworkGame.h
    ChooseMainWindow.h
    SelectGameMode.h
    AboutAuthor.h)
qt5_wrap_ui(UI_HEADERS AboutAuthor.ui
        ChessBoard.ui)
qt5_add_resources(QRCS chooseresource.qrc)

set(SRCS_FILES main.cpp
    ChessBoard.cpp
    ChessPieces.cpp
    ChessStep.cpp
    ChessVoice.cpp
    MachineGame.cpp
    NetworkGame.cpp
    ChooseMainWindow.cpp
    SelectGameMode.cpp
    AboutAuthor.cpp)

# 指定生成目标
add_executable(${PROJECT_NAME}
        ${SRCS_FILES}
        ${UI_HEADERS}
        ${MOC_SRCS}
        ${QRCS})

target_link_libraries(${PROJECT_NAME}
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Network
        Qt5::Multimedia
        )
