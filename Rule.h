#ifndef RULE_H
#define RULE_H

#include "ChessPieces.h"
#include "ChessStep.h"
#include "ChessState.h"

#define TOTAL_ROW 10
#define TOTAL_COL 9

#include <vector>
//------------------------------ helpers
namespace rule {
    // step*() provides steps withou limitation, can go off bound, use with combined validator
    void stepJIANGorBING(ChessPiece const &pieces,std::vector<ChessStep> &result){
        if(pieces.type != ChessPiece::JIANG || pieces.type != ChessPiece::BING ){
            return;
        }

        ChessStep s1(pieces),s2(pieces),s3(pieces),s4(pieces);

        // Goes Up
        s1.toCol = pieces.col;
        s1.toRow = pieces.row-1;

        //Goes down
        s2.toCol = pieces.col;
        s2.toRow = pieces.row+1;

        // Goes right
        s3.toCol = pieces.col+1;
        s3.toRow = pieces.row;

        // Goes left
        s4.toCol = pieces.col-1;
        s4.toRow = pieces.row;

        result.push_back(s1);
        result.push_back(s2);
        result.push_back(s3);
        result.push_back(s4);
    }

    void stepPAOorCHE(ChessPiece const &pieces,std::vector<ChessStep> &result){
        if(pieces.type != ChessPiece::CHE || pieces.type != ChessPiece::PAO ){
            return;
        }

        for(int row = 0;row<TOTAL_ROW;row++){
            for(int col = 0;col<TOTAL_COL;col++){
                // if the row is the same row, or the col is the same col but not the same spot
                if(row == pieces.row || col  == pieces.col
                        && (row == pieces.row && col  == pieces.col )){
                    ChessStep step(pieces);
                    step.toRow = row;
                    step.toCol = col;
                    result.push_back(step);
                }
            }
        }
    }

    void stepSHI(ChessPiece const &pieces,std::vector<ChessStep> &result){
        if(pieces.type != ChessPiece::SHI){
            return;
        }

        ChessStep s1(pieces),s2(pieces),s3(pieces),s4(pieces);

        // Goes top left
        s1.toCol = pieces.col-1;
        s1.toRow = pieces.row-1;

        //Goes bottom right
        s2.toCol = pieces.col+1;
        s2.toRow = pieces.row+1;

        // Goes top right
        s3.toCol = pieces.col-1;
        s3.toRow = pieces.row+1;

        // Goes boot left
        s4.toCol = pieces.col+1;
        s4.toRow = pieces.row-1;

        result.push_back(s1);
        result.push_back(s2);
        result.push_back(s3);
        result.push_back(s4);
    }

    void stepXIANG(ChessPiece const &pieces,std::vector<ChessStep> &result){
        if(pieces.type != ChessPiece::XIANG){
            return;
        }

        ChessStep s1(pieces),s2(pieces),s3(pieces),s4(pieces);

        // Goes top left by two
        s1.toCol = pieces.col-2;
        s1.toRow = pieces.row-2;

        //Goes bottom right by two
        s2.toCol = pieces.col+2;
        s2.toRow = pieces.row+2;

        // Goes top right by two
        s3.toCol = pieces.col-2;
        s3.toRow = pieces.row+2;

        // Goes boot left by two
        s4.toCol = pieces.col+2;
        s4.toRow = pieces.row-2;

        result.push_back(s1);
        result.push_back(s2);
        result.push_back(s3);
        result.push_back(s4);

    }

    void stepMA(ChessPiece const &pieces,std::vector<ChessStep> &result){
        if(pieces.type != ChessPiece::MA){
            return;
        }

        ChessStep s1(pieces),s2(pieces),s3(pieces),s4(pieces),s5(pieces),s6(pieces),s7(pieces),s8(pieces);


        s1.toCol = pieces.col+1;
        s1.toRow = pieces.row+2;


        s2.toCol = pieces.col+1;
        s2.toRow = pieces.row-2;

        s3.toCol = pieces.col-1;
        s3.toRow = pieces.row+2;

        s4.toCol = pieces.col-1;
        s4.toRow = pieces.row-2;

        s5.toCol = pieces.col-2;
        s5.toRow = pieces.row-1;

        s6.toCol = pieces.col-2;
        s6.toRow = pieces.row+1;

        s7.toCol = pieces.col+2;
        s7.toRow = pieces.row-1;

        s8.toCol = pieces.col+2;
        s8.toRow = pieces.row+1;

        result.push_back(s1);
        result.push_back(s2);
        result.push_back(s3);
        result.push_back(s4);
        result.push_back(s5);
        result.push_back(s6);
        result.push_back(s7);
        result.push_back(s8);

    }

    std::vector<ChessStep> generateUnblockingSteps(ChessPiece const &pieces){
        std::vector<ChessStep> result;
        stepJIANGorBING(pieces,result);
        stepPAOorCHE(pieces,result);
        stepSHI(pieces,result);
        stepXIANG(pieces,result);
        stepMA(pieces,result);
        return result;
    }

    bool validateJIANG(ChessStep &step,ChessState* state){

    }

    bool validateBING(ChessStep &step,ChessState* state){

    }

    bool validatePAO(ChessStep &step,ChessState* state){

    }

    bool validateCHE(ChessStep &step,ChessState* state){

    }

    bool valid(ChessStep &step,ChessState* state){
        if(step.toCol >= TOTAL_COL || step.toCol < 0){
            return false;
        }

        if(step.toRow >= TOTAL_ROW || step.toRow < 0){
            return false;
        }


    }
}

#endif // RULE_H
