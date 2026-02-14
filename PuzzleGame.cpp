// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2019-2026 XMuli & Contributors

#include "PuzzleGame.h"

PuzzleGame::PuzzleGame(const PuzzleConfig& config, AIDifficulty diff)
    : MachineGame(diff), m_puzzle(config)
{
    loadPuzzle(config);
}

void PuzzleGame::loadPuzzle(const PuzzleConfig& config)
{
    m_puzzle = config;

    // 先将所有棋子标记为死亡
    for (int i = 0; i < 32; i++) {
        m_ChessPieces[i].init(i);
        m_ChessPieces[i].m_bDead = true;
    }

    // 根据配置恢复存活棋子的位置
    for (const auto& p : config.pieces) {
        if (p.id >= 0 && p.id < 32) {
            m_ChessPieces[p.id].m_nRow = p.row;
            m_ChessPieces[p.id].m_nCol = p.col;
            m_ChessPieces[p.id].m_bDead = false;
        }
    }

    // 设置先手和AI方
    m_bIsRed = config.redFirst;
    m_bAiIsRed = !config.playerIsRed;

    // 如果用户执黑，翻转视角
    setPerspectiveFlipped(!config.playerIsRed);

    m_ChessSteps.clear();
    m_nSelectID = -1;
    m_bIsOver = false;
    m_bIsShowStep = true;
    m_bTimerAutoStarted = false;

    update();

    // 如果AI先手，立即让AI走棋
    if (m_bIsRed == m_bAiIsRed) {
        machineChooseAndMovePieces();
    }
}
