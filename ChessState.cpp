#include "ChessState.h"
#include "ChessStep.h"
#include "ChessRuleProvider.h"

using namespace std;
namespace ChessStateHelper {
    void move(ChessPieces &piece,ChessStep step){
        piece.m_nRow = step.m_nRowTo;
        piece.m_nCol = step.m_nnColTo;
    }

    // generate a vector of possible chess steps
    std::vector<ChessStep> generateSteps(std::vector<ChessPieces> pieces){

        ChessRuleProvider chessRuleProvider(pieces);
        QVector<ChessStep> qsteps;
        chessRuleProvider.getAllPossibleSteps(qsteps);

        return qsteps.toStdVector();
    }

    ChessState generateStateFromMove(std::vector<ChessPieces> pieces,ChessStep step){
        std::vector<ChessPieces> newPieces;
        for(ChessPieces &pieces:pieces){
            ChessPieces newpiece = pieces;
            if(newpiece.m_nID == step.m_nMoveID){
                ChessStateHelper::move(newpiece,step);
            }
            if(newpiece.m_nID == step.m_nKillID){
                newpiece.m_bDead = true;
            }
            newPieces.push_back(newpiece);
        }
        return ChessState(newPieces);
    }

}

ChessState::ChessState(ChessPieces pieces[]){
    for(int i = 0; i<32 ;i++){
        this->chessPieces.push_back(pieces[i]);
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
