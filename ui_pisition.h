/********************************************************************************
** Form generated from reading UI file 'pisition.ui'
**
** Created: Sat Feb 2 22:38:39 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PISITION_H
#define UI_PISITION_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLabel *labelX;
    QLabel *labelY;
    QDoubleSpinBox *position_X_Box;
    QDoubleSpinBox *position_YBox;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(240, 320);
        Form->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        buttonBox = new QDialogButtonBox(Form);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(40, 200, 156, 23));
        buttonBox->setStyleSheet(QString::fromUtf8(""));
        buttonBox->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(false);
        label = new QLabel(Form);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(60, 20, 111, 31));
        labelX = new QLabel(Form);
        labelX->setObjectName(QString::fromUtf8("labelX"));
        labelX->setGeometry(QRect(70, 70, 21, 16));
        labelY = new QLabel(Form);
        labelY->setObjectName(QString::fromUtf8("labelY"));
        labelY->setGeometry(QRect(70, 130, 20, 20));
        position_X_Box = new QDoubleSpinBox(Form);
        position_X_Box->setObjectName(QString::fromUtf8("position_X_Box"));
        position_X_Box->setGeometry(QRect(110, 70, 62, 22));
        position_YBox = new QDoubleSpinBox(Form);
        position_YBox->setObjectName(QString::fromUtf8("position_YBox"));
        position_YBox->setGeometry(QRect(110, 130, 62, 22));

        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", 0, QApplication::UnicodeUTF8));
        Form->setWindowFilePath(QString());
#ifndef QT_NO_WHATSTHIS
        buttonBox->setWhatsThis(QApplication::translate("Form", "<html><head/><body><p>OK</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        label->setText(QApplication::translate("Form", "<html><head/><body><p>Position Setting</p></body></html>", 0, QApplication::UnicodeUTF8));
        labelX->setText(QApplication::translate("Form", "X:", 0, QApplication::UnicodeUTF8));
        labelY->setText(QApplication::translate("Form", "Y:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PISITION_H
