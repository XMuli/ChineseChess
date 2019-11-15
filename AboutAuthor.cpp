#include "AboutAuthor.h"
#include "ui_AboutAuthor.h"

AboutAuthor::AboutAuthor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutAuthor)
{
    ui->setupUi(this);
}

AboutAuthor::~AboutAuthor()
{
    delete ui;
}
