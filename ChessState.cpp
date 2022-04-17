#include "ChessState.h"
#include "ChessStep.h"
#include "ChessRuleProvider.h"
#include <random>
#include "myLog.h"

#define VALUE_MAX 10000

using namespace std;



// Core funciton
std::vector<ChessState> ChessState::getAllPossibleNextState(){
    ChessRuleProvider ruler;
    return ruler.getAllPossibleChildState(this);;
}

bool ChessState::playoutUntilEnd(){
    //TODO
    return true;
}

//----------------------------------------------------------------------helpers
ChessPiece ChessState::getPieceById(int id){
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
void ChessState::print(){
    for(auto& p:chessPieces){
        std::cout<< p.type <<" is at "<<p.row<<":"<<p.col << std::endl;
    }

     std::cout<<"================================== "<< std::endl;
}

void ChessState::move(ChessStep const &step){
    for(auto& p:chessPieces){
        if (p.id == step.moveId){
            if(p.row!=step.fromRow || p.col!=step.fromCol){
                throw "step contains wrong info";
            }
            p.row = step.toRow;
            p.col = step.toCol;
        }
        if(p.id == step.killId){
            if(p.row!=step.toRow || p.col!=step.toCol){
                throw "step contains wrong info";
            }
            p.isDead = true;
        }
    }
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
