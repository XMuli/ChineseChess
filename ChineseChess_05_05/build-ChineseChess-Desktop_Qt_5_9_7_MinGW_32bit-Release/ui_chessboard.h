/********************************************************************************
** Form generated from reading UI file 'chessboard.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHESSBOARD_H
#define UI_CHESSBOARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChessBoard
{
public:
    QFrame *line_2;
    QLCDNumber *lcdNumber;
    QLabel *label;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_start;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_reset;
    QPushButton *pushButton_about;
    QLabel *label_2;

    void setupUi(QWidget *ChessBoard)
    {
        if (ChessBoard->objectName().isEmpty())
            ChessBoard->setObjectName(QStringLiteral("ChessBoard"));
        ChessBoard->resize(1156, 940);
        line_2 = new QFrame(ChessBoard);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(850, 0, 16, 991));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);
        lcdNumber = new QLCDNumber(ChessBoard);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));
        lcdNumber->setGeometry(QRect(890, 60, 241, 81));
        label = new QLabel(ChessBoard);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(890, 20, 131, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\215\216\346\226\207\350\241\214\346\245\267"));
        font.setPointSize(18);
        label->setFont(font);
        layoutWidget = new QWidget(ChessBoard);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(893, 150, 241, 31));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_start = new QPushButton(layoutWidget);
        pushButton_start->setObjectName(QStringLiteral("pushButton_start"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\215\216\346\226\207\350\241\214\346\245\267"));
        font1.setPointSize(10);
        pushButton_start->setFont(font1);

        horizontalLayout->addWidget(pushButton_start);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_reset = new QPushButton(layoutWidget);
        pushButton_reset->setObjectName(QStringLiteral("pushButton_reset"));
        pushButton_reset->setFont(font1);

        horizontalLayout->addWidget(pushButton_reset);

        pushButton_about = new QPushButton(ChessBoard);
        pushButton_about->setObjectName(QStringLiteral("pushButton_about"));
        pushButton_about->setGeometry(QRect(1060, 880, 75, 23));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\215\216\346\226\207\350\241\214\346\245\267"));
        font2.setPointSize(10);
        font2.setBold(false);
        font2.setWeight(50);
        pushButton_about->setFont(font2);
        label_2 = new QLabel(ChessBoard);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(860, 0, 291, 941));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/images/b.jpg")));
        label_2->setScaledContents(true);
        label_2->raise();
        line_2->raise();
        lcdNumber->raise();
        label->raise();
        layoutWidget->raise();
        pushButton_about->raise();

        retranslateUi(ChessBoard);

        QMetaObject::connectSlotsByName(ChessBoard);
    } // setupUi

    void retranslateUi(QWidget *ChessBoard)
    {
        ChessBoard->setWindowTitle(QApplication::translate("ChessBoard", "ChessBoard", Q_NULLPTR));
        label->setText(QApplication::translate("ChessBoard", "\345\257\271\346\210\230\350\256\241\346\227\266:", Q_NULLPTR));
        pushButton_start->setText(QApplication::translate("ChessBoard", "\345\274\200\345\247\213", Q_NULLPTR));
        pushButton_reset->setText(QApplication::translate("ChessBoard", "\351\207\215\347\275\256", Q_NULLPTR));
        pushButton_about->setText(QApplication::translate("ChessBoard", "\345\205\263\344\272\216\344\275\234\350\200\205", Q_NULLPTR));
        label_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ChessBoard: public Ui_ChessBoard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHESSBOARD_H
