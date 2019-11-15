#ifndef SELECTGAMEMODE_H
#define SELECTGAMEMODE_H

#include <QDialog>
#include <QPushButton>

class SelectGameMode : public QDialog
{
    Q_OBJECT
public:
    explicit SelectGameMode(QWidget *parent = 0);
    ~SelectGameMode();

    QPushButton* m_buttons[4];
    int m_nSelect;
signals:

public slots:
    void slotClicked();
};

#endif // SELECTGAMEMODE_H
