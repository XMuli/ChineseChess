#ifndef CHESSSTATE_H
#define CHESSSTATE_H

#include <vector>
#include <ChessPieces.h>

class ChessState
{
public:
    ChessState() = default;
    ChessState(std::vector<ChessPieces> pieces):chessPieces(pieces){}

    ChessState suggestedNextState(){
        return ChessState();
    }
    bool hasNext(){
        return true;
    }
    void playout(){}
    bool result(){return true;}
    std::vector<ChessState> getAllPossibleNextState(){
        std::vector<ChessState> v;
        return v;
    }

private:
    //all chess pieces, contains position infos
    std::vector<ChessPieces> chessPieces;
};

#endif // CHESSSTATE_H
