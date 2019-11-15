#ifndef CHESSPIECES_H
#define CHESSPIECES_H
#include <QString>


class ChessPieces
{
public:
    ChessPieces();
    ~ChessPieces();


public:
    QString getText();  //根据enum  TYPE得类型决定棋子上面的汉字
    void initialize(int id);  //32个棋子的初始化

public:
    enum TYPE{JIANG, SHI, XIANG, MA, CHE, PAO, BING };
    int _row;  //棋子在棋盘的行(不是界面的坐标)
    int _col;  //棋子在棋盘的列(不是界面的坐标)
    int _id;  //棋子的ID
    bool _deal;  //棋子是否死亡
    bool _red;  //棋子的颜色
    TYPE _type;  //棋子的类型

};

#endif // CHESSPIECES_H
