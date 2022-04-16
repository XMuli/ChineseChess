#include "ChessState.h"
#include "ChessStep.h"
#include "ChessRuleProvider.h"
#include <random>
#include "myLog.h"

#define VALUE_MAX 10000

using namespace std;



// Core funciton
std::vector<ChessState> ChessState::getAllPossibleNextState(){
    std::vector<ChessState> res;
    return res;
}

bool ChessState::playoutUntilEnd(){
    //TODO
    return true;
}

//----------------------------------------------------------------------helpers
ChessPiece ChessState::getPiece(int id){
    for(auto& p:chessPieces){
        if (p.id == id){
            return p;
        }
    }
    throw "exception";
}

ChessPiece* ChessState::getPieceByPos(int row,int col){
    for(auto& p:chessPieces){
        if (p.row == row && p.col == col){
            return &p;
        }
    }
    return nullptr;
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
        if(value(a) > max){
            res = a;
        }
    }
    return res;
}

int ChessState::value(ChessState const &state){
    return 0;
}
