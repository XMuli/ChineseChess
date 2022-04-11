#ifndef CHESSRULEPROVIDER_H
#define CHESSRULEPROVIDER_H
#include "ChessPieces.h"
#include "ChessStep.h"
#include <vector>
#include "myLog.h"
#include "ChessState.h"
#define TOTALNUM 32

class ChessRuleProvider
{
public:
    ChessRuleProvider(std::vector<ChessPiece>& pieces):chessPieces(pieces){}
    void getAllPossibleSteps(std::vector<ChessStep>& steps,bool currentTurn);
    bool isGameEnd();
    bool whoWins();

private:
    std::vector<ChessPiece> chessPieces;
    std::vector<ChessPiece> getOneColorPiece(bool color);
    std::vector<ChessStep> getStepsForPiece(ChessPiece piece);





};

#endif // CHESSRULEPROVIDER_H
