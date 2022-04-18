#include "ChessState.h"
#include "ChessStep.h"
#include "ChessRuleProvider.h"
#include <random>
#include "myLog.h"
#include "Rule.h"
#include <algorithm>
#define VALUE_MAX 50000

using namespace std;
using namespace rule;


// Core funciton
std::vector<ChessState> ChessState::getGoodPossibleNextStates(){
    auto states = ruler.getAllPossibleChildState(this);


    sort(states.begin(),states.end(),[](ChessState& a, ChessState& b){
        return a.value() > b.value();
    });

    states.resize(states.size()/2);

    return states;
}

bool ChessState::playoutUntilEnd(){
    auto best = *this;

    int played = 0;


    while(!this->ruler.isGameEnd(&best)){

        best = best.getBestChild();

        if(played >= 15){
            return rule::whoHasBetterChanceToWin(&best);
        }
        played++;
    }

    return ruler.whoWins(&best);
}



ChessState ChessState::getBestChild(){
    auto steps = ruler.getAllValidSteps(this);

    auto best = steps.at(0);
    int bestValue = stepValue(best);
    for(auto &step:steps){
        auto value= stepValue(step);
        if(value > bestValue){
            best = step;
            bestValue = value;
        }
    }

    return ruler.getState(best,this);
}

int ChessState::value(){
    if(this->cachedValue != 1){
        return cachedValue;
    }
    // maxmize value for parent

    int res = 0;
    for(auto& p:this->chessPieces){
        if(p.isRed){
            res += p.value();
        }else{
            res -= p.value();
        }
    }

    if(this->currentTurn == BLACK){
        res = -res;
    }

    cachedValue = res;

    return cachedValue;
}

int ChessState::stepValue(ChessStep &step){
    int res = value();

    if(step.killId != -1){
        res += this->getPieceById(step.killId).value();
    }

    auto piece = getPieceById(step.moveId);
    if(piece.type == ChessPiece::CHE){
        res += 200;
    }

    if(piece.type == ChessPiece::MA){
        res += 100;
    }


    return res;
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


