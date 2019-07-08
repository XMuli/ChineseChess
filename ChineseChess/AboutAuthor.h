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

private:
    Ui::AboutAuthor *ui;
};

#endif // ABOUTAUTHOR_H
