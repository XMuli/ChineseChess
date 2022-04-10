#ifndef CHESSSTATE_H
#define CHESSSTATE_H

#include <vector>
#include <ChessPieces.h>

class ChessState
{
public:
    ChessState() = default;
    ChessState(std::vector<ChessPieces> pieces):chessPieces(pieces){}
    ChessState(ChessPieces pieces[]);

    ChessState suggestedNextState();
    bool hasNext();
    void playout();
    bool result();
    std::vector<ChessState> getAllPossibleNextState();

private:
    //all chess pieces, contains position infos
    std::vector<ChessPieces> chessPieces;
};

#endif // CHESSSTATE_H
