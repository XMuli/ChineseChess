#ifndef CHESSSTATE_H
#define CHESSSTATE_H

#include <vector>
#include <ChessPieces.h>
#include "ChessState.fwd.h"
#include "ChessRuleProvider.h"
#include "ChessStep.h"
#include <iostream>
#define BLACK false
#define RED true
#define _UNCACHED 1;


class ChessState
{
public:
    bool currentTurn = BLACK;

    ChessState() = default;
    ChessState(std::vector<ChessPiece> pieces,bool currentTurn = BLACK);
    ChessState(ChessPiece pieces[],bool currentTurn = BLACK);
    std::vector<ChessPiece> getChessPieces(){
        return this->chessPieces;
    }
    ChessPiece getPieceById(int id);
    ChessPiece* getPieceByPos(int row,int col);
    void move(ChessStep const &step);
    void print();
    int value();

    bool playoutUntilEnd();
    std::vector<ChessState> getAllPossibleNextState();
    ChessState getBestChild();

private:
    int cachedValue = 1;
    //all chess pieces, contains position infos
    std::vector<ChessPiece> chessPieces;
    ChessRuleProvider ruler;

};

#endif // CHESSSTATE_H
