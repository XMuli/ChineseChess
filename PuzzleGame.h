// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2019-2026 XMuli & Contributors

#ifndef PUZZLEGAME_H
#define PUZZLEGAME_H

#include "MachineGame.h"
#include "PuzzleData.h"

class PuzzleGame : public MachineGame
{
    Q_OBJECT
public:
    PuzzleGame(const PuzzleConfig& config,
               AIDifficulty diff = AIDifficulty::Medium);
    ~PuzzleGame() = default;

    void loadPuzzle(const PuzzleConfig& config);

private:
    PuzzleConfig m_puzzle;
};

#endif // PUZZLEGAME_H
