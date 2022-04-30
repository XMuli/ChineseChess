# ChinessChess

<div align=center>
<img src="https://cdn.jsdelivr.net/gh/xmuli/xmuliPic@pic/2021/logo.svg" height="240" width="240" />
</div>


<br>

## Introduction:

<p align="right"><br><a href="README.md">English</a> | <a href="README.zh_CN.md">简体中文</a></p>

![](https://img.shields.io/github/license/XMuli/chinessChess) ![](https://img.shields.io/github/v/release/XMuli/chinessChess?style=flat&color=birightgreen) ![](https://img.shields.io/badge/powered%20by-XMuli-ff69b4)  ![](https://img.shields.io/github/stars/XMuli/chinessChess?style=social) ![](https://img.shields.io/github/forks/XMuli/chinessChess?style=social&label=Fork)

![](https://img.shields.io/github/workflow/status/XMuli/chinessChess/Windows?style=flat&logo=windows) ![](https://img.shields.io/github/workflow/status/XMuli/chinessChess/MacOS?style=flat&logo=apple) ![](https://img.shields.io/github/workflow/status/XMuli/chinessChess/Ubuntu?style=flat&logo=linux) ![](https://img.shields.io/github/languages/code-size/XMuli/chinessChess)  ![](https://img.shields.io/github/downloads/XMuli/chinessChess/total)

<br>

> The Chinese chess online battle platform (including communication function) developed based on `Qt5` realizes the function of chess game in a single or networked state, no matter whether it is single or multiple players, regardless of whether the system is the same.

<br>

## characteristic:

**The main functional modules of the project are divided into:**

① Players play against themselves

② Play against the computer AI

③ Multiplayer network battle (can cross different systems)

④ Battle timing

⑤ Repent (multiple moves possible)

⑥ track of chess moves

⑦ About the work information

<br>

# Run the demo:

<font color=#70AD47 size=4 face="幼圆">**Video presentation:**</font> 
[ChinessChess QT-based cross-platform online chess game demonstration](https://www.bilibili.com/video/av45509758)

<br>

<font color=#D0087E size=4 face="幼圆">**Win10 running example:**</font>

<img src="https://cdn.jsdelivr.net/gh/xmuli/xmuliPic@pic/2021/20190709004321.gif"  height="500" width="800">

<br>

<font color=#D0087E size=4 face="幼圆">**Linux running example:**</font>

<img src="https://cdn.jsdelivr.net/gh/xmuli/xmuliPic@pic/2021/20190709004216.gif"  height="500" width="800">

<br>

<font color=#D0087E size=4 face="幼圆">**MacOS running example:**</font>

<img src="https://cdn.jsdelivr.net/gh/xmuli/xmuliPic@pic/2021/20190709004745.gif"  height="500" width="800">

<br>

<font color=#70AD47 size=4 face="幼圆">**Examples of cross-platform battles:**</font>   **MacOS 10.14  vs  Win10**

<img src="https://cdn.jsdelivr.net/gh/xmuli/xmuliPic@pic/2021/20190709004454.gif"  height="500" width="800">

<br>

<font color=#FE7207  size=4 face="幼圆">**About the program:** </font> 

 <img src="https://cdn.jsdelivr.net/gh/xmuli/xmuliPic@pic/2021/about.png" width="100%"/>

<br>

## Update (2022.01.01)

### Features  v6.0

- Add regret function, unlimited regret
- Show move track, current move
- Restart game, click to restart
- Code logic optimization, new comments
- Update chess interface, use ancient chess characters
- Update about program, add contributor name
- Linux ARM Raspberry Pi support: [apt.raspbian-addons.org](https://apt.raspbian-addons.org/debian/pool/main/c/chinesechess/), both 32 and 64-bit

<br>

### Show

<img src="https://cdn.jsdelivr.net/gh/xmuli/xmuliPic@pic/2021/ChineChess.gif" width="90%"/>

<img src="https://cdn.jsdelivr.net/gh/xmuli/xmuliPic@pic/2021/20211229011429.png" width="90%"/>

<br>

## Development tutorial：

- [Project actual combat: Qt5/C++: QT chess [Basic version]](https://blog.csdn.net/qq_33154343/article/details/80931400) 

- [QT5/C++ project: QT-based cross-platform online battle chess (1)](https://blog.csdn.net/qq_33154343/article/details/89284983)

- [QT5/C++ project: QT-based cross-platform online battle chess (2)](https://blog.csdn.net/qq_33154343/article/details/89285968)

- [QT5/C++ project: QT-based cross-platform online battle chess (3)](https://blog.csdn.net/qq_33154343/article/details/89286553)

<br>

In addition, the source code summary is accompanied by detailed code comments for easy understanding.

<br>

## Dependencies:

### Runtime

- libqt5multimedia5

## Build:

1. Install Qt （Qt >= 5.9.0）and other dependencies 
   
   For Debian and Ubuntu, run:
   
   ```bash
   $ sudo apt install -y git make g++ qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools qtmultimedia5-dev
   ```
   
2. Run the command::

   ```bash
   $ git clone https://github.com/XMuli/chinessChess.git
   $ cd chinessChess
   $ qmake
   $ make
   $ ./ChineseChess
   ```


Or you can skip the second step and use Qt Creator to compile and run.

<br>

## Contributor:

Thanks for the contributions submitted by the friends 🥳🥳:

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

If it helped you, <font color=#FE7207 size=4 face="幼圆"> can click on the project’s  <img src="https://raw.githubusercontent.com/touwoyimuli/FigureBed/master/project_log/20190709023321.png" height="18" width="18"/>  **Star** and <img src="https://raw.githubusercontent.com/touwoyimuli/FigureBed/master/project_log/20190709023317.png" height ="18" width="18"/> **Fork**’s two icons are convenient for raising your hands. It’s quite a thumbs-up.</font> There is a fragrance in your hand；The next best thing is to buy me a cold Coke.

<br>

## Author:

<font color=#70AD47 size=4 face="幼圆">**偕臧 (XMuli)：** </font> [https://ifmet.cn](https://ifmet.cn)

<br>

## License：

This project is distributed and used based on the `GNU General Public License v3.0` protocol. For more information, please refer to [Agreement File](/LICENSE).

