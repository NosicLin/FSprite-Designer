/********************************************************************************
** Form generated from reading UI file 'about.ui'
**
** Created: Sat Feb 2 22:38:39 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUT_H
#define UI_ABOUT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_AboutDialog
{
public:
    QLabel *about;
    QPushButton *close;
    QLabel *logo_label;

    void setupUi(QDialog *AboutDialog)
    {
        if (AboutDialog->objectName().isEmpty())
            AboutDialog->setObjectName(QString::fromUtf8("AboutDialog"));
        AboutDialog->resize(600, 365);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/IDI_TEAM_LOGO.ico"), QSize(), QIcon::Normal, QIcon::Off);
        AboutDialog->setWindowIcon(icon);
        about = new QLabel(AboutDialog);
        about->setObjectName(QString::fromUtf8("about"));
        about->setGeometry(QRect(20, 140, 541, 201));
        close = new QPushButton(AboutDialog);
        close->setObjectName(QString::fromUtf8("close"));
        close->setGeometry(QRect(500, 320, 75, 23));
        logo_label = new QLabel(AboutDialog);
        logo_label->setObjectName(QString::fromUtf8("logo_label"));
        logo_label->setGeometry(QRect(10, 0, 341, 121));
        logo_label->setPixmap(QPixmap(QString::fromUtf8(":/images/FAERIS_LOGO.png")));

        retranslateUi(AboutDialog);
        QObject::connect(close, SIGNAL(clicked()), AboutDialog, SLOT(accept()));

        QMetaObject::connectSlotsByName(AboutDialog);
    } // setupUi

    void retranslateUi(QDialog *AboutDialog)
    {
        AboutDialog->setWindowTitle(QApplication::translate("AboutDialog", "About FSprite Designer", 0, QApplication::UnicodeUTF8));
        about->setText(QApplication::translate("AboutDialog", "<html><head/><body><p>\351\243\236\345\243\253\347\262\276\347\201\265\357\274\210FSprite Designer\357\274\211\346\230\257\346\210\221\344\273\254\351\243\236\345\243\253\345\233\242\351\230\237\351\222\210\345\257\271\346\211\213\346\234\272\346\270\270\346\210\217\347\262\276\345\277\203\346\211\223\351\200\240\347\232\204\344\270\200\346\254\2762D\345\212\250\347\224\273\347\274\226\350\276\221\345\231\250\343\200\202\345\256\203\347\256\200\346\264\201\345\256\236\347\224\250\357\274\214\344\275\277\347\224\250\346\226\271\344\276\277\357\274\214\346\200\247\350\203\275\347\250\263\345\256\232\357\274\214\346\213\245\346\234\211\351\243\236\345\243\253\347\262\276\347\201\265\357\274\214\347\250\213\345\272\217\347\274\226\347\240\201\345\267\245\344\275\234\345\217\257\344\273\245\345\244\247\345\244\247\345\207\217\345\260\221\357\274\201</p><p>Email\357\274\232contact@faeris.com</p><p>\344\270\273\351\241\265\357\274\232<a href=\"www.faeris.com\"><span style=\" text-decoration: underline; color:#0000ff;"
                        "\">www.faeris.com</span></a></p><p>\350\256\272\345\235\233\357\274\232<a href=\"www.faeris.com/dz\"><span style=\" text-decoration: underline; color:#0000ff;\">www.faeris.com/dz</span></a></p><p>\350\205\276\350\256\257\345\276\256\345\215\232\357\274\232<a href=\"http://t.qq.com/faerisGame\"><span style=\" text-decoration: underline; color:#0000ff;\">http://t.qq.com/faerisGame</span></a></p><p>\347\211\210\346\235\203\346\211\200\346\234\211:www.faeris.com</p><p><br/></p></body></html>", 0, QApplication::UnicodeUTF8));
        close->setText(QApplication::translate("AboutDialog", "Close", 0, QApplication::UnicodeUTF8));
        logo_label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class AboutDialog: public Ui_AboutDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUT_H
