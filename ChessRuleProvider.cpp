#include "ChessRuleProvider.h"


std::vector<ChessState> ChessRuleProvider::getAllPossibleChildState(ChessState* state){
    std::vector<ChessPiece> toMoves;
    for(auto& pieces:state->getChessPieces()){
        if(pieces.m_bRed == state->currentTurn){
            toMoves.push_back(pieces);
        }
    }
}

bool ChessRuleProvider::isGameEnd(ChessState* state){

}

bool ChessRuleProvider:: whoWins(ChessState* state){

}

//------------------------------ helpers
namespace rule {

}
