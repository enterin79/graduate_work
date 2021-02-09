/********************************************************************************
** Form generated from reading UI file 'edit.ui'
**
** Created by: Qt User Interface Compiler version 5.12.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDIT_H
#define UI_EDIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include "comboboxfordb.h"

QT_BEGIN_NAMESPACE

class Ui_Edit
{
public:
    QGroupBox *gbEquip;
    QLineEdit *leNameEq;
    QDateEdit *deFirstExpDate;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QTextEdit *leNote;
    QGroupBox *gbTest;
    QLineEdit *leNameTest;
    QDateEdit *deDateTest;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QTextEdit *leDescript;
    ComboBoxForDB *cbEquipId;
    QLineEdit *unshowing;
    QPushButton *Apply;
    QPushButton *Delete;

    void setupUi(QWidget *Edit)
    {
        if (Edit->objectName().isEmpty())
            Edit->setObjectName(QString::fromUtf8("Edit"));
        Edit->resize(475, 273);
        gbEquip = new QGroupBox(Edit);
        gbEquip->setObjectName(QString::fromUtf8("gbEquip"));
        gbEquip->setGeometry(QRect(10, 0, 191, 201));
        leNameEq = new QLineEdit(gbEquip);
        leNameEq->setObjectName(QString::fromUtf8("leNameEq"));
        leNameEq->setGeometry(QRect(60, 30, 113, 21));
        deFirstExpDate = new QDateEdit(gbEquip);
        deFirstExpDate->setObjectName(QString::fromUtf8("deFirstExpDate"));
        deFirstExpDate->setGeometry(QRect(60, 60, 111, 22));
        label = new QLabel(gbEquip);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 30, 47, 14));
        label_2 = new QLabel(gbEquip);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(0, 60, 47, 14));
        label_3 = new QLabel(gbEquip);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(0, 90, 47, 14));
        leNote = new QTextEdit(gbEquip);
        leNote->setObjectName(QString::fromUtf8("leNote"));
        leNote->setGeometry(QRect(60, 90, 104, 70));
        gbTest = new QGroupBox(Edit);
        gbTest->setObjectName(QString::fromUtf8("gbTest"));
        gbTest->setGeometry(QRect(220, 0, 201, 231));
        leNameTest = new QLineEdit(gbTest);
        leNameTest->setObjectName(QString::fromUtf8("leNameTest"));
        leNameTest->setGeometry(QRect(60, 30, 113, 21));
        deDateTest = new QDateEdit(gbTest);
        deDateTest->setObjectName(QString::fromUtf8("deDateTest"));
        deDateTest->setGeometry(QRect(60, 60, 111, 22));
        label_4 = new QLabel(gbTest);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(0, 30, 47, 14));
        label_5 = new QLabel(gbTest);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(0, 60, 47, 14));
        label_6 = new QLabel(gbTest);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(0, 90, 47, 14));
        leDescript = new QTextEdit(gbTest);
        leDescript->setObjectName(QString::fromUtf8("leDescript"));
        leDescript->setGeometry(QRect(60, 90, 104, 70));
        cbEquipId = new ComboBoxForDB(gbTest);
        cbEquipId->setObjectName(QString::fromUtf8("cbEquipId"));
        cbEquipId->setGeometry(QRect(60, 170, 111, 22));
        unshowing = new QLineEdit(gbTest);
        unshowing->setObjectName(QString::fromUtf8("unshowing"));
        unshowing->setGeometry(QRect(60, 200, 113, 21));
        Apply = new QPushButton(Edit);
        Apply->setObjectName(QString::fromUtf8("Apply"));
        Apply->setGeometry(QRect(10, 210, 80, 22));
        Delete = new QPushButton(Edit);
        Delete->setObjectName(QString::fromUtf8("Delete"));
        Delete->setGeometry(QRect(100, 210, 80, 22));

        retranslateUi(Edit);

        QMetaObject::connectSlotsByName(Edit);
    } // setupUi

    void retranslateUi(QWidget *Edit)
    {
        Edit->setWindowTitle(QApplication::translate("Edit", "Form", nullptr));
        gbEquip->setTitle(QApplication::translate("Edit", "GroupBox", nullptr));
        label->setText(QApplication::translate("Edit", "TextLabel", nullptr));
        label_2->setText(QApplication::translate("Edit", "TextLabel", nullptr));
        label_3->setText(QApplication::translate("Edit", "TextLabel", nullptr));
        gbTest->setTitle(QApplication::translate("Edit", "GroupBox", nullptr));
        label_4->setText(QApplication::translate("Edit", "TextLabel", nullptr));
        label_5->setText(QApplication::translate("Edit", "TextLabel", nullptr));
        label_6->setText(QApplication::translate("Edit", "TextLabel", nullptr));
        Apply->setText(QApplication::translate("Edit", "\320\237\320\276\320\264\321\202\320\262\320\265\321\200\320\264\320\270\321\202\321\214", nullptr));
        Delete->setText(QApplication::translate("Edit", "\320\236\321\202\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Edit: public Ui_Edit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDIT_H
