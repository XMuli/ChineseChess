#ifndef RULE_H
#define RULE_H

#include "ChessPieces.h"
#include "ChessStep.h"
#include "ChessState.h"

#define TOTAL_ROW 10
#define TOTAL_COL 9
#define RED_BORDER 5
#define BLACK_BOREDR 4

#include <vector>
//------------------------------ helpers
namespace rule {

    ChessPiece getPieces(ChessState* state,bool redOrBlack,ChessPiece::CHESS_TYPE type);
    // step*() provides steps withou limitation, can go off bound, use with combined validator
    std::vector<ChessStep> generateUnblockingStepsForOnePiece(ChessPiece const &pieces);

    bool validStep(ChessStep &step,ChessState* state);

    std::vector<ChessStep> generateSteps(ChessPiece const &pieces);

    bool whoHasBetterChanceToWin(ChessState *state);
    namespace _helper {

            void stepJIANGorBING(ChessPiece const &pieces,std::vector<ChessStep> &result);

            void stepPAOorCHE(ChessPiece const &pieces,std::vector<ChessStep> &result);

            void stepSHI(ChessPiece const &pieces,std::vector<ChessStep> &result);

            void stepXIANG(ChessPiece const &pieces,std::vector<ChessStep> &result);

            void stepMA(ChessPiece const &pieces,std::vector<ChessStep> &result);

            bool validateJIANG(ChessStep &step,ChessState* state);

            bool validateBING(ChessStep &step,ChessState* state);

            bool validatePAO(ChessStep &step,ChessState* state);

            bool validateCHE(ChessStep &step,ChessState* state);

            bool validateXIANG(ChessStep &step,ChessState* state);

            bool validateMA(ChessStep &step,ChessState* state);

            bool validateSHI(ChessStep &step,ChessState* state);

            bool isPositionOccupied(int row,int col,ChessState* state);

            bool isEnemyPiece(ChessPiece& pieceA,ChessPiece& pieceB);

            void handleKill(ChessStep &step,ChessPiece *tokill);

            bool isInPalace(int row,int col);

            bool isInHomeSide(ChessPiece& piece);

            bool isDestinationTakenByAlly(ChessStep &step,ChessPiece& piece,ChessState* state);

            int numberOfPiecesInBetweenStep(ChessStep &step,ChessState* state);


        }


}

#endif // RULE_H
