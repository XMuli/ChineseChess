# ChinessChess

<div align=center>
<img src="https://cdn.jsdelivr.net/gh/xmuli/xmuliPic@pic/2021/logo.svg" height="240" width="240" />
</div>
<br>

## 项目介绍

<p align="right"><br><a href="README.md">English</a> | <a href="README.zh_CN.md">简体中文</a></p>

![](https://img.shields.io/github/license/XMuli/chinessChess) ![](https://img.shields.io/github/v/release/XMuli/chinessChess?style=flat&color=birightgreen) ![](https://img.shields.io/badge/powered%20by-XMuli-ff69b4)  ![](https://img.shields.io/github/stars/XMuli/chinessChess?style=social) ![](https://img.shields.io/github/forks/XMuli/chinessChess?style=social&label=Fork)

![](https://img.shields.io/github/workflow/status/XMuli/chinessChess/Windows?style=flat&logo=windows) ![](https://img.shields.io/github/workflow/status/XMuli/chinessChess/MacOS?style=flat&logo=apple) ![](https://img.shields.io/github/workflow/status/XMuli/chinessChess/Ubuntu?style=flat&logo=linux) ![](https://img.shields.io/github/languages/code-size/XMuli/chinessChess)  ![](https://img.shields.io/github/downloads/XMuli/chinessChess/total)

<br>

> 基于`Qt5`开发的中国象棋网络对战平台(含通讯功能)，实现了在单机或联网状态下，无论是单人还是多人，无论使用系统是否相同，均可以实现象棋游戏功能。 

<br>

## 特性:

**该项目主要功能模块分为：**

① 玩家与自己对战

② 玩家与电脑AI对战 

③ 多人网络对战(可跨不同系统)

④ 对战计时

⑤ 悔棋（可多步）

⑥ 下棋轨迹

⑦ 关于作品信息

<br>

# 运行演示：

<font color=#70AD47 size=4 face="幼圆">**视频演示：**</font> 

[ChinessChess 基于QT的跨平台网络象棋对战演示](https://www.bilibili.com/video/av45509758)

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

## 更新(2022.01.01 v6.0)

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

<img src="https://cdn.jsdelivr.net/gh/xmuli/xmuliPic@pic/2021/20211229011429.png" width="90%"/>

<br>

## 开发教程：

- [项目实战：Qt5／C++：QT象棋【初版】](https://blog.csdn.net/qq_33154343/article/details/80931400) 

- [QT5/C++项目：基于QT的跨平台网络对战象棋（一）](https://blog.csdn.net/qq_33154343/article/details/89284983)

- [QT5/C++项目：基于QT的跨平台网络对战象棋（二）](https://blog.csdn.net/qq_33154343/article/details/89285968)

- [QT5/C++项目：基于QT的跨平台网络对战象棋（三）](https://blog.csdn.net/qq_33154343/article/details/89286553)

<br>

## 依赖：

### 运行

- libqt5multimedia5

### 构建

- git
- make
- g++
- qtbase5-dev
- qtchooser
- qt5-qmake
- qtbase5-dev-tools
- qtmultimedia5-dev

## 构建：

1. 安装 Qt （Qt >= 5.9.0）和其他依赖

   以 Debian 和 Ubuntu 为例，执行:
   
   ```bash
   $ sudo apt install -y git make g++ qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools qtmultimedia5-dev
   ```
   
2. 运行命令:

   ```bash
   $ git clone https://github.com/XMuli/chinessChess.git
   $ cd chinessChess
   $ qmake
   $ make
   $ ./ChineseChess
   ```


或者，你可以跳过第 2 步，直接使用 Qt Creator 进行编译和运行。

<br>

## 贡献者：

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
     </tr>
  </thead>
</table>


<br>

若是帮助到了你，<font color=#FE7207  size=4 face="幼圆">可以点击该项目的的<img src="https://raw.githubusercontent.com/touwoyimuli/FigureBed/master/project_log/20190709023321.png" height="18" width="18"/>   **Star** 和<img src="https://raw.githubusercontent.com/touwoyimuli/FigureBed/master/project_log/20190709023317.png" height="18" width="18"/>  **Fork** 的两个图标，方便抬手之间，相当点个赞，</font>手有余香；其次才是一份冰的快乐水。

<br>

## 作者：

<font color=#70AD47 size=4 face="幼圆">**偕臧 (XMuli)：** </font> [https://ifmet.cn](https://ifmet.cn)

<br>

## 协议：

该项目基于 `GNU General Public License v3.0` 协议进行分发和使用。 有关更多信息，请参阅[协议文件](/LICENSE)。
