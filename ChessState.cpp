#include "ChessState.h"
#include "ChessStep.h"
#include "ChessRuleProvider.h"
#include <random>
#include "myLog.h"

using namespace std;
namespace ChessStateHelper {
    void move(ChessPiece &piece,ChessStep step){
        piece.m_nRow = step.m_nRowTo;
        piece.m_nCol = step.m_nColTo;
    }

    int random(int min, int max) //range : [min, max]
    {
       static bool first = true;
       if (first)
       {
          srand( time(NULL) ); //seeding for the first time only!
          first = false;
       }
       return min + rand() % (( max + 1 ) - min);
    }

    // generate a vector of possible chess steps
    std::vector<ChessStep> generateSteps(std::vector<ChessPiece> pieces){

        ChessRuleProvider chessRuleProvider(pieces);
        QVector<ChessStep> qsteps;
        chessRuleProvider.getAllPossibleSteps(qsteps);

        return qsteps.toStdVector();
    }

    ChessState generateStateFromMove(ChessState* state,ChessStep step){
        std::vector<ChessPiece> oldPieces = state->getChessPieces();
        std::vector<ChessPiece> newPieces;
        for(ChessPiece & oldPiece:oldPieces){
            ChessPiece newpiece = oldPiece;
            if(newpiece.m_nID == step.m_nMoveID){
                ChessStateHelper::move(newpiece,step);
            }
            if(newpiece.m_nID == step.m_nKillID){
                newpiece.m_bDead = true;
            }
            newPieces.push_back(newpiece);
        }
        return ChessState(newPieces,!state->currentTurn);
    }

    int value(ChessState state){
        //evaluate state
        return 0;
    }
}

ChessState::ChessState(ChessPiece pieces[],bool currentTurn){
    for(int i = 0; i<32 ;i++){
        this->chessPieces.push_back(pieces[i]);
    }
    this->currentTurn = currentTurn;
}

ChessState::ChessState(vector<ChessPiece> pieces,bool currentTurn){
    for(auto &pieces: pieces){
        this->chessPieces.push_back(pieces);
    }
    this->currentTurn = currentTurn;
}


ChessState ChessState::suggestedNextState(){
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

std::vector<ChessState> ChessState::getAllPossibleNextState(){
    std::vector<ChessState> allPossibleState;

    // for all chess pieces, find it's possible move, for each possible move generate a state
    std::vector<ChessStep> steps = ChessStateHelper::generateSteps(this->chessPieces);
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
