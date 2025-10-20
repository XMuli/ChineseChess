// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2019-2025 XMuli & Contributors
// SPDX-GitHub: https://github.com/XMuli/ChineseChess
// SPDX-Author: XMuli <xmulitech@gmail.com>

#include "ChessVoice.h"

ChessVoice::ChessVoice(QObject *parent)
    : QObject(parent)
{
    // 注意：资源路径用 qrc 前缀（已在资源文件 .qrc 中配置）
    m_win.setSource(QUrl(QStringLiteral("qrc:/sound/WinSound.wav")));
    m_select.setSource(QUrl(QStringLiteral("qrc:/sound/selectChess.wav")));
    m_move.setSource(QUrl(QStringLiteral("qrc:/sound/moveChess.wav")));
    m_eat.setSource(QUrl(QStringLiteral("qrc:/sound/eatChess.wav")));
    m_back.setSource(QUrl(QStringLiteral("qrc:/sound/backChess.wav")));
    m_general.setSource(QUrl(QStringLiteral("qrc:/sound/generalSound.wav")));

    // 设置音量（0.0 至 1.0）
    m_win.setVolume(1.0f);
    m_select.setVolume(1.0f);
    m_move.setVolume(1.0f);
    m_eat.setVolume(1.0f);
    m_back.setVolume(1.0f);
    m_general.setVolume(1.0f);

    // 可选：预加载或设置 loopCount 等，下面为一次播放
    m_win.setLoopCount(1);
    m_select.setLoopCount(1);
    m_move.setLoopCount(1);
    m_eat.setLoopCount(1);
    m_back.setLoopCount(1);
    m_general.setLoopCount(1);
}

ChessVoice::~ChessVoice()
{
    // QSoundEffect 自动析构，成员变量无需手动 delete
}

void ChessVoice::voiceWin()
{
    m_win.play();
}

void ChessVoice::voiceSelect()
{
    m_select.play();
}

void ChessVoice::voiceMove()
{
    m_move.play();
}

void ChessVoice::voiceEat()
{
    m_eat.play();
}

void ChessVoice::voiceBack()
{
    m_back.play();
}

void ChessVoice::voiceGeneral()
{
    m_general.play();
}
