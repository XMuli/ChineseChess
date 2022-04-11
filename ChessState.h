#ifndef CHESSSTATE_H
#define CHESSSTATE_H

#include <vector>
#include <ChessPieces.h>

#define BLACK false
#define RED true

class ChessState
{
public:
    ChessState() = default;
    ChessState(std::vector<ChessPiece> pieces,bool currentTurn = BLACK);
    ChessState(ChessPiece pieces[],bool currentTurn = BLACK);

    std::vector<ChessPiece> getChessPieces(){
        return this->chessPieces;
    }

    ChessState suggestedNextState();
    bool playoutUntilEnd();
    std::vector<ChessState> getAllPossibleNextState();
    bool currentTurn = BLACK;

private:
    //all chess pieces, contains position infos
    std::vector<ChessPiece> chessPieces;

};

#endif // CHESSSTATE_H
