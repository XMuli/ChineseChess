#ifndef CHESSRULEPROVIDER_H
#define CHESSRULEPROVIDER_H

#include "ChessStep.h"
#include <vector>
#include "ChessState.fwd.h"
#include "ChessRuleProvider.fwd.h"
#include "ChessPieces.h"
#define TOTALNUM 32

class ChessRuleProvider
{
public:
    ChessRuleProvider(){}
    std::vector<ChessState> getAllPossibleChildState(ChessState* state);
    bool isGameEnd(ChessState* state);
    bool whoWins(ChessState* state);

private:
    std::vector<ChessStep> getSteps(ChessPiece const &pieces,ChessState *state);
    std::vector<ChessState> getStates(ChessStep const &step,ChessState *state);

};

#endif // CHESSRULEPROVIDER_H
