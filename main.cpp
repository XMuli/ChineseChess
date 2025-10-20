//-------------------------------------------------
// 联系作者:
// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2019-2025 XMuli & Contributors
// SPDX-GitHub: https://github.com/XMuli/ChineseChess
// SPDX-Author: XMuli <xmulitech@gmail.com>

// GitHub:        https://github.com/XMuli/ChineseChess
// Site:          https://chinesechess.xmuli.tech
// More Products  https://product.xmuli.tech
// Telegram:      https://t.me/xmuli
// CSDN Bolg:     https://blog.csdn.net/qq_33154343
// My Blog:       https://xmuli.tech
//-------------------------------------------------

#include <QApplication>
#include "ChooseMainWindow.h"

/***
 *  佛曰:
 *          写字楼里写字间，写字间里程序员；
 *          程序人员写程序，又拿程序换酒钱。
 *          酒醒只在网上坐，酒醉还来网下眠；
 *          酒醉酒醒日复日，网上网下年复年。
 *          但愿老死电脑间，不愿鞠躬老板前；
 *          奔驰宝马贵者趣，公交自行程序员。
 *          别人笑我忒疯癫，我笑自己命太贱；
 *          不见满街漂亮妹，哪个归得程序员？
 */


/**
 * @brief 环境： 本工程可以用 Qt 5.15.2 和 6.8.3 LTS 版本同时可编译通过
 * @param IDE： 推荐直接只用 Qt Creator 打开 CMakeLists.txt 进行构建
 * @param Other： 也可以自行 CMake 转 .sln 使用 Visual Studio 2022 构建
 * @note  更多项目集： https://product.xmuli.tech/
 */
int main(int argc, char *argv[])
{

    // 启用高 DPI 缩放
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    qDebug() << "Using Qt 6 or newer";
    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough); // support 1.25 1.5
#else
    qDebug() << "Using Qt 5";
    // QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#endif

    qApp->setOrganizationName(QStringLiteral("XMuli"));                 // 因多处使用 QSettings，故声明组织等信息
    qApp->setOrganizationDomain(QStringLiteral("github.com/XMuli"));
    QApplication a(argc, argv);

    ChooseMainWindow c;
    c.show();

    return a.exec();
}
