/*
 * Copyright (C)  2019~2020  偕臧  All rights reserved.
 *
 * Author:  xmuli(偕臧) xmulitech@gmail.com
 *
 * github:  https://github.com/xmuli
 * blogs:   https://ifmet.cn
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/gpl-3.0.html>.
 */
#ifndef CHESSPIECES_H
#define CHESSPIECES_H

#include <QString>
#include <string>
#include <map>

class ChessPiece
{
public:
    ChessPiece();
    ~ChessPiece();
    int value();

    void init(int id);  //初始化
    QString getnName(bool isRedSide);    //棋子对应的汉字

    enum CHESS_TYPE{JIANG, SHI, XIANG, MA, CHE, PAO, BING};

    std::map<ChessPiece::CHESS_TYPE,std::string> typeStrMap = {
        {ChessPiece::CHE,"CHE"},
        {ChessPiece::MA,"MA"},
        {ChessPiece::PAO,"PAO"},
        {ChessPiece::XIANG,"XIANG"},
        {ChessPiece::SHI,"SHI"},
        {ChessPiece::JIANG,"JIANG"},
        {ChessPiece::BING,"BING"},
    };

    int  row;   //行
    int  col;   //列
    int  id;    //ID号
    bool isDead;  //死亡状态
    bool isRed;   //是否是红方
    CHESS_TYPE type;  //具体哪一个棋子

    std::string toString(){
        std::string typeStr = typeStrMap.at(this->type);

        std::string res = (isRed?"Red ":"BLACK ");
        res += typeStr;
        res += " [" ;
        res += std::to_string(row) ;
        res +=":" + std::to_string(col) ;
        res +="]";
        res += isDead?"Dead":"Alive";

        return res;
    }
};

#endif // CHESSPIECES_H
