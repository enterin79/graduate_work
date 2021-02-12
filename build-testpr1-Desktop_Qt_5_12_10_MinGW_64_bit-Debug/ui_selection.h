/********************************************************************************
** Form generated from reading UI file 'selection.ui'
**
** Created by: Qt User Interface Compiler version 5.12.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTION_H
#define UI_SELECTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include "comboboxfordb.h"

QT_BEGIN_NAMESPACE

class Ui_Selection
{
public:
    QPushButton *RevertTable;
    ComboBoxForDB *cbSelectColumn;
    QLabel *label_2;
    QPushButton *Search;
    QTextEdit *teDecript;
    QLabel *label_3;

    void setupUi(QWidget *Selection)
    {
        if (Selection->objectName().isEmpty())
            Selection->setObjectName(QString::fromUtf8("Selection"));
        Selection->resize(233, 265);
        RevertTable = new QPushButton(Selection);
        RevertTable->setObjectName(QString::fromUtf8("RevertTable"));
        RevertTable->setGeometry(QRect(100, 180, 80, 22));
        cbSelectColumn = new ComboBoxForDB(Selection);
        cbSelectColumn->setObjectName(QString::fromUtf8("cbSelectColumn"));
        cbSelectColumn->setGeometry(QRect(100, 30, 111, 22));
        label_2 = new QLabel(Selection);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 40, 47, 14));
        Search = new QPushButton(Selection);
        Search->setObjectName(QString::fromUtf8("Search"));
        Search->setGeometry(QRect(100, 150, 80, 22));
        teDecript = new QTextEdit(Selection);
        teDecript->setObjectName(QString::fromUtf8("teDecript"));
        teDecript->setGeometry(QRect(100, 70, 104, 70));
        label_3 = new QLabel(Selection);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 70, 47, 14));

        retranslateUi(Selection);

        QMetaObject::connectSlotsByName(Selection);
    } // setupUi

    void retranslateUi(QWidget *Selection)
    {
        Selection->setWindowTitle(QApplication::translate("Selection", "Form", nullptr));
        RevertTable->setText(QApplication::translate("Selection", "\320\222\320\276\321\201\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214", nullptr));
        label_2->setText(QApplication::translate("Selection", "TextLabel", nullptr));
        Search->setText(QApplication::translate("Selection", "\320\235\320\260\320\271\321\202\320\270", nullptr));
        label_3->setText(QApplication::translate("Selection", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Selection: public Ui_Selection {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTION_H
