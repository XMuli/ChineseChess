// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2019-2026 XMuli & Contributors
// SPDX-GitHub: https://github.com/XMuli/ChineseChess
// SPDX-Author: XMuli <xmulitech@gmail.com>

#include "MachineGame.h"
#include <QRandomGenerator>
#include <climits>
#include <algorithm>

// 棋子基础分值: JIANG, SHI, XIANG, MA, CHE, PAO, BING
static const int chessScore[] = {10000, 20, 40, 60, 100, 80, 10};

MachineGame::MachineGame(AIDifficulty diff)
    : m_difficulty(diff), m_bAiIsRed(false)
{
}

MachineGame::~MachineGame()
{
}

int MachineGame::getSearchDepth() const
{
    switch (m_difficulty) {
    case AIDifficulty::Easy:   return 1;
    case AIDifficulty::Medium: return 3;
    case AIDifficulty::Hard:   return 5;
    }
    return 3;
}

void MachineGame::saveStep(int selectID, int checkedID, int row, int col, QVector<ChessStep *> &steps)
{
    ChessStep* step = new ChessStep;
    step->m_nRowFrom = m_ChessPieces[selectID].m_nRow;
    step->m_nColFrom = m_ChessPieces[selectID].m_nCol;
    step->m_nRowTo = row;
    step->m_nnColTo = col;
    step->m_nMoveID = selectID;
    step->m_nKillID = checkedID;
    steps.append(step);
}

void MachineGame::getAllMoves(QVector<ChessStep *> &steps, bool forRed)
{
    int start = forRed ? 16 : 0;
    int end   = forRed ? 32 : 16;

    for (int id = start; id < end; id++) {
        if (m_ChessPieces[id].m_bDead)
            continue;

        for (int row = 0; row < 10; row++) {
            for (int col = 0; col < 9; col++) {
                int targetId = getStoneId(row, col);
                if (targetId != -1 && sameColor(id, targetId))
                    continue;
                int killId = (targetId != -1) ? targetId : -1;
                if (canMove(id, killId, row, col))
                    saveStep(id, killId, row, col, steps);
            }
        }
    }
}

void MachineGame::mouseReleaseEvent(QMouseEvent *ev)
{
    const bool wasRedTurn = m_bIsRed;
    ChessBoard::mouseReleaseEvent(ev);

    // AI 执黑时：红方刚走完（wasRedTurn=true, 现在m_bIsRed=false）触发AI
    // AI 执红时：黑方刚走完（wasRedTurn=false, 现在m_bIsRed=true）触发AI
    if (!m_bIsOver && wasRedTurn != m_bIsRed && m_bIsRed == m_bAiIsRed) {
        machineChooseAndMovePieces();
    }
}

void MachineGame::fakeMove(ChessStep *step)
{
    if (step->m_nKillID != -1)
        m_ChessPieces[step->m_nKillID].m_bDead = true;

    m_ChessPieces[step->m_nMoveID].m_nRow = step->m_nRowTo;
    m_ChessPieces[step->m_nMoveID].m_nCol = step->m_nnColTo;
    m_bIsRed = !m_bIsRed;
}

void MachineGame::unFakeMove(ChessStep *step)
{
    if (step->m_nKillID != -1)
        m_ChessPieces[step->m_nKillID].m_bDead = false;

    m_ChessPieces[step->m_nMoveID].m_nRow = step->m_nRowFrom;
    m_ChessPieces[step->m_nMoveID].m_nCol = step->m_nColFrom;
    m_bIsRed = !m_bIsRed;
}

// 位置评估表（黑方视角，row 0-9, col 0-8）
// 马的位置分
static const int posMA[10][9] = {
    { 0, 0, 4, 2, 2, 2, 4, 0, 0},
    { 0, 4, 6, 8, 8, 8, 6, 4, 0},
    { 4, 6,10,12,12,12,10, 6, 4},
    { 2, 8,12,14,14,14,12, 8, 2},
    { 2, 8,12,14,16,14,12, 8, 2},
    { 2, 8,12,14,16,14,12, 8, 2},
    { 2, 8,12,14,14,14,12, 8, 2},
    { 4, 6,10,12,12,12,10, 6, 4},
    { 0, 4, 6, 8, 8, 8, 6, 4, 0},
    { 0, 0, 4, 2, 2, 2, 4, 0, 0}
};

// 车的位置分
static const int posCHE[10][9] = {
    { 6, 8, 6, 8,10, 8, 6, 8, 6},
    { 6, 8, 8,10,12,10, 8, 8, 6},
    { 4, 8, 8, 8,10, 8, 8, 8, 4},
    { 4, 8, 8, 8,10, 8, 8, 8, 4},
    { 4, 8, 8, 8,10, 8, 8, 8, 4},
    { 4, 8, 8, 8,10, 8, 8, 8, 4},
    { 4, 8, 8, 8,10, 8, 8, 8, 4},
    { 4, 8, 8, 8,10, 8, 8, 8, 4},
    { 6, 8, 8,10,12,10, 8, 8, 6},
    { 6, 8, 6, 8,10, 8, 6, 8, 6}
};

