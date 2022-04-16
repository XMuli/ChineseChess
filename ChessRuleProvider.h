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
    std::vector<ChessState> getAllPossibleChildState(ChessState* state);
    bool isGameEnd(ChessState* state);
    bool whoWins(ChessState* state);
};

#endif // CHESSRULEPROVIDER_H
