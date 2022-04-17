#include "ChessState.h"
#include "ChessStep.h"
#include "ChessRuleProvider.h"
#include <random>
#include "myLog.h"
#include "Rule.h"
#define VALUE_MAX 50000

using namespace std;
using namespace rule;


// Core funciton
std::vector<ChessState> ChessState::getAllPossibleNextState(){
    auto states = ruler.getAllPossibleChildState(this);

//    std::cout<<"============================================\n";
//    this->print();
//    std::cout<<"Children\n";
//    for(auto& s:states){
//        s.print();
//    }
//    std::cout<<"============================================\n";
    return states;
}

bool ChessState::playoutUntilEnd(){
    auto best = *this;

    int played = 0;

//    best.print();
//    std::cout<<"find best start========================== the above is parent state"<<std::endl;
    while(!this->ruler.isGameEnd(&best)){

        best = best.getBestChild();
//        best.print();
//        std::cout<<played<<"th iteration done"<<std::endl;

        if(played >= 5){
            return rule::whoHasBetterChanceToWin(&best);
        }
        played++;
    }

    return ruler.whoWins(&best);
}

ChessState ChessState::getBestChild(){
    auto children = getAllPossibleNextState();
    int max = -VALUE_MAX;
    ChessState best = children.at(0);

    for(auto& child: children){
        if(child.value() > max){
            best = child;
            max = child.value();
        }
    }

    return best;
}

int ChessState::value(){
    if(this->cachedValue != 1){
        return cachedValue;
    }
    // maxmize value for parent
    bool maxMizeValueFor = !this->currentTurn;

    int res = 0;
    for(auto& p:this->chessPieces){
        if(p.isDead){
            continue;
        }
        if(p.isRed == maxMizeValueFor){
            res += p.value();
        }else{
            res -= p.value();
        }
    }
    cachedValue = res;

    return cachedValue;
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
    string s = this->currentTurn?"RED turn  ":"BLACK turn  ";
    s +="value = ";
    s += std::to_string(this->value());
    s +=" ";
    for(auto& p:chessPieces){
        s+=p.toString();
        s+=",";
    }

     std::cout<<s<< std::endl;
}

void ChessState::move(ChessStep const &step){
    for(auto& p:chessPieces){
        if (p.id == step.moveId){
            if(p.row!=step.fromRow || p.col!=step.fromCol){
                throw "step contains wrong info";
            }
            p.row = step.toRow;
            p.col = step.toCol;
            if(step.killId == -1){
                break;
            }
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


