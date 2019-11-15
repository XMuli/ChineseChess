#include "SelectGameMode.h"
#include <QVBoxLayout>

SelectGameMode::SelectGameMode(QWidget *parent): QDialog(parent)
{
    QVBoxLayout* lay = new QVBoxLayout(this);

    lay->addWidget(m_buttons[0] = new QPushButton("玩家自己对战"));
    lay->addWidget(m_buttons[1] = new QPushButton("玩家和AI对战"));
    lay->addWidget(m_buttons[2] = new QPushButton("双人网络对战"));

    for(int i=0; i<3; i++)
    {
        connect(m_buttons[i], SIGNAL(clicked()), this, SLOT(slotClicked()));
    }

}

SelectGameMode::~SelectGameMode()
{

}

void SelectGameMode::slotClicked()
{
    QObject* s = sender();
    for(int i=0; i<3; ++i)
    {
        if(m_buttons[i] == s)
        {
            this->m_nSelect = i;
            break;
        }
    }
    accept();
}