// 炮的位置分
static const int posPAO[10][9] = {
    { 0, 0, 2, 4, 4, 4, 2, 0, 0},
    { 0, 2, 4, 4, 4, 4, 4, 2, 0},
    { 2, 4, 4, 4, 6, 4, 4, 4, 2},
    { 2, 4, 6, 8, 8, 8, 6, 4, 2},
    { 2, 4, 6, 8,10, 8, 6, 4, 2},
    { 2, 4, 6, 8,10, 8, 6, 4, 2},
    { 2, 4, 6, 8, 8, 8, 6, 4, 2},
    { 2, 4, 4, 4, 6, 4, 4, 4, 2},
    { 0, 2, 4, 4, 4, 4, 4, 2, 0},
    { 0, 0, 2, 4, 4, 4, 2, 0, 0}
};

// 兵的位置分（黑方兵视角）
static const int posBING[10][9] = {
    { 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 2, 2, 4, 6, 6, 6, 4, 2, 2},
    { 4, 6, 8,10,12,10, 8, 6, 4},
    { 4, 8,10,14,16,14,10, 8, 4},
    { 8,12,14,18,20,18,14,12, 8},
    {10,14,16,20,22,20,16,14,10},
    {10,14,16,20,22,20,16,14,10},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

static int getPositionScore(int type, int row, int col, bool isRed)
{
    // 红方棋子翻转行坐标
    int r = isRed ? (9 - row) : row;
    int c = isRed ? (8 - col) : col;
    switch (type) {
    case 3: return posMA[r][c];    // MA
    case 4: return posCHE[r][c];   // CHE
    case 5: return posPAO[r][c];   // PAO
    case 6: return posBING[r][c];  // BING
    default: return 0;
    }
}

int MachineGame::calcScore()
{
    int blackScore = 0;
    int redScore = 0;

    for (int i = 0; i < 16; i++) {
        if (m_ChessPieces[i].m_bDead) continue;
        int type = m_ChessPieces[i].m_emType;
        blackScore += chessScore[type];
        if (m_difficulty >= AIDifficulty::Medium)
            blackScore += getPositionScore(type, m_ChessPieces[i].m_nRow, m_ChessPieces[i].m_nCol, false);
    }

    for (int i = 16; i < 32; i++) {
        if (m_ChessPieces[i].m_bDead) continue;
        int type = m_ChessPieces[i].m_emType;
        redScore += chessScore[type];
        if (m_difficulty >= AIDifficulty::Medium)
            redScore += getPositionScore(type, m_ChessPieces[i].m_nRow, m_ChessPieces[i].m_nCol, true);
    }

    // AI 执黑时返回 black-red，执红时返回 red-black
    if (m_bAiIsRed)
        return redScore - blackScore;
    return blackScore - redScore;
}

int MachineGame::alphaBeta(int depth, int alpha, int beta, bool isMaximizing)
{
    if (depth == 0)
        return calcScore();

    // 检查将帅是否已死
    if (m_ChessPieces[4].m_bDead)  // 黑将死
        return m_bAiIsRed ? 100000 + depth : -(100000 + depth);
    if (m_ChessPieces[20].m_bDead) // 红帅死
        return m_bAiIsRed ? -(100000 + depth) : 100000 + depth;

    QVector<ChessStep*> steps;
    bool forRed = m_bIsRed;
    getAllMoves(steps, forRed);

    if (steps.isEmpty()) {
        return isMaximizing ? -(99999 + depth) : (99999 + depth);
    }

    // 走法排序：吃子走法优先
    std::sort(steps.begin(), steps.end(), [](ChessStep* a, ChessStep* b) {
        return (a->m_nKillID != -1) > (b->m_nKillID != -1);
    });

    int bestVal = isMaximizing ? INT_MIN : INT_MAX;

    for (auto* step : steps) {
        fakeMove(step);
        int val = alphaBeta(depth - 1, alpha, beta, !isMaximizing);
        unFakeMove(step);

        if (isMaximizing) {
            if (val > bestVal) bestVal = val;
            if (val > alpha) alpha = val;
        } else {
            if (val < bestVal) bestVal = val;
            if (val < beta) beta = val;
        }
        if (alpha >= beta)
            break;
    }

    for (auto* s : steps) delete s;
    return bestVal;
}

ChessStep* MachineGame::getBestMove()
{
    int depth = getSearchDepth();
    QVector<ChessStep*> steps;
    bool aiIsRedTurn = m_bIsRed;
    getAllMoves(steps, aiIsRedTurn);

    if (steps.isEmpty()) {
        whoWin();
        return nullptr;
    }

    // 走法排序：吃子走法优先
    std::sort(steps.begin(), steps.end(), [](ChessStep* a, ChessStep* b) {
        return (a->m_nKillID != -1) > (b->m_nKillID != -1);
    });

    int bestScore = INT_MIN;
    ChessStep* bestStep = nullptr;

    for (auto* step : steps) {
        fakeMove(step);
        int score = alphaBeta(depth - 1, INT_MIN, INT_MAX, false);
        unFakeMove(step);

        if (score > bestScore) {
            bestScore = score;
            bestStep = step;
        }
    }

    // 清理未使用的 step
    for (auto* s : steps) {
        if (s != bestStep) delete s;
    }

    if (!bestStep)
        whoWin();

    return bestStep;
}

void MachineGame::machineChooseAndMovePieces()
{
    ChessStep* step = getBestMove();
    if (step == nullptr)
        return;

    doMoveStone(step->m_nMoveID, step->m_nKillID, step->m_nRowTo, step->m_nnColTo);
    m_nSelectID = -1;
    delete step;
    update();
}
