#-------------------------------------------------
# Project created by QtCreator 2019-01-22T19:52:58
#
# 关于作者:
# 偕臧 xmulitech@gmail.com
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

# CMake 最低版本号要求
cmake_minimum_required (VERSION 3.3)
# 项目信息
project (ChineseChess)

set(EXECUTABLE_OUTPUT_PATH  ${CMAKE_BINARY_DIR}/bin) # 更改二进制输出路径

# 此处配合 VMSVC 的 UTF8-BOM 插件，达到跨平台
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  message("---using Clang---")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  message("---using GCC---")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
  message("---using Intel C++---")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
        message("---using Visual Studio C++---")
        add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
        add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif()

# msvc multicore compilation
if (WIN32)
    if(MSVC)
        add_definitions(-DUNICODE -D_UNICODE)   # 设置 DUNICODE 编码

                OPTION(USE_MP "use multiple" ON)
                OPTION(ProjectConfig_Global_COMPILE_FLAGS_WITH_MP
                        "Set The Global Option COMPILE_FLAGS /MP to target." ON)
                if(ProjectConfig_Global_COMPILE_FLAGS_WITH_MP OR USE_MP)
                        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /MP")
                        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
                endif()
                set(VS_STARTUP_PROJECT ${PROJECT_NAME})
    endif(MSVC)
endif()

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

qt5_wrap_ui(UI_HEADERS AboutAuthor.ui
        ChessBoard.ui)
qt5_add_resources(QRCS chooseresource.qrc)

set(SRCS_FILES
    main.cpp
    ChessBoard.h
    ChessBoard.cpp
    ChessPieces.h
    ChessPieces.cpp
    ChessStep.h
    ChessStep.cpp
    ChessVoice.h
    ChessVoice.cpp
    MachineGame.h
    MachineGame.cpp
    NetworkGame.h
    NetworkGame.cpp
    ChooseMainWindow.h
    ChooseMainWindow.cpp
    AboutAuthor.h
    AboutAuthor.cpp)

# 指定生成目标
if (APPLE)
    set(MACOSX_BUNDLE_BUNDLE_NAME ${PROJECT_NAME})
    set(MACOSX_BUNDLE_GUI_IDENTIFIER "Org.XMuli.ChineseChess")
    set(MACOSX_BUNDLE_INFO_STRING "Cross-platform and online battle platform game based on Qt: Chinese Chess. Also known as: Xiangqi")

    add_executable(${PROJECT_NAME} MACOSX_BUNDLE
        ${SRCS_FILES}
        ${UI_HEADERS}
        ${QRCS})
else()
    add_executable(${PROJECT_NAME} WIN32
        ${SRCS_FILES}
        ${UI_HEADERS}
        ${QRCS})
endif()

target_link_libraries(${PROJECT_NAME}
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Network
        Qt5::Multimedia
        )

if(APPLE)

elseif(WIN32)
    # install(TARGETS ${PROJECT_NAME} RUNTIME)
else()
    install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION /usr/bin)
endif()
