#include "ChessState.h"
#include "ChessStep.h"
#include "ChessRuleProvider.h"
#include <random>
#include "myLog.h"

#define VALUE_MAX 10000

using namespace std;



std::vector<ChessState> ChessState::getAllPossibleNextState(){
    std::vector<ChessState> allPossibleState;

    // for all chess pieces, find it's possible move, for each possible move generate a state
    std::vector<ChessStep> steps = ChessStateHelper::generateSteps(this->chessPieces,this->currentTurn);
    for(ChessStep &step:steps){
        ChessState newState = ChessStateHelper::generateStateFromMove(this,step);
        allPossibleState.push_back(newState);
    }

    return allPossibleState;
}

bool ChessState::playoutUntilEnd(){
    ChessState playoutState(this->chessPieces);
    ChessRuleProvider ruler(this->chessPieces);

    while (!ruler.isGameEnd()) {
        myLog::print("playing out ");
        playoutState = playoutState.suggestedNextState();
    }

    ChessRuleProvider newRuler(playoutState.chessPieces);
    return ruler.whoWins();
}


// ---------------------------------------------------------------------constrctor

ChessState::ChessState(ChessPiece pieces[],bool currentTurn){
    for(int i = 0; i<32 ;i++){
        this->chessPieces.push_back(pieces[i]);
    }
    this->currentTurn = currentTurn;
}

ChessState::ChessState(vector<ChessPiece> pieces,bool currentTurn){
    for(auto &piece: pieces){
        this->chessPieces.push_back(piece);
    }
    this->currentTurn = currentTurn;
}

//------------------------------------------------------------------------- private methods
ChessState ChessState::suggestedNextState(){
    // randomly for now
    int max = -1;
    ChessState res;
    vector<ChessState> childrenStates = getAllPossibleNextState();

    foreach (auto& a, childrenStates) {
        if(ChessStateHelper::value(a) > max){
            res = a;
        }
    }
    return res;
}
