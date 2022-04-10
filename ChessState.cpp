#include "ChessState.h"
#include "ChessStep.h"

using namespace std;
namespace ChessStateHelper {
    std::vector<ChessStep> generateSteps(std::vector<ChessPieces> pieces){
        vector<ChessStep> steps;
        for(auto& piece:pieces){
            // generate steps for this specific piece, under current suituation
        }

        return steps;
    }

    ChessState generateStateFromMove(std::vector<ChessPieces> pieces,ChessStep step){
        return ChessState();
    }
}

ChessState ChessState::suggestedNextState(){

    return ChessState();
}


std::vector<ChessState> ChessState::getAllPossibleNextState(){
    std::vector<ChessState> allPossibleState;

    // for all chess pieces, find it's possible move, for each possible move generate a state

    std::vector<ChessStep> steps = ChessStateHelper::generateSteps(this->chessPieces);
    for(ChessStep &step:steps){
        ChessState newState = ChessStateHelper::generateStateFromMove(this->chessPieces,step);
        allPossibleState.push_back(newState);
    }



    return allPossibleState;
}

bool ChessState::hasNext(){
    return true;
}
void ChessState::playout(){
    return;
}
bool ChessState::result(){
    return true;
}
