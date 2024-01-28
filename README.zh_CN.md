# ChineseChess

<div align=center>
<img src="https://cdn.jsdelivr.net/gh/xmuli/xmuliPic@pic/2021/logo.svg" height="240" width="240" />
</div>
<br>

## 项目介绍

<p align="right"><br><a href="README.md">English</a> | <a href="README.zh_CN.md">简体中文</a></p>

![](https://img.shields.io/github/license/XMuli/chineseChess) ![](https://img.shields.io/github/v/release/XMuli/ChineseChess?style=flat&color=birightgreen)![](https://img.shields.io/badge/powered%20by-XMuli-ff69b4)![](https://img.shields.io/github/stars/XMuli/ChineseChess?style=social) ![](https://img.shields.io/github/forks/XMuli/ChineseChess?style=social&label=Fork)

[![macos-badge](https://github.com/xmuli/ChineseChess/workflows/MacOS/badge.svg)](https://github.com/xmuli/ChineseChess/workflows/MacOS/badge.svg)  [![win-badge](https://github.com/xmuli/ChineseChess/workflows/Windows/badge.svg)](https://github.com/xmuli/ChineseChess/workflows/Windows/badge.svg)  [![ubuntu-badge](https://github.com/xmuli/ChineseChess/workflows/Ubuntu/badge.svg)](https://github.com/xmuli/ChineseChess/workflows/Ubuntu/badge.svg)   ![](https://img.shields.io/github/languages/code-size/XMuli/ChineseChess)  ![](https://img.shields.io/github/downloads/XMuli/ChineseChess/total)
<br>

> 基于`Qt5`开发的中国象棋网络对战平台(含通讯功能)，实现了在单机或联网状态下，无论是单人还是多人，无论使用系统是否相同，均可以实现象棋游戏功能。 

<br>

## 特性

**该项目主要功能模块分为：**

ⅰ 玩家与自己对战

ⅱ 玩家与电脑AI对战 

ⅲ 多人网络对战(可跨不同系统)

ⅳ 对战计时

ⅴ 悔棋（可多步）

ⅵ 下棋轨迹

ⅵ 关于作品信息

<br>

# 运行演示：

<font color=#70AD47 size=4 face="幼圆">**视频演示：**</font> 

[ChineseChess 基于QT的跨平台网络象棋对战演示](https://www.bilibili.com/video/av45509758)

<br>

<font color=#D0087E size=4 face="幼圆">**win10系统演示：**</font>

<img src="https://cdn.jsdelivr.net/gh/xmuli/xmuliPic@pic/2021/20190709004321.gif"  height="500" width="800">

<br>

<font color=#D0087E size=4 face="幼圆">**Linux系统演示：**</font>

<img src="https://cdn.jsdelivr.net/gh/xmuli/xmuliPic@pic/2021/20190709004216.gif"  height="500" width="800">

<br>

<font color=#D0087E size=4 face="幼圆">**MacOS系统演示：**</font>

<img src="https://cdn.jsdelivr.net/gh/xmuli/xmuliPic@pic/2021/20190709004745.gif"  height="500" width="800">

<br>

<font color=#70AD47 size=4 face="幼圆">**跨平台对战演示：**</font>   **MacOS 10.14  vs  Win10**

<img src="https://cdn.jsdelivr.net/gh/xmuli/xmuliPic@pic/2021/20190709004454.gif"  height="500" width="800">

<br>

<font color=#FE7207  size=4 face="幼圆">**作者作品详情：** </font> 

 <img src="https://cdn.jsdelivr.net/gh/xmuli/xmuliPic@pic/2021/about.png" width="100%"/>

<br>

## 更新(2022-2024 v6.x)

### 功能

- 添加悔棋功能，无限制悔棋
- 显示下棋轨迹，当前执手
- 重新开始游戏，点击重开
- 代码逻辑优化，新增注释
- 下棋界面更新，使用古象棋棋字
- 更新关于程序，添加贡献者姓名
- Linux ARM64 deb 树莓派支持： [apt.raspbian-addons.org](https://apt.raspbian-addons.org/debian/pool/main/c/chinesechess/)

<br>

### 演示

<img src="https://cdn.jsdelivr.net/gh/xmuli/xmuliPic@pic/2021/ChineChess.gif" width="90%"/>

<img src="https://fastly.jsdelivr.net/gh/XMuli/xmuliPic@pic/2024/202401282117185.png" width="80%"/>

<br>

## 开发教程

- [项目实战：Qt5／C++：QT象棋【初版】](https://blog.csdn.net/qq_33154343/article/details/80931400) 

- [QT5/C++项目：基于QT的跨平台网络对战象棋（一）](https://blog.csdn.net/qq_33154343/article/details/89284983)

- [QT5/C++项目：基于QT的跨平台网络对战象棋（二）](https://blog.csdn.net/qq_33154343/article/details/89285968)

- [QT5/C++项目：基于QT的跨平台网络对战象棋（三）](https://blog.csdn.net/qq_33154343/article/details/89286553)

## 构建

1. 安装 Qt （Qt >= 5.12.11）和其他依赖

   以 Debian 和 Ubuntu 为例，执行:
   
   ```bash
   $ sudo apt install cmake qtbase5-dev qt5-default libqt5svg5-dev qtmultimedia5-dev qttools5-dev libqt5x11extras5-dev
   ```
   
2. 运行命令:

   ```bash
   $ git clone https://github.com/XMuli/ChineseChess.git
   $ cd ChineseChess
   $ mkdir build && cd build
   $ cmake ..  # or qmake
   $ make
   ```


或者，你可以跳过第 2 步，直接使用 Qt Creator 进行编译和运行。

<br>

## 贡献者

感谢的小伙伴提交的贡献 🥳🥳:

<br>

<table frame=void>
    <tr>
      <th align="center" style="width: 80px;">
        <a href="https://github.com/XMuli">
          <img src="https://cdn.jsdelivr.net/gh/xmuli/xmuliPic@pic/2020/20201101220931.png" width="50px"><br>            
          <sub>XMuli</sub>
        </a>
      </th>        
      <th align="center" style="width: 80px;">
        <a href="https://github.com/Bruce-Ch">
          <img src="https://cdn.jsdelivr.net/gh/xmuli/xmuliPic@pic/2020/20200709204616.png" width="50px"><br>
          <sub>Bruce-Ch</sub>
        </a>
      </th>
      <th align="center" style="width: 80px;">
        <a href="https://github.com/BlueArvin">
          <img src="https://cdn.jsdelivr.net/gh/xmuli/xmuliPic@pic/2020/20200727212509.png" width="50px"><br>
          <sub>BlueArvin</sub>
        </a>
      </th>
         <th align="center" style="width: 80px;">
        <a href="https://github.com/Ubuntuser2012">
          <img src="https://cdn.jsdelivr.net/gh/xmuli/xmuliPic@pic/2020/20201101215738.png" width="50px"><br>
          <sub>Ubuntuser2012</sub>
        </a>
      </th>
         <th align="center" style="width: 80px;">
        <a href="https://github.com/kira-yamatoo">
          <img src="https://cdn.jsdelivr.net/gh/xmuli/xmuliPic@pic/2021/20210911163133.png" width="50px"><br>
          <sub>kirayamatoo</sub>
      </th>
         <th align="center" style="width: 80px;">
        <a href="https://github.com/hmsjy2017">
          <img src="https://cdn.jsdelivr.net/gh/xmuli/xmuliPic@pic/2021/20211227232947.png" width="50px"><br>
          <sub>hmsjy2017</sub>
        </a>
    </tr>
         <th align="center" style="width: 80px;">
        <a href="https://github.com/ryanfortner">
          <img src="https://cdn.jsdelivr.net/gh/XMuli/xmuliPic@pic/2022/71036629.png" width="50px"><br>
          <sub>ryanfortner</sub>
        </a>
       <th align="center" style="width: 80px;">
        <a href="https://github.com/zjuyk">
          <img src="https://fastly.jsdelivr.net/gh/XMuli/xmuliPic@pic/2024/202401282118007.png" width="50px"><br>
          <sub>zjuyk</sub>
        </a>
     </tr>
  </thead>
</table>



<br>

若是帮助到了你，或者觉得有用，<font color=#FE7207  size=4 face="幼圆">可以点击该项目的的 <font color=#D0087E size=4 face="幼圆">**⭐Star** </font>和<font color=#D0087E size=4 face="幼圆">**🍴 Fork**</font> 的两个图标，方便抬手之间，表示点个赞，手有余香，</font>其次才是一份冰的肥宅快乐水。

<br>

## 作者

[![alt text](https://img.shields.io/badge/QQ-%E5%81%95%E8%87%A7-brightgreen)](https://sighttp.qq.com/authd?IDKEY=31f3ef7312b39e2c8dc822ae2f4c3b3118e1a6f31cc83373) [![alt text](https://img.shields.io/badge/GitHub-XMuli-brightgreen)](https://github.com/XMuli) [![alt text](https://img.shields.io/badge/Blog-%E5%81%95%E8%87%A7%E7%9A%84%E5%B0%8F%E7%AB%99-ff69b4)](https://ifmet.cn/) 

<br>

## 系列教程

[QtExamples](https://github.com/XMuli/QtExamples)  欢迎 `star` ⭐ 和 `fork` 🍴 这个系列的 `C++ / QT / DTK` 学习，这里你可以学到如何亲自编写这类软件的经验，这是一系列完整的教程，并且**免费**！

