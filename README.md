# ChineseChess

<div align=center>
<img src="https://cdn.jsdelivr.net/gh/xmuli/xmuliPic@pic/2021/logo.svg" height="240" width="240" />
</div>


<br>

## Introduction

<p align="right"><br><a href="README.md">English</a> | <a href="README.zh_CN.md">简体中文</a></p>

![](https://img.shields.io/github/license/XMuli/chineseChess) ![](https://img.shields.io/github/v/release/XMuli/ChineseChess?style=flat&color=birightgreen)![](https://img.shields.io/badge/powered%20by-XMuli-ff69b4)![](https://img.shields.io/github/stars/XMuli/ChineseChess?style=social) ![](https://img.shields.io/github/forks/XMuli/ChineseChess?style=social&label=Fork)

[![macos-badge](https://github.com/xmuli/ChineseChess/workflows/MacOS/badge.svg)](https://github.com/xmuli/ChineseChess/workflows/MacOS/badge.svg)  [![win-badge](https://github.com/xmuli/ChineseChess/workflows/Windows/badge.svg)](https://github.com/xmuli/ChineseChess/workflows/Windows/badge.svg)  [![ubuntu-badge](https://github.com/xmuli/ChineseChess/workflows/Ubuntu/badge.svg)](https://github.com/xmuli/ChineseChess/workflows/Ubuntu/badge.svg)   ![](https://img.shields.io/github/languages/code-size/XMuli/ChineseChess)  ![](https://img.shields.io/github/downloads/XMuli/ChineseChess/total)


> - The Chinese chess online battle platform (including communication function) developed based on `Qt5.15 and Qt6.8` realizes the function of chess game in a single or networked state, no matter whether it is single or multiple players, regardless of whether the system is the same.
> - More project collections: https://product.xmuli.tech
> - Video Effects: https://www.bilibili.com/video/av45509758

<br>



## characteristic

**The main functional modules of the project are divided into:**

ⅰ Players play against themselves

ⅱ Play against the computer AI

ⅲ Multiplayer network battle (can cross different systems)

ⅳ Battle timing

ⅴ Repent (multiple moves possible)

ⅵ track of chess moves

ⅵ About the work information

<br>

# Run the demo

<font color=#70AD47 size=4 face="幼圆">**Video presentation:**</font> 
[ChineseChess QT-based cross-platform online chess game demonstration](https://www.bilibili.com/video/av45509758)

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

## Update (2022-2025 v7.x)

### Features

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

<img src="https://fastly.jsdelivr.net/gh/XMuli/xmuliPic@pic/2024/202401282117185.png" width="80%"/>

<br>

## Development tutorial

- [Project actual combat: Qt5/C++: QT chess [Basic version]](https://xmuli.blog.csdn.net//article/details/80931400) 

- [QT5/C++ project: QT-based cross-platform online battle chess (1)](https://xmuli.blog.csdn.net//article/details/89284983)

- [QT5/C++ project: QT-based cross-platform online battle chess (2)](https://xmuli.blog.csdn.net//article/details/89285968)

- [QT5/C++ project: QT-based cross-platform online battle chess (3)](https://xmuli.blog.csdn.net//article/details/89286553)

<br>

In addition, the source code summary is accompanied by detailed code comments for easy understanding.

<br>

## Build

> This project supports both Qt 5 and Qt 6 builds. 
>
> For more project list: https://product.xmuli.tech



- Environment: This project compiles successfully with both Qt 5.15.2 and 6.8.3 LTS versions. Tested minimum build version is Qt 5.12; lower versions are unverified.
- IDE: We recommend using Qt Creator directly to open CMakeLists.txt for building.
- Other: You may also convert CMake to .sln manually and build using Visual Studio 2022.



### Windows Build

1. Install Qt (recommended: Qt 5.15 or Qt 6.8 LTS)
2. Open CMakeLists.txt directly in the Qt Creator IDE
3. Click Build > Compile in the bottom-left corner
4. You should see it run successfully. Enjoy~



### Linux / Mac Build

1. Using Debian and Ubuntu as examples, install Qt (recommended: Qt 5.15 or Qt 6.8 LTS) Execute:

   ```bash
   $ sudo apt install cmake qtbase5-dev qt5-default libqt5svg5-dev qtmultimedia5-dev qttools5-dev libqt5x11extras5-dev
   ```

2. Run commands:

   ```bash
   $ git clone https://github.com/XMuli/ChineseChess.git
   $ cd ChineseChess
   $ mkdir build && cd build
   $ cmake ..
   $ make
   ```

3. Alternatively, you can skip Step 2 and directly use Qt Creator for compilation and execution, which is more convenient.


<br>

## Contributor

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
       <th align="center" style="width: 80px;">
        <a href="https://github.com/zjuyk">
          <img src="https://fastly.jsdelivr.net/gh/XMuli/xmuliPic@pic/2024/202401282118007.png" width="50px"><br>
          <sub>zjuyk</sub>
        </a>
     </tr>
  </thead>
</table>





If it helps you, or find it useful, <font color=#FE7207  size=4 face="幼圆">you can click on the item's <font color=#D0087E size=4 face="幼圆">**⭐Star** **🍴 Fork** </font> of the two icons, conveniently lift the hand between, said a point of praise the hand,</font> There is a fragrance in your hand；The next best thing is to buy me a cold Coke.

<br>

## Author

[![alt text](https://img.shields.io/badge/QQ-%E5%81%95%E8%87%A7-brightgreen)](https://sighttp.qq.com/authd?IDKEY=31f3ef7312b39e2c8dc822ae2f4c3b3118e1a6f31cc83373) [![alt text](https://img.shields.io/badge/GitHub-XMuli-brightgreen)](https://github.com/XMuli) [![alt text](https://img.shields.io/badge/Blog-%E5%81%95%E8%87%A7%E7%9A%84%E5%B0%8F%E7%AB%99-ff69b4)](https://ifmet.cn/) 

<br>

## Tutorial Series

[QtExamples](https://github.com/XMuli/QtExamples) Welcome to `star` ⭐ and `fork` 🍴 This series of `C++ / QT / DTK` studies, where you can learn how to write this kind of software yourself, is a complete series of tutorials. And **FREE**!

