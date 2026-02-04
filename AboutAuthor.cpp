// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2019-2025 XMuli & Contributors
// SPDX-GitHub: https://github.com/XMuli/ChineseChess
// SPDX-Author: XMuli <xmulitech@gmail.com>

#include "AboutAuthor.h"
#include "ui_AboutAuthor.h"
#include <QIcon>
#include <QPainter>

AboutAuthor::AboutAuthor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutAuthor)
{
    this->setWindowIcon(QIcon(":/images/chess.svg"));
    ui->setupUi(this);
}

AboutAuthor::~AboutAuthor()
{
    delete ui;
}

void AboutAuthor::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(rect(), QPixmap(":/images/background.jpg"));

    QDialog::paintEvent(event);
}
