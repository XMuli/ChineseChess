#include "ChessRuleProvider.h"
#include "ChessStep.h"
#include "Rule.h"


using namespace rule;

std::vector<ChessState> ChessRuleProvider::getAllPossibleChildState(ChessState* state){
    std::vector<ChessStep> stepsToMove;
    // for all the pieces in current state that is moveable, generate it's possible steps
    for(auto const &pieces:state->getChessPieces()){
        if(pieces.isRed == state->currentTurn){
            auto const &stepsForPiece = rule::getSteps(pieces,state);
            stepsToMove.insert(stepsToMove.end(),stepsForPiece.begin(),stepsForPiece.end());
        }
    }

    // generate state for all possible steps
    std::vector<ChessState> states;
    for(auto const &step:stepsToMove){
        auto const &stateForStep = rule::getStates(step,state);
        states.insert(states.end(),stateForStep.begin(),stateForStep.end());
    }

    return states;
}

bool ChessRuleProvider::isGameEnd(ChessState* state){
    return true;
}

bool ChessRuleProvider:: whoWins(ChessState* state){
    return true;
}


