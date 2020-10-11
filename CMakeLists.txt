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
if (Qt5Core_FOUND AND Qt5Widgets_FOUND AND Qt5Gui_FOUND AND
        Qt5OpenGL_FOUND AND Qt5Network_FOUND AND Qt5Xml_FOUND AND Qt5Svg_FOUND)
    set(QT_INCLUDES ${QT_INCLUDES}
            ${Qt5Core_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS} ${Qt5OpenGL_INCLUDE_DIRS}
            ${Qt5Network_INCLUDE_DIRS} ${Qt5Xml_INCLUDE_DIRS} ${Qt5Svg_INCLUDE_DIRS})
    include_directories(${QT_INCLUDES})
endif()

qt5_wrap_cpp(MOC_SRCS NetworkGame.h
        SelectGameMode.h
        ChooseMainWindow.h
        ChessStep.h
        ChessBoard.h
        AboutAuthor.h)
qt5_wrap_ui(UI_HEADERS AboutAuthor.ui
        ChessBoard.ui)
qt5_add_resources(QRCS chooseresource.qrc)

set(SRCS_FILES AboutAuthor.cpp
        ChessBoard.cpp
        ChessPieces.cpp
        ChessStep.cpp
        ChooseMainWindow.cpp
        MachineGame.cpp
        NetworkGame.cpp
        SelectGameMode.cpp
        main.cpp)

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
        )