#include "ChessState.h"
#include "ChessStep.h"
#include "ChessRuleProvider.h"
#include <random>
#include "myLog.h"
#include "Rule.h"
#include <algorithm>
#include "Config.h"
#define VALUE_MAX 50000

using namespace std;
using namespace rule;


// Core funciton
std::vector<ChessState> ChessState::getGoodPossibleNextStates(){
    auto states = ruler.getAllPossibleChildState(this);


    sort(states.begin(),states.end(),[](ChessState& a, ChessState& b){
        return a.value() > b.value();
    });

    states.resize((int)(states.size()*Config::proportion_of_child_to_expand));

    return states;
}

bool ChessState::playoutUntilEnd(){
    auto best = *this;

    int played = 0;


    while(!this->ruler.isGameEnd(&best)){

        best = best.getBestChild();

        if(played >= Config::Max_playout_depth){
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

// value such that maximize parent's advantage
int ChessState::value(){
    if(this->cachedValue != 1){
        return cachedValue;
    }
    // maxmize value for parent

    int res = 0;
    for(auto& p:this->chessPieces){
        if(p.isRed == !this->currentTurn){
            res += p.value();
        }else{
            res -= p.value();
        }
    }

    cachedValue = res;

    return cachedValue;
}

// value fpr a certain step in current state
int ChessState::stepValue(ChessStep &step){
    int res = -value();

    if(step.killId != -1){
        res += this->getPieceById(step.killId).value()*Config::kill_reward_scalar;
    }

    auto p = this->getPieceById(step.moveId);
    if(p.type == ChessPiece::CHE){
        res += 10;
    }

    if(p.type == ChessPiece::MA){
        res += 9;
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


