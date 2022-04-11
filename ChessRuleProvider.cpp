#include "ChessRuleProvider.h"


void ChessRuleProvider::getAllPossibleSteps(std::vector<ChessStep>& steps,bool currentTurn){
    std::vector<ChessPiece> toMove= getOneColorPiece(currentTurn == RED?RED:BLACK);
    for (auto &piece : toMove) {
        std::vector<ChessStep> stepsForThisPiece = this->getStepsForPiece(piece);
        // add all steps for this pieces to steps for all pieces
        steps.insert(steps.end(),stepsForThisPiece.begin(),stepsForThisPiece.end());
    }
}

bool ChessRuleProvider::isGameEnd(){
    for(ChessPiece &p:chessPieces){
        if(p.m_emType == ChessPiece::JIANG && p.m_bDead){
            return true;
        }
    }
    return false;
}

bool ChessRuleProvider::whoWins(){
    for(ChessPiece &p:chessPieces){
        if(p.m_emType == ChessPiece::JIANG && p.m_bDead){
            return p.m_bRed?BLACK:RED;
        }
    }
    throw std::invalid_argument( "received negative value" );
    // should never get here
}
std::vector<ChessPiece> ChessRuleProvider::getOneColorPiece(bool color){
    std::vector<ChessPiece> res;
    for(ChessPiece &p:chessPieces){
        if(p.m_bRed == color){
            res.push_back(p);
        }
    }
    return res;
}
std::vector<ChessStep> ChessRuleProvider::getStepsForPiece(ChessPiece piece){
    std::vector<ChessStep> res;

    return res;

}
