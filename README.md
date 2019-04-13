# Qt_ChinessChess

个人大学毕业设计，基于Qt开发的中国象棋网络对战平台(含通讯功能)



## 项目运行演示：
[![asciicast](https://blog.csdn.net/qq_33154343/article/details/89284983)](https://www.bilibili.com/video/av45509758)

![Image text](https://github.com/touwoyimuli/2019_01_Qt5_ChinessChess/blob/master/images/1.png)
![Image text](https://github.com/touwoyimuli/2019_01_Qt5_ChinessChess/blob/master/images/2.png)
![Image text](https://github.com/touwoyimuli/2019_01_Qt5_ChinessChess/blob/master/images/3.png)



## 相关文章链接：

[QT5/C++项目：基于QT的跨平台网络对战象棋（一）](https://blog.csdn.net/qq_33154343/article/details/89284983)

[QT5/C++项目：基于QT的跨平台网络对战象棋（二）](https://blog.csdn.net/qq_33154343/article/details/89285968)

[QT5/C++项目：基于QT的跨平台网络对战象棋（三）](https://blog.csdn.net/qq_33154343/article/details/89286553)



## 源码说明：

**ChineseChess_01_01.zip**
1.1版本，创建一个空的widget的中国象棋项目

**ChineseChess_01_02.zip**
1.2版本，新增加了单人单机中国象棋对战模式
完成了中国象棋项目功能如下:
1、棋盘和棋子的绘画
2、每一种棋子的规则走法确定
3、实现了一台电脑一个人同时控制两方象棋的进行游戏
优缺点:
1、代码稍有杂乱、其中棋子类ChessPieces.cpp中还可以运用少量的宏，用公有函数去调用是有函数， 提出更加合理的简单的代码优化、注释
2、其中运用到了"魔数"32，虽然项目里面数值很明显，但是应该用const 或者宏 替换出来，注意编程规范
3、代码写完，有空重构优化一下

**ChineseChess_02_01.zip**
2.1版本命名按照google谷歌编程规范命名 ，且略微重构了一番

**ChineseChess_03_01.zip**
3.1版本，新增加人机对战模式。可以实现电脑和玩家对战
 但是人工智能略有缺陷： (不影响使用，后续全部完成了再继续优化)
（1）电脑过于弱智，只能看一步的局面分。
（2）由于设计的人工智能步骤，电脑是依靠杀死玩家的棋子，来进行下一步的，若是无棋可杀，程序则会自动结束（算是一个崩溃吧，在5.3版本已经修复）

**ChineseChess_04_01.zip**
4.1版本，新增游戏模式，在局域网下，双人同时不同台PC进行对战游戏

**ChineseChess_05_01.zip**
5.1版本，基本所有的功能都已经实现，且整合。余下的就是一些需要完善的一些地方

**ChineseChess_05_02.zip**
5.2版本，添加了关于作者相关信息

**ChineseChess_05_03.zip**
5.3版本，且优化加强人机AI对战的算法，和修复之前遗留的小问题。

**ChineseChess_05_04.zip**
5.4版本。基本无需修改，但是遗漏了自定义的一个login图标，关于运行程序的图标。

**ChineseChess_05_05.zip**
5.5版本。最终发布版本。

若需要下载最终的一份源码学习，下载最终的ChineseChess_05_05.zip版本即可以。



## 关于作者：

|   **GitHub**    | **<https://github.com/touwoyimuli>**       |
| :-------------: | ------------------------------------------ |
|    **CSDN**     | **<https://blog.csdn.net/qq_33154343>**    |
|  **bilibili**   | **<https://space.bilibili.com/106940738>** |
|  **Telegram**   | **<https://t.me/touwoyimuli>**             |
|   **QQGmail**   | **252311126@qq.com**                       |
| **GoogleGmail** | **252311126aq@gmail.com**                  |



### 说明：且以上所有源码全带有详细注释。

发开编程环境qt-opensource-windows-x86-5.9.7.exe（附官网下载地址：http://download.qt.io/archive/qt/5.9/5.9.7/ ）如若下载的项目编译运行失败，请使用下载这一版本的QtCreator编译运行项目
