// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2019-2026 XMuli & Contributors

#include "PuzzleData.h"

// 棋子ID映射 (黑方0-15, 红方16-31):
// 黑: 车0,马1,象2,士3,将4,士5,象6,马7,车8,炮9,炮10,卒11-15
// 红: 车16,马17,象18,士19,帅20,士21,象22,马23,车24,炮25,炮26,兵27-31

QVector<PuzzleConfig> getBuiltinPuzzles()
{
    QVector<PuzzleConfig> puzzles;

    // 残局1: 大刀剜心
    {
        PuzzleConfig p;
        p.name = "大刀剜心";
        p.description = "红先胜，经典杀法残局";
        p.redFirst = true;
        p.playerIsRed = true;
        p.pieces = {
            {4, 0, 4},   // 黑将
            {3, 0, 3},   // 黑士
            {5, 0, 5},   // 黑士
            {24, 1, 4},  // 红车
            {25, 2, 4},  // 红炮
            {20, 9, 4},  // 红帅
        };
        puzzles.append(p);
    }

    // 残局2: 双车错
    {
        PuzzleConfig p;
        p.name = "双车错";
        p.description = "红先胜，双车配合杀法";
        p.redFirst = true;
        p.playerIsRed = true;
        p.pieces = {
            {4, 0, 4},   // 黑将
            {3, 0, 3},   // 黑士
            {5, 0, 5},   // 黑士
            {0, 1, 0},   // 黑车
            {16, 1, 3},  // 红车
            {24, 2, 5},  // 红车
            {20, 9, 4},  // 红帅
        };
        puzzles.append(p);
    }

    // 残局3: 炮辗丹砂
    {
        PuzzleConfig p;
        p.name = "炮辗丹砂";
        p.description = "红先胜，炮的精妙运用";
        p.redFirst = true;
        p.playerIsRed = true;
        p.pieces = {
            {4, 0, 4},   // 黑将
            {3, 0, 3},   // 黑士
            {0, 2, 0},   // 黑车
            {25, 0, 2},  // 红炮
            {26, 3, 4},  // 红炮
            {16, 2, 8},  // 红车
            {20, 9, 4},  // 红帅
        };
        puzzles.append(p);
    }

    // 残局4: 马后炮
    {
        PuzzleConfig p;
        p.name = "马后炮";
        p.description = "红先胜，经典马后炮杀法";
        p.redFirst = true;
        p.playerIsRed = true;
        p.pieces = {
            {4, 0, 4},   // 黑将
            {3, 0, 3},   // 黑士
            {5, 0, 5},   // 黑士
            {23, 2, 3},  // 红马
            {25, 4, 4},  // 红炮
            {20, 9, 4},  // 红帅
        };
        puzzles.append(p);
    }

    // 残局5: 铁门栓
    {
        PuzzleConfig p;
        p.name = "铁门栓";
        p.description = "红先胜，车炮配合经典杀法";
        p.redFirst = true;
        p.playerIsRed = true;
        p.pieces = {
            {4, 0, 3},   // 黑将
            {5, 1, 4},   // 黑士
            {9, 3, 0},   // 黑炮
            {16, 3, 3},  // 红车
            {25, 5, 3},  // 红炮
            {20, 9, 4},  // 红帅
        };
        puzzles.append(p);
    }

    return puzzles;
}
