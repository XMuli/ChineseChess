#ifndef CHESSRULEPROVIDER_H
#define CHESSRULEPROVIDER_H
#include "ChessPieces.h"
#include "ChessStep.h"
#include <vector>
#include <QVector>
#include "myLog.h"
#include "ChessState.h"
#define TOTALNUM 32
class ChessRuleProvider
{
public:
    ChessRuleProvider(ChessPiece pieces[]);
    ChessRuleProvider(std::vector<ChessPiece> pieces);
    bool canMove(int moveId, int killId, int row, int col);
    void getAllPossibleSteps(QVector<ChessStep>& steps);
    void getAllPossibleMoveStepAndKill(QVector<ChessStep>& steps);
    void getAllPossibleMoveStepAndNoKill(QVector<ChessStep>& steps);
    bool isGameEnd();
    bool whoWins();

private:
    ChessPiece m_ChessPieces[32];

    bool canMoveJIANG(int moveId, int killId, int row, int col);
    bool canMoveSHI(int moveId, int killId, int row, int col);
    bool canMoveXIANG(int moveId, int killId, int row, int col);
    bool canMoveMA(int moveId, int killId, int row, int col);
    bool canMoveCHE(int moveId, int killId, int row, int col);
    bool canMovePAO(int moveId, int killId, int row, int col);
    bool canMoveBING(int moveId, int killId, int row, int col);
    bool canSelect(int id);
    bool sameColor(int moveId, int killId);
    bool isRed(int id);
    int relation(int row1, int col1, int row2, int col2);
    int getStoneId(int row, int col);
    int  getStoneCountAtLine(int row1, int col1, int row2, int col2);
    bool isDead(int id);
    void saveStep(int moveid, int killid, int row, int col, QVector<ChessStep>& steps);

};

#endif // CHESSRULEPROVIDER_H
