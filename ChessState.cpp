#include "ChessState.h"

ChessState ChessState::suggestedNextState(){

    return ChessState();
}


std::vector<ChessState> ChessState::getAllPossibleNextState(){
    std::vector<ChessState> v;
    return v;
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
