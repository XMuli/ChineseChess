# Qt_ChinessChess



![](https://raw.githubusercontent.com/touwoyimuli/FigureBed/master/log/20190708214213.png)

## 项目介绍：

个人大学毕业设计，基于Qt5开发的中国象棋网络对战平台(含通讯功能)

该项目主要功能模块分为①玩家与自己对战、②玩家与电脑AI对战、③多人网络对战(可跨系统)、④对战计时、⑤关于作品信息。实现了在单机或联网状态下，无论是单人还是多人，无论使用系统是否相同，均可以实现象棋游戏功能。



<font color=#70AD47 size=4 face="幼圆">**编码语言：**</font>![](https://img.shields.io/badge/language-c++-orange.svg)

<font color=#70AD47 size=4 face="幼圆">**代码大小：**</font>![](https://img.shields.io/github/languages/code-size/touwoyimuli/2019_01_Qt5_ChinessChess.svg?logo=chess)

<font color=#70AD47 size=4 face="幼圆">**项目进度：**</font>![](http://progressed.io/bar/100?title=completed)

<font color=#70AD47 size=4 face="幼圆">**总下载量：**</font>![](https://img.shields.io/github/downloads/touwoyimuli/2019_01_Qt5_ChinessChess/total.svg)

<font color=#70AD47 size=4 face="幼圆">**项目编译：**</font>[![](https://travis-ci.org/Alamofire/Alamofire.svg?branch=master)](https://travis-ci.org/Alamofire/Alamofire)

<font color=#70AD47 size=4 face="幼圆">**支持平台：**</font>![](https://img.shields.io/conda/pn/conda-forge/qt.svg)

<br>

## 项目运行演示：

<font color=#70AD47 size=4 face="幼圆">**视频演示：**</font> [2019_01_Qt5_ChinessChess 基于QT的跨平台网络象棋对战演示](https://www.bilibili.com/video/av45509758)

<br>

<font color=#D0087E size=4 face="幼圆">**win10系统演示：**</font>

<img src="https://raw.githubusercontent.com/touwoyimuli/FigureBed/master/project_log/20190709004321.gif"  height="500" width="800">

<br>

<font color=#D0087E size=4 face="幼圆">**Linux系统演示：**</font>

<img src="https://raw.githubusercontent.com/touwoyimuli/FigureBed/master/project_log/20190709004216.gif"  height="500" width="800">

<br>

**<font color=#D0087E size=4 face="幼圆">MacOS系统演示：**</font>

<img src="https://raw.githubusercontent.com/touwoyimuli/FigureBed/master/project_log/20190709004745.gif"  height="500" width="800">

<br>

<font color=#70AD47 size=4 face="幼圆">**跨平台对战演示：**</font>   **MacOS 10.14  vs  Win10**

<img src="https://raw.githubusercontent.com/touwoyimuli/FigureBed/master/project_log/20190709004454.gif"  height="500" width="800">

<br>

<font color=#FE7207  size=4 face="幼圆">**作者作品详情：**   </font>

<img src="https://raw.githubusercontent.com/touwoyimuli/FigureBed/master/project_log/20190709004107.png"  height="500" width="800">

<br>

<br>

## 相关文章链接：

[QT5/C++项目：基于QT的跨平台网络对战象棋（一）](https://blog.csdn.net/qq_33154343/article/details/89284983)

[QT5/C++项目：基于QT的跨平台网络对战象棋（二）](https://blog.csdn.net/qq_33154343/article/details/89285968)

[QT5/C++项目：基于QT的跨平台网络对战象棋（三）](https://blog.csdn.net/qq_33154343/article/details/89286553)

<br><br>

## 历史版本：

<font color=#70AD47 size=5 face="幼圆">历史版本:</font>

<font color=#70AD47 size=4 face="幼圆">**旧版本:**</font>![](https://img.shields.io/badge/v-1.1-brightgreen.svg)
1.1版本，创建一个空的widget的中国象棋项目

<font color=#70AD47 size=4 face="幼圆">**旧版本:**</font>![](https://img.shields.io/badge/v-1.2-brightgreen.svg)

1.2版本，新增加了单人单机中国象棋对战模式
完成了中国象棋项目功能如下:
1、棋盘和棋子的绘画
2、每一种棋子的规则走法确定
3、实现了一台电脑一个人同时控制两方象棋的进行游戏

<font color=#70AD47 size=4 face="幼圆">**旧版本:**</font>![](https://img.shields.io/badge/v-2.1-brightgreen.svg)

2.1版本命名按照google谷歌编程规范命名 ，且略微重构了一番

<font color=#70AD47 size=4 face="幼圆">**旧版本:**</font>![](https://img.shields.io/badge/v-3.1-brightgreen.svg)

3.1版本，新增加人机对战模式。可以实现电脑和玩家对战
 但是人工智能略有缺陷： (不影响使用，后续全部完成了再继续优化)
（1）电脑过于弱智，只能看一步的局面分。
（2）由于设计的人工智能步骤，电脑是依靠杀死玩家的棋子，来进行下一步的，若是无棋可杀，程序则会自动结束（算是一个崩溃吧，在5.3版本已经修复）

<font color=#70AD47 size=4 face="幼圆">**旧版本:**</font>![](https://img.shields.io/badge/v-4.1-brightgreen.svg)

4.1版本，新增游戏模式，在局域网下，双人同时不同台PC进行对战游戏

<font color=#70AD47 size=4 face="幼圆">**旧版本:**</font>![](https://img.shields.io/badge/v-5.1-brightgreen.svg)

5.1版本，基本所有的功能都已经实现，且整合。余下的就是一些需要完善的一些地方

<font color=#70AD47 size=4 face="幼圆">**旧版本:**</font>![](https://img.shields.io/badge/v-5.2-brightgreen.svg)

5.2版本，添加了关于作者相关信息

<font color=#70AD47 size=4 face="幼圆">**旧版本:**</font>![](https://img.shields.io/badge/v-5.3-brightgreen.svg)

5.3版本。基本无需修改，但是遗漏了自定义的一个login图标，关于运行程序的图标。

<font color=#70AD47 size=4 face="幼圆">**旧版本:**</font>![](https://img.shields.io/badge/v-5.5-brightgreen.svg)

5.5版本。当前最终发布版本。

若需要下载最终的一份源码学习，下载最终的ChineseChess_05_05.zip版本即可以。

<br>

## 说明：

发开编程环境[qt-opensource-windows-x86-5.9.7.exe](http://download.qt.io/archive/qt/5.9/5.9.7/)。 如若下载的项目编译运行失败，请使用下载**这一版本**5.9.7的QtCreator编译运行项目  （使用Desktop Qt 5.9.7 MinGW 32 bit 直接编译运行）（理论5.9.4及以上的版本均可打开编译运行）

<br>

## 捐赠

若是帮助到了你，可以点击该项目的的<img src="https://raw.githubusercontent.com/touwoyimuli/FigureBed/master/project_log/20190709023321.png" height="18" width="18"/>   **Star** 和<img src="https://raw.githubusercontent.com/touwoyimuli/FigureBed/master/project_log/20190709023317.png" height="18" width="18"/>  **Fork** 的两个图标，方便抬手之间，表示点个赞，手有余香
<img  src="https://raw.githubusercontent.com/touwoyimuli/FigureBed/master/project_log/20190709003145.jpg" height="205" width="400" align=center/>

<br>

## 关于作者：

<font color=#70AD47 size=4 face="幼圆">**touwoyimuli：** </font> touwoyimuli@gmai.com         [作者更多联系方式](https://touwoyimuli.github.io/about/)

