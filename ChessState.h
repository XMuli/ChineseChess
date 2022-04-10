#ifndef CHESSSTATE_H
#define CHESSSTATE_H

#include <vector>
#include <ChessPieces.h>

class ChessState
{
public:
    ChessState();

    ChessState suggestedNextState(){
        return ChessState();
    }
    bool hasNext(){
        return true;
    }
    void playout(){}
    bool result(){return true;}
    vector<ChessState> getAllPossibleNextState(){
        vector<ChessState> v;
        return v;
    }

private:
    //all chess pieces, contains position infos
    ChessPieces m_ChessPieces[32];
};

#endif // CHESSSTATE_H
