#include "Rule.h"
#include <iostream>

namespace rule {

    ChessPiece getPieces(ChessState* state,bool redOrBlack,ChessPiece::CHESS_TYPE type){
        return ChessPiece();
    }


    std::vector<ChessStep> generateUnblockingStepsForOnePiece(ChessPiece const &pieces){
        std::vector<ChessStep> result;
        _helper::stepJIANGorBING(pieces,result);
        _helper::stepPAOorCHE(pieces,result);
        _helper::stepSHI(pieces,result);
        _helper::stepXIANG(pieces,result);
        _helper::stepMA(pieces,result);

//        std::cout<<"generated "<< result.size() << " steps for piece at  " << pieces.row << ":"<<pieces.col<< std::endl;
        return result;
    }


    // don't handle kill here
    bool validStep(ChessStep &step,ChessState* state){
        if(step.toCol >= TOTAL_COL || step.toCol < 0){
            return false;
        }

        if(step.toRow >= TOTAL_ROW || step.toRow < 0){
            return false;
        }

        if(step.fromCol == step.toCol && step.fromRow == step.toRow){
            return false;
        }

        switch (state->getPieceById(step.moveId).type) {
        case ChessPiece::JIANG:
            return _helper::validateJIANG(step,state);

        case ChessPiece::BING:
            return _helper::validateBING(step,state);

        case ChessPiece::SHI:
            return _helper::validateSHI(step,state);

        case ChessPiece::XIANG:
            return _helper::validateXIANG(step,state);

        case ChessPiece::CHE:
            return _helper::validateCHE(step,state);

        case ChessPiece::MA:
            return _helper::validateMA(step,state);

        case ChessPiece::PAO:
            return _helper::validatePAO(step,state);

        default:
            break;
        }

        throw "invalid piece";
    }


}

namespace rule {
    // validators
    namespace _helper {
    // validate functions ONLY validate for non-denpendcy steps, not random steps
        bool validateJIANG(ChessStep &step,ChessState* state){
            ChessPiece piece = state->getPieceById(step.moveId);

            if(piece.type != ChessPiece::JIANG){
                throw "invalid parameter";
            }

            // if not in palace, we don't move
            if(!isInPalace(step.toRow,step.toCol)){
                return false;
            }

            return !isDestinationTakenByAlly(step,piece,state);
        }

        bool validateBING(ChessStep &step,ChessState* state){
            ChessPiece piece = state->getPieceById(step.moveId);

            if(piece.type != ChessPiece::BING){
                throw "invalid parameter";
            }

            // cannot go back as red
            if(piece.isRed &&
                    step.fromRow < step.toRow){
                return false;
            }

             // cannot go back as black
            if(!piece.isRed &&
                    step.fromRow > step.toRow){
                return false;
            }

            // if in home side, cannot go left or right
            if(isInHomeSide(piece) && step.toCol != step.fromCol){
                return false;
            }

            return !isDestinationTakenByAlly(step,piece,state);
        }

        bool validatePAO(ChessStep &step,ChessState* state){
            ChessPiece piece = state->getPieceById(step.moveId);
            if(piece.type != ChessPiece::PAO){
                throw "invalid parameter";
            }

            int numInBetween = numberOfPiecesInBetweenStep(step,state);

            if(isDestinationTakenByAlly(step,piece,state)){
                return false;
            }

            // if there's nothing in between destination, and position is not occupied, it is valid
            if(numInBetween == 0 && !isPositionOccupied(step.toRow,step.toCol,state)){
                return true;
            }

            // if there's exactly one pieces beteween start pos to end pos, and the end pos is occupied by an enemy
            // then it is valid by kill the enemy
            if(numInBetween == 1 && isPositionOccupied(step.toRow,step.toCol,state)&&
                    !isDestinationTakenByAlly(step,piece,state)){
                return true;
            }

            return false;
        }

        bool validateCHE(ChessStep &step,ChessState* state){
            ChessPiece piece = state->getPieceById(step.moveId);
            if(piece.type != ChessPiece::CHE){
                throw "invalid parameter";
            }

            if(numberOfPiecesInBetweenStep(step,state)!=0){
                return false;
            }
            return !isDestinationTakenByAlly(step,piece,state);
        }

        bool validateXIANG(ChessStep &step,ChessState* state){

            ChessPiece piece = state->getPieceById(step.moveId);
            if(piece.type != ChessPiece::XIANG){
                throw "invalid parameter";
            }

            // moving over border
            if(step.fromRow >= RED_BORDER && step.toRow <RED_BORDER){
                return false;
            }
            // moving over border
            if(step.fromRow <= BLACK_BOREDR && step.toRow > BLACK_BOREDR){
                return false;
            }

            int eyeRow,eyeCol;

            eyeCol = (step.toCol - step.fromCol)/2 + step.fromCol;
            eyeRow = (step.toRow - step.fromRow)/2 + step.fromRow;


            if(isPositionOccupied(eyeRow,eyeCol,state)){
                return false;
            }

            return !isDestinationTakenByAlly(step,piece,state);
        }

