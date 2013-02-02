/********************************************************************************
** Form generated from reading UI file 'animation_info.ui'
**
** Created: Sat Feb 2 22:38:39 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANIMATION_INFO_H
#define UI_ANIMATION_INFO_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *name;
    QLabel *fps_2;
    QDoubleSpinBox *edit_fps;
    QLabel *cur_frame;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(905, 110);
        horizontalLayoutWidget = new QWidget(Form);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(-1, 19, 901, 61));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        name = new QLabel(horizontalLayoutWidget);
        name->setObjectName(QString::fromUtf8("name"));
        name->setEnabled(true);

        horizontalLayout->addWidget(name);

        fps_2 = new QLabel(horizontalLayoutWidget);
        fps_2->setObjectName(QString::fromUtf8("fps_2"));

        horizontalLayout->addWidget(fps_2);

        edit_fps = new QDoubleSpinBox(horizontalLayoutWidget);
        edit_fps->setObjectName(QString::fromUtf8("edit_fps"));

        horizontalLayout->addWidget(edit_fps);

        cur_frame = new QLabel(horizontalLayoutWidget);
        cur_frame->setObjectName(QString::fromUtf8("cur_frame"));

        horizontalLayout->addWidget(cur_frame);

        edit_fps->raise();
        name->raise();
        fps_2->raise();
        cur_frame->raise();

        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", 0, QApplication::UnicodeUTF8));
        name->setText(QApplication::translate("Form", "name", 0, QApplication::UnicodeUTF8));
        fps_2->setText(QApplication::translate("Form", "fps", 0, QApplication::UnicodeUTF8));
        cur_frame->setText(QApplication::translate("Form", "cur_fame", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANIMATION_INFO_H
