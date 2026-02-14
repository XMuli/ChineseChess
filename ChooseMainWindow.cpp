// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2019-2026 XMuli & Contributors
// SPDX-GitHub: https://github.com/XMuli/ChineseChess
// SPDX-Author: XMuli <xmulitech@gmail.com>

#include "ChooseMainWindow.h"

#include <QApplication>
#include <QMessageBox>
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QSizePolicy>
#include <QInputDialog>

ChooseMainWindow::ChooseMainWindow(QWidget *parent) : QDialog(parent)
{
    this->setWindowTitle(QString("选择游戏方式 %1").arg(XPROJECT_VERSION));
    this->resize(500, 340);
    this->setMinimumSize(480, 280);
    this->setWindowIcon(QIcon(":/images/chess.svg"));

    auto* lay = new QVBoxLayout(this);
    lay->setContentsMargins(24, 24, 24, 24);
    lay->setSpacing(16);

    auto* title = new QLabel("选择一场对局", this);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font: 700 18pt 'Microsoft YaHei'; color: #222;");

    auto* subtitle = new QLabel("选择你希望的开局方式", this);
    subtitle->setAlignment(Qt::AlignCenter);
    subtitle->setStyleSheet("color: #666;");

    auto* btnLayout = new QVBoxLayout();
    btnLayout->setSpacing(12);

    const QStringList texts = {
        "玩家自己对战",
        "玩家和 AI 对战",
        "双人网络对战",
        "残局挑战"
    };

    for (int i = 0; i < 4; ++i) {
        m_buttons[i] = new QPushButton(texts[i], this);
        m_buttons[i]->setMinimumHeight(52);
        m_buttons[i]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        m_buttons[i]->setStyleSheet(
            "QPushButton {"
            "  border: 1px solid #c5c5c5;"
            "  border-radius: 8px;"
            "  background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
            "    stop:0 #ffffff, stop:1 #f3f3f3);"
            "  font: 12pt 'Microsoft YaHei';"
            "  padding: 10px 14px;"
            "}"
            "QPushButton:hover { background: #f8f8f8; }"
            "QPushButton:pressed { background: #e9e9e9; }"
        );
        btnLayout->addWidget(m_buttons[i]);
        btnLayout->setStretch(i, 1);
    }

    lay->addWidget(title);
    lay->addWidget(subtitle);
    lay->addLayout(btnLayout, 1);

    /*游戏方式一: 自己和自己下棋【同一台PC机器】*/
    connect(m_buttons[0], &QPushButton::clicked,[=](){
        this->hide();
        m_pAgainstYourself = new ChessBoard();
        m_pAgainstYourself->showNetworkGui(false);
        m_pAgainstYourself->setWindowTitle(QString("玩家自己对战 %1").arg(XPROJECT_VERSION));
        m_pAgainstYourself->show();

        //返回主窗口
        connect(m_pAgainstYourself,&ChessBoard::toMenu,[=](){
            m_pAgainstYourself->close();
            this->show();
        });
    });

    /*游戏方式二: 自己和电脑下棋【同一台PC机器】*/
    connect(m_buttons[1], &QPushButton::clicked,[=](){
        // 选择AI难度
        QStringList items = {"简单", "中等", "困难"};
        bool ok = false;
        QString item = QInputDialog::getItem(this, "AI难度", "请选择AI难度:", items, 1, false, &ok);
        if (!ok) {
            return;
        }

        AIDifficulty diff = AIDifficulty::Medium;
        if (item == "简单") diff = AIDifficulty::Easy;
        else if (item == "困难") diff = AIDifficulty::Hard;

        this->hide();

        m_pMachineGame = new MachineGame(diff);
        m_pMachineGame->showNetworkGui(false);
        QString diffText = item;
        m_pMachineGame->setWindowTitle(QString("玩家和AI对战 [%1] %2").arg(diffText).arg(XPROJECT_VERSION));
        m_pMachineGame->show();

        //返回主窗口
        connect(m_pMachineGame,&ChessBoard::toMenu,[=](){
            m_pMachineGame->close();
            this->show();
        });
    });

    /*游戏方式三: 双人网络对战下棋【可在局域网/广域网的不同台PC机器】
      - 一台实体主机: 一台主机，一台虚拟机，网络桥接模式
      - 两台实体主机: 同一局域网，或者都具有公网IP的广域网*/
    connect(m_buttons[2], &QPushButton::clicked,[=](){
        this->hide();
        QMessageBox::StandardButtons ret = QMessageBox::question(
            this,
            "提示",
            "是否作为[服务器]启动?<br>"
            "- Yes: 服务器, 属红方<br>"
            "- No: 客户端, 属黑方<br><br>"
            "<a href=\"https://github.com/XMuli/ChineseChess/wiki/%E7%BD%91%E7%BB%9C%E5%AF%B9%E6%88%98%E6%A8%A1%E5%BC%8F%E8%AE%BE%E7%BD%AE\">📢:  📖 Wiki</a>",
            QMessageBox::Yes | QMessageBox::No
            );

        const bool& bServer = ret == QMessageBox::Yes ? true : false;

        m_pNetworkGame = new NetworkGame(bServer);
        m_pNetworkGame->showNetworkGui(true);
        const QString& title = QString("双人网络对战 [%1] [%2]").arg(bServer ? "服务器 - 红方" : "客户端 - 黑方").arg(XPROJECT_VERSION) ;
        m_pNetworkGame->setWindowTitle(title);
        m_pNetworkGame->show();

        //返回主窗口
        connect(m_pNetworkGame,&ChessBoard::toMenu,[=](){
            m_pNetworkGame->close();
            this->show();
        });
    });

    /*游戏方式四: 残局挑战*/
    connect(m_buttons[3], &QPushButton::clicked,[=](){
        QVector<PuzzleConfig> puzzles = getBuiltinPuzzles();
        if (puzzles.isEmpty()) return;

        // 选择残局
        QStringList puzzleNames;
        for (const auto& p : puzzles)
            puzzleNames.append(p.name);

        bool ok = false;
        QString name = QInputDialog::getItem(this, "残局挑战", "请选择残局:", puzzleNames, 0, false, &ok);
        if (!ok) return;

        int idx = puzzleNames.indexOf(name);
        if (idx < 0) return;

        // 选择AI难度
        QStringList diffItems = {"简单", "中等", "困难"};
        QString diffStr = QInputDialog::getItem(this, "AI难度", "请选择AI难度:", diffItems, 1, false, &ok);
        if (!ok) return;

        AIDifficulty diff = AIDifficulty::Medium;
        if (diffStr == "简单") diff = AIDifficulty::Easy;
        else if (diffStr == "困难") diff = AIDifficulty::Hard;

        this->hide();
        m_pPuzzleGame = new PuzzleGame(puzzles[idx], diff);
        m_pPuzzleGame->showNetworkGui(false);
        m_pPuzzleGame->setWindowTitle(QString("残局挑战 - %1 [%2] %3").arg(name).arg(diffStr).arg(XPROJECT_VERSION));
        m_pPuzzleGame->show();

        connect(m_pPuzzleGame, &ChessBoard::toMenu, [=](){
            m_pPuzzleGame->close();
            this->show();
        });
    });
}


