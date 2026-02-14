#-------------------------------------------------
# Project created by QtCreator 2019-01-22T19:52:58
#
# 关于作者:
# 偕臧 xmulitech@gmail.com
# 项目完成时间: 2019-02-01
# 功能更新时间: 2026-02-04
# 其他:如果觉得该作品对你有用，或者有疑惑或者感谢，可以联系作者或者打赏;
#     对我的 Star 和 Fork 是最大鼓励；当然有人欢迎你提交在 GitHub 提交 PR,
#     已将源码和思路开源公布于我的github和博客，供大家学习参考
#
# 联系作者:
# GitHub:        https://github.com/XMuli/ChineseChess
# Site:          https://chinesechess.xmuli.tech
# More Products  https://product.xmuli.tech
# Telegram:      https://t.me/xmuli
# CSDN Bolg:     https://blog.csdn.net/qq_33154343
# My Blog:       https://xmuli.tech
#-------------------------------------------------
cmake_minimum_required(VERSION 3.25)

set(project_name ChineseChess)
set(project_version_major 7)
set(project_version_minor 2)
set(project_version_patch 0)
set(project_version ${project_version_major}.${project_version_minor}.${project_version_patch})
project(${project_name} VERSION ${project_version} LANGUAGES CXX)

add_definitions(-DXBUILD_TIME="2026.02.04")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin") # qtcreator + msvc 可执行文件的输出目录
set(CMAKE_BINARY_DIR "${EXECUTABLE_OUTPUT_PATH}")             # visual studio 2022 可执行的输出目录
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR})                      # 创建输出目录

#set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS ON)

# 需要配置环境变量QT5_DIR
# set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} $ENV{QT5_DIR})

set(qt_modules Core Gui Widgets OpenGL Network Xml Svg Multimedia)                        # Network Multimedia WebSockets
set(qt_version_moduls)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS ${qt_modules} LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS ${qt_modules} LinguistTools) # LinguistTools No link

foreach(it ${qt_modules})
    list(APPEND qt_version_moduls Qt${QT_VERSION_MAJOR}::${it})
    message("--->qt_module:" Qt${QT_VERSION_MAJOR}::${it})
endforeach()

# Try to resolve the Qt bin directory regardless of the major version in use.
set(_qt_cmake_dir "")
if(QT_VERSION_MAJOR EQUAL 6 AND DEFINED Qt6_DIR)
    set(_qt_cmake_dir "${Qt6_DIR}")
elseif(QT_VERSION_MAJOR EQUAL 5 AND DEFINED Qt5_DIR)
    set(_qt_cmake_dir "${Qt5_DIR}")
endif()

if(_qt_cmake_dir)
    get_filename_component(_qt_prefix "${_qt_cmake_dir}/.." ABSOLUTE)
    set(QT_BIN_DIR "${_qt_prefix}/bin")
endif()

if(NOT DEFINED QT_BIN_DIR)
    set(QT_BIN_DIR "")
endif()

if(QT_BIN_DIR)
    message(STATUS "Qt bin dir: ${QT_BIN_DIR}")
else()
    message(WARNING "Qt bin directory could not be deduced; deploy helpers may be skipped.")
endif()

set(src_files
    main.cpp
    ChessBoard.h
    ChessBoard.cpp
    ChessBoard.ui
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
    AboutAuthor.cpp
    AboutAuthor.ui
    PuzzleData.h
    PuzzleData.cpp
    PuzzleGame.h
    PuzzleGame.cpp

    resources/res.qrc
    resources/logo/resources.rc
)

