// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2019-2024 XMuli & Contributors
// SPDX-GitHub: https://github.com/XMuli/ChineseChess
// SPDX-Author: XMuli <xmulitech@gmail.com>

#ifndef ABOUTAUTHOR_H
#define ABOUTAUTHOR_H

#include <QDialog>
#include <QFont>

namespace Ui
{
    class AboutAuthor;
}

class AboutAuthor : public QDialog
{
    Q_OBJECT

public:
    explicit AboutAuthor(QWidget* parent = 0);
    ~AboutAuthor();

protected:
    virtual void paintEvent(QPaintEvent* event) override;

private:
    Ui::AboutAuthor* ui;
};

#endif // ABOUTAUTHOR_H
