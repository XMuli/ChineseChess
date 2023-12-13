/*
 * Copyright (C)  2019~2020  偕臧  All rights reserved.
 *
 * Author:  xmuli(偕臧) xmulitech@gmail.com
 *
 * GitHub:  https://github.com/XMuli/ChineseChess
 * Blogs:   https://xmuli.tech
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/gpl-3.0.html>.
 */
#ifndef ABOUTAUTHOR_H
#define ABOUTAUTHOR_H

#include <QDialog>
#include <QFont>

namespace Ui {
class AboutAuthor;
}

class AboutAuthor : public QDialog
{
    Q_OBJECT

public:
    explicit AboutAuthor(QWidget *parent = 0);
    ~AboutAuthor();

protected:
    virtual void paintEvent(QPaintEvent *event) override;

private:
    Ui::AboutAuthor *ui;
    QWidget * QDialog;
};

#endif // ABOUTAUTHOR_H