#********************************************** 判断且定义 x64/x86 变量 (get kit architecture bit) ****************************
if(CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(arch_bit "86")
    set(is_x64bit false)
elseif(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(arch_bit "64")
    set(is_x64bit true)
endif()

# 定义 lupdate/lrelease 的默认位置，兼容不同平台
set(_qt_tool_suffix "")
if(WIN32)
    set(_qt_tool_suffix ".exe")
endif()

if(UNIX AND NOT APPLE)  # using apt install qt5-devtools*
    execute_process(COMMAND lsb_release -i OUTPUT_VARIABLE LSB_ID ERROR_QUIET)
    if (LSB_ID MATCHES "Deepin" OR LSB_ID MATCHES "UOS")
        set(lupdate_path "/usr/lib/qt5/bin/lupdate")
        set(lrelease_path "/usr/lib/qt5/bin/lrelease")
        message("This is a Deepin or UOS system.")
    else()
        set(lupdate_path "lupdate")
        set(lrelease_path "lrelease")
        message("This is other linux system.")
    endif()
else()
    if(QT_BIN_DIR)
        set(lupdate_path "${QT_BIN_DIR}/lupdate${_qt_tool_suffix}")
        set(lrelease_path "${QT_BIN_DIR}/lrelease${_qt_tool_suffix}")
    else()
        set(lupdate_path "lupdate${_qt_tool_suffix}")
        set(lrelease_path "lrelease${_qt_tool_suffix}")
    endif()
endif()

message("Qt5_DIR:" ${Qt5_DIR})
message("Qt6_DIR:" ${Qt6_DIR})
message("lupdate_path:" ${lupdate_path})
message("lrelease_path:" ${lrelease_path})
message("EXECUTABLE_OUTPUT_PATH:" ${EXECUTABLE_OUTPUT_PATH})
message("CMAKE_BINARY_DIR:" ${CMAKE_BINARY_DIR})
message("CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
message("CMAKE_RUNTIME_OUTPUT_DIRECTORY: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
message("CMAKE_RUNTIME_OUTPUT_DIRECTORY: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")         # exe 和 dll 运行的输出路径
message("CMAKE_LIBRARY_OUTPUT_DIRECTORY: ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")         # 动态链接库（DLL、SO 等）的输出目录(实际不生效)
message("CMAKE_ARCHIVE_OUTPUT_DIRECTORY： ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")         # 静态库的输出目录
#************************************************* 拷贝 .ini 和资源文件 *******************************************************
# copy "resources" 文件夹下的指定文件夹
set(folders_to_copy "licenses" "logo" "debian" "debian_portable")  # "cpack"
set(source_root "${CMAKE_SOURCE_DIR}/resources")
set(traget_root "${EXECUTABLE_OUTPUT_PATH}/resources")

# 遍历复制文件夹集合中的每个文件夹
foreach(it ${folders_to_copy})
    set(copy_source_dir "${source_root}/${it}")
    file(COPY ${copy_source_dir} DESTINATION ${traget_root})
endforeach()

#file(COPY "${CMAKE_SOURCE_DIR}/xconfig.ini" DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
#******************************************* **********************************************

add_executable(${project_name} ${src_files})
target_link_libraries(${project_name} PRIVATE ${qt_version_moduls})

set_target_properties(${project_name} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER https://chinesechess.xmuli.tech
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Define some variables that can be used in *.cpp
target_compile_definitions(${project_name} PRIVATE XPROJECT_NAME="${project_name}")
target_compile_definitions(${project_name} PRIVATE XPROJECT_VERSION="${project_version}")
target_compile_definitions(${project_name} PRIVATE XARCH_BIT="${arch_bit}")
target_compile_definitions(${project_name} PRIVATE XCOMPILER="${CMAKE_HOST_SYSTEM_PROCESSOR}")  # i386/i686/x86_64/unknown  Win: AMD64
target_compile_definitions(${project_name} PRIVATE XCOMPILER_ID="${CMAKE_CXX_COMPILER_ID}")     # Clang/GCC/MSVC or GNU

message("------------BRGIN------------")
message("XPROJECT_NAME:${project_name}")
message("XPROJECT_VERSION:${project_version}")
message("XARCH_BIT:${arch_bit}")
message("XCOMPILER:${CMAKE_HOST_SYSTEM_PROCESSOR}")
message("XCOMPILER_ID:${CMAKE_CXX_COMPILER_ID}")

message("CMake Path:"
    "\nPROJECT_NAME:"  ${project_name}
    "\nCMAKE_INSTALL_PREFIX:"  ${CMAKE_INSTALL_PREFIX}
    "\nPROJECT_BINARY_DIR:"    ${PROJECT_BINARY_DIR}
    "\nCMAKE_INSTALL_BINDIR:"  ${CMAKE_INSTALL_BINDIR}
    "\nCMAKE_INSTALL_LIBDIR:"  ${CMAKE_INSTALL_LIBDIR}
    "\nCMAKE_INSTALL_INCLUDEDIR:"  ${CMAKE_INSTALL_INCLUDEDIR})
message("------------END------------")

target_compile_definitions(${project_name} PRIVATE UNICODE _UNICODE)                         # 定义 XWIDGET_LIBRARY 宏( ET 后面没有 S)，表明为导出。后期将导出为 动态库 封装

if(MSVC)
    # 设置默认启动 project
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${project_name})
    # Fix: Visual Studio 2022 生成的目标文件的输出目录, 移除掉 Release/Debug 的多一层文件夹
    set_target_properties(${project_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${EXECUTABLE_OUTPUT_PATH}")
    set_target_properties(${project_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${EXECUTABLE_OUTPUT_PATH}")
    set_target_properties(${project_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${EXECUTABLE_OUTPUT_PATH}")
    set_target_properties(${project_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${EXECUTABLE_OUTPUT_PATH}")
    set_target_properties(${project_name} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${EXECUTABLE_OUTPUT_PATH}")
    set_target_properties(${project_name} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${EXECUTABLE_OUTPUT_PATH}")
    set_target_properties(${project_name} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL "${EXECUTABLE_OUTPUT_PATH}")
    set_target_properties(${project_name} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${EXECUTABLE_OUTPUT_PATH}")

    # 开启 MSVC 终端上的中文不乱码
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")
    add_compile_options(/source-charset:utf-8 /execution-charset:utf-8)
#    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
#    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
    # 开启 UNICODE 等常规
    target_compile_definitions(${project_name} PRIVATE
        WIN32_LEAN_AND_MEAN                                                                  # Header files containing only the common APIs
        _CRT_SECURE_NO_WARNINGS                                                              # Unsafe functions such as strcpy, scanf, etc. are allowed)
    )
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
        set(VS_STARTUP_PROJECT ${project_name})
    endif(MSVC)
endif()

#******************************************* Qt runtime dependency deployment **********************************************
option(SKIP_DEPLOY "Skip POST_BUILD Qt runtime deployment (for batch build scripts)" OFF)

set(_qt_deploy_hints)
if(QT_BIN_DIR)
    list(APPEND _qt_deploy_hints "${QT_BIN_DIR}")
endif()

set(_qt_runtime_deploy_handled FALSE)
if(NOT SKIP_DEPLOY AND QT_VERSION_MAJOR EQUAL 6)
    include(Qt6DeploySupport OPTIONAL RESULT_VARIABLE _qt6_deploysupport_included)
    if(_qt6_deploysupport_included AND NOT (_qt6_deploysupport_included MATCHES "NOTFOUND") AND COMMAND qt_generate_deploy_app_script)
        qt_generate_deploy_app_script(
            TARGET ${project_name}
            OUTPUT_SCRIPT qt_deploy_script
            NO_COMPILER_RUNTIME
            NO_UNSUPPORTED_PLATFORM_ERROR
        )
        add_custom_command(TARGET ${project_name} POST_BUILD
            COMMAND "${CMAKE_COMMAND}"
                -DQT_DEPLOY_PREFIX="$<TARGET_FILE_DIR:${project_name}>"
                -P "${qt_deploy_script}"
            COMMENT "Deploying Qt runtime dependencies for Qt6 target: ${project_name}"
        )
        set(_qt_runtime_deploy_handled TRUE)
    endif()
endif()

if(NOT SKIP_DEPLOY AND NOT _qt_runtime_deploy_handled)
    if(QT_VERSION_MAJOR EQUAL 6 AND (NOT DEFINED _qt6_deploysupport_included OR _qt6_deploysupport_included MATCHES "NOTFOUND"))
        message(WARNING "Qt6DeploySupport.cmake unavailable; falling back to classic deploy helpers.")
    endif()

    if(WIN32)
        if(_qt_deploy_hints)
            find_program(QT_WINDEPLOYQT_EXECUTABLE
                NAMES windeployqt windeployqt.exe
            HINTS ${_qt_deploy_hints}
            NO_DEFAULT_PATH)
    endif()
    if(NOT QT_WINDEPLOYQT_EXECUTABLE)
        find_program(QT_WINDEPLOYQT_EXECUTABLE NAMES windeployqt windeployqt.exe)
    endif()
    if(QT_WINDEPLOYQT_EXECUTABLE)
        add_custom_command(TARGET ${project_name} POST_BUILD
            COMMAND "${QT_WINDEPLOYQT_EXECUTABLE}"
                --no-opengl-sw
                --no-translations
                --dir "$<TARGET_FILE_DIR:${project_name}>"
                "$<TARGET_FILE:${project_name}>"
            COMMENT "Deploying Qt runtime dependencies with windeployqt"
        )
    else()
        message(WARNING "windeployqt not found; runtime dependencies will not be copied automatically.")
    endif()
elseif(APPLE)
    if(_qt_deploy_hints)
        find_program(QT_MACDEPLOYQT_EXECUTABLE
            NAMES macdeployqt
            HINTS ${_qt_deploy_hints}
            NO_DEFAULT_PATH)
    endif()
    if(NOT QT_MACDEPLOYQT_EXECUTABLE)
        find_program(QT_MACDEPLOYQT_EXECUTABLE NAMES macdeployqt)
    endif()
    if(QT_MACDEPLOYQT_EXECUTABLE)
        add_custom_command(TARGET ${project_name} POST_BUILD
            COMMAND "${QT_MACDEPLOYQT_EXECUTABLE}"
                "$<TARGET_BUNDLE_DIR:${project_name}>"
                -always-overwrite
            COMMENT "Deploying Qt runtime dependencies with macdeployqt"
        )
    else()
        message(WARNING "macdeployqt not found; runtime dependencies will not be copied automatically.")
    endif()
elseif(UNIX)
    if(_qt_deploy_hints)
        find_program(QT_LINUXDEPLOYQT_EXECUTABLE
            NAMES linuxdeployqt
            HINTS ${_qt_deploy_hints}
            NO_DEFAULT_PATH)
    endif()
    if(NOT QT_LINUXDEPLOYQT_EXECUTABLE)
        find_program(QT_LINUXDEPLOYQT_EXECUTABLE NAMES linuxdeployqt)
    endif()
    if(QT_LINUXDEPLOYQT_EXECUTABLE)
        add_custom_command(TARGET ${project_name} POST_BUILD
            COMMAND "${QT_LINUXDEPLOYQT_EXECUTABLE}"
                "$<TARGET_FILE:${project_name}>"
                -always-overwrite
                -bundle-non-qt-libs
                -qmldir "${CMAKE_SOURCE_DIR}"
            COMMENT "Deploying Qt runtime dependencies with linuxdeployqt"
        )
    else()
        message(WARNING "linuxdeployqt not found; runtime dependencies will not be copied automatically.")
    endif()
endif() # platform deploy fallback
endif() # _qt_runtime_deploy_handled
#***************************************************************************************************************************

if(APPLE)
elseif(WIN32)
    # install(TARGETS ${project_name} RUNTIME)
else()
    install(TARGETS ${project_name} RUNTIME DESTINATION /usr/bin)
endif()
