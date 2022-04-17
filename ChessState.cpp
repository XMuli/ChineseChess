#include "ChessState.h"
#include "ChessStep.h"
#include "ChessRuleProvider.h"
#include <random>
#include "myLog.h"

#define VALUE_MAX 10000

using namespace std;

namespace stateHelper {

}



// Core funciton
std::vector<ChessState> ChessState::getAllPossibleNextState(){
    return ruler.getAllPossibleChildState(this);
}

bool ChessState::playoutUntilEnd(){
    auto best = getBestChild();

    while(!this->ruler.isGameEnd(&best)){
        best = best.getBestChild();
    }

    return true;
}

ChessState ChessState::getBestChild(){
    auto children = getAllPossibleNextState();
    int max = -VALUE_MAX;
    ChessState best = children.at(0);

    for(auto& child: children){
        if(child.value() > max){
            best = child;
        }
    }

    return best;
}

int ChessState::value(){
    // maxmize value for parent
    return 0;
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


