// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2019-2026 XMuli & Contributors

#ifndef PUZZLEDATA_H
#define PUZZLEDATA_H

#include <QString>
#include <QVector>

struct PuzzlePiece {
    int id;
    int row;
    int col;
};

struct PuzzleConfig {
    QString name;
    QString description;
    bool redFirst;
    bool playerIsRed;
    QVector<PuzzlePiece> pieces;  // 只列出存活棋子，其余默认死亡
};

QVector<PuzzleConfig> getBuiltinPuzzles();

#endif // PUZZLEDATA_H
