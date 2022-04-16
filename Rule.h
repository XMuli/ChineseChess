#ifndef RULE_H
#define RULE_H

#include "ChessPieces.h"
#include "ChessStep.h"
#include "ChessState.h"

#include <vector>
//------------------------------ helpers
namespace rule {
    std::vector<ChessStep> generateUnblockingSteps(ChessPiece const &pieces,ChessState *state);

    std::vector<ChessStep> getSteps(ChessPiece const &pieces,ChessState *state){
        std::vector<ChessStep> result = generateUnblockingSteps(pieces,state);


        return result;
    }

    std::vector<ChessState> getStates(ChessStep const &step,ChessState *state){
        std::vector<ChessState> result;

        return result;
    }

    std::vector<ChessStep> generateUnblockingSteps(ChessPiece const &pieces,ChessState *state){
        std::vector<ChessStep> result;


        return result;
    }
}

#endif // RULE_H
