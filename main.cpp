// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2019-2025 XMuli & Contributors
// SPDX-GitHub: https://github.com/XMuli/ChineseChess
// SPDX-Author: XMuli <xmulitech@gmail.com>

//-------------------------------------------------
// Project created by QtCreator 2019-01-22T19:52:58
//
// 关于作者:
// 偕臧 xmulitech@gmail.com
// 项目完成时间: 2019-02-01
// 功能更新时间: 2025-10-10
// 其他:如果觉得该作品对你有用，或者有疑惑或者感谢，可以联系作者或者打赏;
//     对我的 Star 和 Fork 是最大鼓励；当然有人欢迎你提交在 GitHub 提交 PR,
//     已将源码和思路开源公布于我的github和博客，供大家学习参考
//
// 联系作者:
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
 * @brief 环境： 本工程可以用 Qt 5.15.2 和 6.8.3 两个长期版本编译通过
 * @param IDE： 推荐直接只用 Qt Creator 打开 CMakeLists.txt 进行构建
 * @param Other： 也可以自行 CMake 转 .sln 使用 Visual Studio 2022 构建
 * @note
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ChooseMainWindow c;
    c.show();

    return a.exec();
}
