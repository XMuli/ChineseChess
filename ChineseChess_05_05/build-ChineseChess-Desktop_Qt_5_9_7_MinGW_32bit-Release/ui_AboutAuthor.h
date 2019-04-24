/********************************************************************************
** Form generated from reading UI file 'AboutAuthor.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTAUTHOR_H
#define UI_ABOUTAUTHOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_AboutAuthor
{
public:
    QDialogButtonBox *buttonBox;
    QTextBrowser *textBrowser;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;

    void setupUi(QDialog *AboutAuthor)
    {
        if (AboutAuthor->objectName().isEmpty())
            AboutAuthor->setObjectName(QStringLiteral("AboutAuthor"));
        AboutAuthor->resize(882, 491);
        AboutAuthor->setFocusPolicy(Qt::NoFocus);
        AboutAuthor->setAcceptDrops(false);
        AboutAuthor->setToolTipDuration(0);
        AboutAuthor->setLayoutDirection(Qt::RightToLeft);
        buttonBox = new QDialogButtonBox(AboutAuthor);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(700, 430, 151, 31));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        textBrowser = new QTextBrowser(AboutAuthor);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(20, 10, 651, 461));
        textBrowser->setStyleSheet(QString::fromUtf8("background-image: url(:/images/5abc.png);\n"
"font: 9pt \"\345\215\216\346\226\207\346\245\267\344\275\223\";"));
        label = new QLabel(AboutAuthor);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(750, 30, 61, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\215\216\346\226\207\350\241\214\346\245\267"));
        font.setPointSize(16);
        label->setFont(font);
        label_2 = new QLabel(AboutAuthor);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(740, 220, 61, 31));
        label_2->setFont(font);
        label_3 = new QLabel(AboutAuthor);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(700, 60, 150, 150));
        label_3->setPixmap(QPixmap(QString::fromUtf8(":/images/WeChat.jpg")));
        label_3->setScaledContents(true);
        label_4 = new QLabel(AboutAuthor);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(700, 250, 150, 150));
        label_4->setPixmap(QPixmap(QString::fromUtf8(":/images/Alipay.jpg")));
        label_4->setScaledContents(true);
        label_5 = new QLabel(AboutAuthor);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(0, 0, 882, 491));
        label_5->setPixmap(QPixmap(QString::fromUtf8(":/images/5abc.png")));
        label_5->setScaledContents(true);
        label_5->raise();
        buttonBox->raise();
        textBrowser->raise();
        label->raise();
        label_2->raise();
        label_3->raise();
        label_4->raise();

        retranslateUi(AboutAuthor);
        QObject::connect(buttonBox, SIGNAL(accepted()), AboutAuthor, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), AboutAuthor, SLOT(reject()));

        QMetaObject::connectSlotsByName(AboutAuthor);
    } // setupUi

    void retranslateUi(QDialog *AboutAuthor)
    {
        AboutAuthor->setWindowTitle(QApplication::translate("AboutAuthor", "Dialog", Q_NULLPTR));
        textBrowser->setHtml(QApplication::translate("AboutAuthor", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'\345\215\216\346\226\207\346\245\267\344\275\223'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:12pt;\">\345\205\263\344\272\216\344\275\234\350\200\205:</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:12pt;\">\345\205\211\350\260\267\345\214\227\346\226\227\345\233\275\351\231\205\345\255\246\351\231\242  2015\347\272\247\350\275\257\344\273\266\345\267\245\347\250\213(1)\347\217\255  \345\274\240\346\226\207\350\200\225</span></p>\n"
""
                        "<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:12pt;\">\344\275\234\345\223\201\345\256\214\346\210\220\346\227\266\351\227\264:2019-2-1</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:12pt;\">\344\275\234\345\223\201\347\224\250\351\200\224: \346\257\225\344\270\232\350\256\276\350\256\241\344\275\234\345\223\201</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:12pt;\">\345\205\266\344\273\226:\345\246\202\346\236\234\350\247\211\345\276\227\350\257\245\344\275\234\345\223\201\345\257\271\344\275\240\346\234\211\347\224\250\357\274\214\346\210\226\350\200\205\346\234\211\347\226\221\346\203\221\346\210\226\350\200\205\346"
                        "\204\237\350\260\242\357\274\214\345\217\257\344\273\245\350\201\224\347\263\273\344\275\234\350\200\205\346\210\226\350\200\205\346\211\223\350\265\217\343\200\202\346\272\220\347\240\201\345\222\214\346\200\235\350\267\257\345\267\262\347\273\217\345\217\221\345\270\203\346\210\220\347\263\273\345\210\227\346\226\207\347\253\240\357\274\214\344\270\224\345\274\200\346\272\220\345\205\254\345\270\203\344\272\216\346\210\221\347\232\204github\345\222\214\345\215\232\345\256\242\357\274\214\344\276\233\345\244\247\345\256\266\345\255\246\344\271\240\345\217\202\350\200\203</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'SimSun';\"><br /></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:12pt;\">                                  \350\201\224\347\263\273\344\275\234"
                        "\350\200\205:</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:12pt;\">                                  QQ:252311126</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:12pt;\">                                  github: </span><a href=\"https://github.com/touwoyimuli/2019_01_Qt5_ChinessChess\"><span style=\" text-decoration: underline; color:#0000ff;\">https://github.com/touwoyimuli/2019_01_Qt5_ChinessChess</span></a></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:12pt;\">                                  Twitter: touwoyimuli</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right"
                        ":0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:12pt;\">                                  Facebook: touwoyimuli</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:12pt;\">                                  Telegram: </span><a href=\"https://t.me/joinchat/AAAAAEsU6akLiS41OXPzPQ\"><span style=\" font-family:'SimSun'; text-decoration: underline; color:#0000ff;\">https://t.me/joinchat/AAAAAEsU6akLiS41OXPzPQ</span></a></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:12pt;\">                                  QQ GMAILE: 252311126@qq.com<br />                                  GOOGLE GMAILE: 252311126aq@gmial.com </span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-bl"
                        "ock-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:12pt;\">                                  Personal Blog: </span><a href=\"https://blog.csdn.net/qq_33154343\"><span style=\" text-decoration: underline; color:#0000ff;\">\346\204\277\344\273\245\347\231\276\345\271\264\346\214\275\346\234\235\345\244\225\347\232\204\345\215\232\345\256\242</span></a></p></body></html>", Q_NULLPTR));
        label->setText(QApplication::translate("AboutAuthor", "\345\276\256    \344\277\241", Q_NULLPTR));
        label_2->setText(QApplication::translate("AboutAuthor", "\346\224\257\344\273\230\345\256\235", Q_NULLPTR));
        label_3->setText(QString());
        label_4->setText(QString());
        label_5->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class AboutAuthor: public Ui_AboutAuthor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTAUTHOR_H
