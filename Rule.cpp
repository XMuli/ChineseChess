#include "Rule.h"


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

        switch (state->getPiece(step.moveId).type) {
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
            ChessPiece piece = state->getPiece(step.moveId);

            if(piece.type != ChessPiece::JIANG){
                throw "invalid parameter";
            }

            // if not in palace, we don't remove
            if(!isInPalace(step.toCol,step.toRow)){
                return false;
            }

            return canMoveInState(step,piece,state);
        }

        bool validateBING(ChessStep &step,ChessState* state){
            ChessPiece piece = state->getPiece(step.moveId);

            if(piece.type != ChessPiece::BING){
                throw "invalid parameter";
            }

            // cannot go back
            if(step.fromRow < step.toRow){
                return false;
            }

            // if in home side, cannot go left or right
            if(isInHomeSide(piece) && step.toCol != step.fromCol){
                return false;
            }

            return canMoveInState(step,piece,state);
        }

        bool validatePAO(ChessStep &step,ChessState* state){
            int numInBetween = numberOfPiecesInBetweenStep(step,state);

            if(numInBetween == 0){
                return true;
            }

            if(numInBetween == 1 && isPositionOccupied(step.toRow,step.toCol,state)){
                return true;
            }

            return false;
        }

        bool validateCHE(ChessStep &step,ChessState* state){
            if(numberOfPiecesInBetweenStep(step,state)!=0){
                return false;
            }
            return true;
        }

        bool validateXAING(ChessStep &step,ChessState* state){
            // moving over border
            if(step.fromRow >= RED_BORDER && step.toRow <RED_BORDER){
                return false;
            }
            // moving over border
            if(step.fromRow <= BLACK_BOREDR && step.toRow > BLACK_BOREDR){
                return false;
            }

            int eyeRow,eyeCol;

            eyeCol == (stpe.toCol - stpe.fromCol)/2 + stpe.fromCol;
            eyeRow == (stpe.toRow - stpe.fromRow)/2 + stpe.fromRow;


            return isPositionOccupied(eyeRow,eyeCol,state);
        }

        bool validateMA(ChessStep &step,ChessState* state){

            //moving to right
            if(step.toCol - step.fromCol == 2){
                return isPositionOccupied(step.fromRow,step.fromCol+1,state);
            }

            //move to the left
            if(step.toCol - step.fromCol == -2){
                return isPositionOccupied(step.fromRow,step.fromCol-1,state);
            }

            //  move to bottom
            if(step.toRow - step.fromRow == 2){
                return isPositionOccupied(step.fromRow+1,step.fromCol,state);
            }

            // move to top
            if(step.toRow - step.fromRow == -2){
                return isPositionOccupied(step.fromRow-1,step.fromCol,state);
            }


            return false;
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
            return pieceA.isRed == pieceB.isRed;
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

        bool canMoveInState(ChessStep &step,ChessPiece& piece,ChessState* state){

            if(isPositionOccupied(step.toRow,step.toCol,state)){
                ChessPiece* pieceHoldsPos = state->getPieceByPos(step.toRow,step.toCol);

                if(isEnemyPiece(piece,*pieceHoldsPos)){
                    return true;
                }else{
                    // a pos is taken by alias pieces, cannot move
                    return false;
                }
            }
            // pos not taken
            return true;
        }

        int numberOfPiecesInBetweenStep(ChessStep &step,ChessState* state){
            if (step.fromCol != step.toCol && step.fromRow!=step.toRow){
                throw "invaid, not going stright";
            }

            int count = 0;

            // if movine along the same row, see if there's anything in between from col to to col
            if(step.fromRow == step.toRow){
                for(auto col = step.fromCol+1; col<step.toCol; col++){
                    if(state->getPieceByPos(step.fromRow,col) !=nullptr){
                        count++;
                    }
                }
            }

            if(step.fromCol == step.toCol){
                for(auto row = step.fromRow+1; row<step.toRow; row++){
                    if(state->getPieceByPos(step.row,step.fromCol) !=nullptr){
                        count++;
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

    }
}
