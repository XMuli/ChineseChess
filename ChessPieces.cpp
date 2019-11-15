#include "ChessPieces.h"



struct POS
{
    int row; //行
    int col; //列
    ChessPieces::TYPE type;

};

POS pos[16] = {        //给void ChessPieces::initialize(int id)使用
    {0, 0, ChessPieces::CHE},
    {0, 1, ChessPieces::MA},
    {0, 2, ChessPieces::XIANG},
    {0, 3, ChessPieces::SHI},
    {0, 4, ChessPieces::JIANG},
    {0, 5, ChessPieces::SHI},
    {0, 6, ChessPieces::XIANG},
    {0, 7, ChessPieces::MA},
    {0, 8, ChessPieces::CHE},

    {2, 1, ChessPieces::PAO},
    {2, 7, ChessPieces::PAO},
    {3, 0, ChessPieces::BING},
    {3, 2, ChessPieces::BING},
    {3, 4, ChessPieces::BING},
    {3, 6, ChessPieces::BING},
    {3, 8, ChessPieces::BING},
};



ChessPieces::ChessPieces()
{

}

ChessPieces::~ChessPieces()
{

}


//根据enum TYPE得类型决定棋子上面的汉字
QString ChessPieces::getText()
{
    //enum TYPE{JIANG, SHI, XIANG, MA, CHE, PAO, BING };
    switch (_type)
    {
    case JIANG:
        return "将";
    case SHI:
        return "士";
    case XIANG:
        return "相";
    case MA:
        return "马";
    case CHE:
        return "车";
    case PAO:
        return "炮";
    case BING:
        return "兵";
    }
    return "ERROR";
}


//32个棋子的初始化
void ChessPieces::initialize(int id)
{
    _id = id;
    _deal = false;

    if(id < 16)
    {
       _red = true;  //红色棋子
       _row = pos[id].row;
       _col = pos[id].col;
       _type = pos[id].type;
    }
    else
    {
        _red = false;  //黑色棋子
        _row = 9 - pos[id-16].row;
        _col = 8 - pos[id-16].col;
        _type = pos[id-16].type;
    }
}



