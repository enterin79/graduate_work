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
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
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
    QWidget *layoutWidget;
    QFormLayout *formLayout_2;
    QLabel *label;
    QLineEdit *leNameEq;
    QLabel *label_2;
    QDateEdit *deFirstExpDate;
    QLabel *label_3;
    QTextEdit *leNote;
    QGroupBox *gbTest;
    QWidget *layoutWidget1;
    QFormLayout *formLayout;
    QLabel *label_4;
    QLineEdit *leNameTest;
    QLabel *label_5;
    QDateEdit *deDateTest;
    QLabel *label_6;
    QTextEdit *leDescript;
    ComboBoxForDB *cbEquipId;
    QLabel *label_7;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout;
    QPushButton *Apply;
    QPushButton *Delete;

    void setupUi(QWidget *Edit)
    {
        if (Edit->objectName().isEmpty())
            Edit->setObjectName(QString::fromUtf8("Edit"));
        Edit->resize(263, 281);
        gbEquip = new QGroupBox(Edit);
        gbEquip->setObjectName(QString::fromUtf8("gbEquip"));
        gbEquip->setGeometry(QRect(10, 10, 241, 231));
        layoutWidget = new QWidget(gbEquip);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 30, 221, 191));
        formLayout_2 = new QFormLayout(layoutWidget);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label);

        leNameEq = new QLineEdit(layoutWidget);
        leNameEq->setObjectName(QString::fromUtf8("leNameEq"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, leNameEq);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_2);

        deFirstExpDate = new QDateEdit(layoutWidget);
        deFirstExpDate->setObjectName(QString::fromUtf8("deFirstExpDate"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, deFirstExpDate);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_3);

        leNote = new QTextEdit(layoutWidget);
        leNote->setObjectName(QString::fromUtf8("leNote"));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, leNote);

        gbTest = new QGroupBox(Edit);
        gbTest->setObjectName(QString::fromUtf8("gbTest"));
        gbTest->setGeometry(QRect(10, 10, 241, 231));
        layoutWidget1 = new QWidget(gbTest);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 30, 221, 191));
        formLayout = new QFormLayout(layoutWidget1);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(layoutWidget1);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_4);

        leNameTest = new QLineEdit(layoutWidget1);
        leNameTest->setObjectName(QString::fromUtf8("leNameTest"));

        formLayout->setWidget(0, QFormLayout::FieldRole, leNameTest);

        label_5 = new QLabel(layoutWidget1);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_5);

        deDateTest = new QDateEdit(layoutWidget1);
        deDateTest->setObjectName(QString::fromUtf8("deDateTest"));

        formLayout->setWidget(1, QFormLayout::FieldRole, deDateTest);

        label_6 = new QLabel(layoutWidget1);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_6);

        leDescript = new QTextEdit(layoutWidget1);
        leDescript->setObjectName(QString::fromUtf8("leDescript"));

        formLayout->setWidget(2, QFormLayout::FieldRole, leDescript);

        cbEquipId = new ComboBoxForDB(layoutWidget1);
        cbEquipId->setObjectName(QString::fromUtf8("cbEquipId"));

        formLayout->setWidget(3, QFormLayout::FieldRole, cbEquipId);

        label_7 = new QLabel(layoutWidget1);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_7);

        layoutWidget2 = new QWidget(Edit);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(10, 250, 168, 24));
        horizontalLayout = new QHBoxLayout(layoutWidget2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        Apply = new QPushButton(layoutWidget2);
        Apply->setObjectName(QString::fromUtf8("Apply"));

        horizontalLayout->addWidget(Apply);

        Delete = new QPushButton(layoutWidget2);
        Delete->setObjectName(QString::fromUtf8("Delete"));

        horizontalLayout->addWidget(Delete);


        retranslateUi(Edit);

        QMetaObject::connectSlotsByName(Edit);
    } // setupUi

    void retranslateUi(QWidget *Edit)
    {
        Edit->setWindowTitle(QApplication::translate("Edit", "\320\240\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\320\275\320\270\320\265", nullptr));
        gbEquip->setTitle(QApplication::translate("Edit", "\320\236\320\261\320\276\321\200\321\203\320\264\320\276\320\262\320\260\320\275\320\270\320\265", nullptr));
        label->setText(QApplication::translate("Edit", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265", nullptr));
        label_2->setText(QApplication::translate("Edit", "\320\224\320\260\321\202\320\260 \320\267\320\260\320\277\321\203\321\201\320\272\320\260", nullptr));
        label_3->setText(QApplication::translate("Edit", "\320\236\320\277\320\270\321\201\320\260\320\275\320\270\320\265", nullptr));
        gbTest->setTitle(QApplication::translate("Edit", "\320\242\320\265\321\201\321\202", nullptr));
        label_4->setText(QApplication::translate("Edit", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265", nullptr));
        label_5->setText(QApplication::translate("Edit", "\320\224\320\260\321\202\320\260 \320\277\321\200\320\276\320\262\320\265\320\264\320\265\320\275\320\270\321\217", nullptr));
        label_6->setText(QApplication::translate("Edit", "\320\236\320\277\320\270\321\201\320\260\320\275\320\270\320\265", nullptr));
        label_7->setText(QApplication::translate("Edit", "\320\236\320\261\320\276\321\200\321\203\320\264\320\276\320\262\320\260\320\275\320\270\320\265", nullptr));
        Apply->setText(QApplication::translate("Edit", "\320\237\320\276\320\264\321\202\320\262\320\265\321\200\320\264\320\270\321\202\321\214", nullptr));
        Delete->setText(QApplication::translate("Edit", "\320\236\321\202\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Edit: public Ui_Edit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDIT_H