        bool validateMA(ChessStep &step,ChessState* state){

            ChessPiece piece = state->getPieceById(step.moveId);
            if(piece.type != ChessPiece::MA){
                throw "invalid parameter";
            }

            //moving to right
            if(step.toCol - step.fromCol == 2){
                return !isPositionOccupied(step.fromRow,step.fromCol+1,state);
            }

            //move to the left
            if(step.toCol - step.fromCol == -2){
                return !isPositionOccupied(step.fromRow,step.fromCol-1,state);
            }

            //  move to bottom
            if(step.toRow - step.fromRow == 2){
                return !isPositionOccupied(step.fromRow+1,step.fromCol,state);
            }

            // move to top
            if(step.toRow - step.fromRow == -2){
                return !isPositionOccupied(step.fromRow-1,step.fromCol,state);
            }


            return !isDestinationTakenByAlly(step,piece,state);
        }

        bool validateSHI(ChessStep &step,ChessState* state){
            ChessPiece piece = state->getPieceById(step.moveId);
            if(piece.type != ChessPiece::SHI){
                throw "invalid parameter";
            }

            if(!isInPalace(step.toRow,step.toCol)){
                return false;
            }

            return !isDestinationTakenByAlly(step,piece,state);
        }
    }
    // helpers
    namespace _helper{
        bool isPositionOccupied(int row,int col,ChessState* state){
            ChessPiece* piece = state->getPieceByPos(row,col);
            if (piece == nullptr){
                return false;
            }
            return !piece->isDead;
        }

        bool isEnemyPiece(ChessPiece& pieceA,ChessPiece& pieceB){
            return pieceA.isRed != pieceB.isRed;
        }

        bool isInPalace(int row,int col){
            if(col<=5 && col >=3){
                return (row >= 0 && row <=2) || (row >= 7 && row <=9);
            }
            return false;
        }
        bool isInHomeSide(ChessPiece& piece){
            if(piece.isRed){
                return piece.row >=5;
            }

            return piece.row <= 4;
        }


        bool isDestinationTakenByAlly(ChessStep &step,ChessPiece& piece,ChessState* state){

            if(isPositionOccupied(step.toRow, step.toCol, state)){
                ChessPiece* pieceHoldsPos = state->getPieceByPos(step.toRow,step.toCol);
                if(!isEnemyPiece(piece,*pieceHoldsPos)){
                    //pos is occupied by alias
                    return true;
                }
            }
            // pos not taken
            return false;
        }

        int numberOfPiecesInBetweenStep(ChessStep &step,ChessState* state){
            if (step.fromCol != step.toCol && step.fromRow!=step.toRow){
                throw "invaid, not going stright";
            }

            int count = 0;
            int toCheckRow[] = {0,1,2,3,4,5,6,7,8,9};
            int toCheckCol[] = {0,1,2,3,4,5,6,7,8};

            // if movine along the same row, see if there's anything in between from col to to col
            if(step.fromRow == step.toRow){
                toCheckCol[step.fromCol] = - 1;
                toCheckCol[step.toCol] = - 1;
                bool flag = false;
                for(int col:toCheckCol){

                   if(flag &&col != step.toCol && isPositionOccupied(step.fromRow, col, state)){
                       count++;
                   }

                   if(col == -1){
                       flag = !flag;
                   }
                }

            }

            if(step.fromCol == step.toCol){
                toCheckRow[step.fromRow] = - 1;
                toCheckRow[step.toRow] = - 1;
                bool flag = false;
                for(int row:toCheckRow){
                    if(flag && row!= step.toRow && isPositionOccupied(row, step.fromCol, state)){
                        count++;
                    }


                    if(row == -1){
                        flag = !flag;
                    }
                }
            }

            return count;
        }
    }
    // independent step generators
    namespace _helper {
        // step*() provides steps withou limitation, can go off bound, use with combined validator
        void stepJIANGorBING(ChessPiece const &pieces,std::vector<ChessStep> &result){
            if(!(pieces.type == ChessPiece::JIANG || pieces.type == ChessPiece::BING) ){
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
            if(!(pieces.type == ChessPiece::CHE || pieces.type == ChessPiece::PAO) ){
                return;
            }

            for(int row = 0;row<TOTAL_ROW;row++){
                ChessStep step(pieces);
                step.toRow = row;
                step.toCol = pieces.col;
                result.push_back(step);
            }

            for(int col = 0;col<TOTAL_COL;col++){
                ChessStep step(pieces);
                step.toRow = pieces.row;
                step.toCol = col;
                result.push_back(step);
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

    }
}
