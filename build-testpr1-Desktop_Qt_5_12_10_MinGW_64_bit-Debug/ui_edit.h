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
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include "comboboxfordb.h"

QT_BEGIN_NAMESPACE

class Ui_Edit
{
public:
    QGroupBox *gbEquip;
    QGridLayout *gridLayout_2;
    QFormLayout *formLayout_2;
    QLabel *label;
    QLineEdit *leNameEq;
    QLabel *label_3;
    QTextEdit *leDescriptEq;
    QLabel *label_2;
    ComboBoxForDB *cbStructEq;
    QGroupBox *gbCond;
    QGridLayout *gridLayout_3;
    QFormLayout *formLayout;
    QLabel *label_4;
    QLineEdit *leNameCond;
    QSpinBox *sbLoadCond;
    QLabel *label_5;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *Apply;
    QPushButton *Delete;
    QPushButton *btLogFile;
    QGroupBox *gbSolution;
    QGridLayout *gridLayout_4;
    QFormLayout *formLayout_3;
    QLabel *label_6;
    QLineEdit *leNameSolut;
    QTextEdit *leDescriptSolut;
    QLabel *label_7;
    QGroupBox *gbBreak;
    QGridLayout *gridLayout;
    QFormLayout *formLayout_4;
    QLabel *label_8;
    QLineEdit *leNameBreak;
    QTextEdit *leDescriptBreak;
    QLabel *label_9;
    QLineEdit *leCodeBreak;
    QLabel *label_10;
    QGroupBox *gbLog;
    QGridLayout *gridLayout_6;
    QGridLayout *gridLayout_5;
    QLabel *label_14;
    QDateTimeEdit *dtCurrTime;
    QLabel *label_15;
    QLabel *label_11;
    ComboBoxForDB *cbSolut;
    QRadioButton *rbUnnormalLog;
    QLabel *label_19;
    QPushButton *CurrDTPaste;
    QTextEdit *leDescriptLog;
    QDateTimeEdit *dtSolutExec;
    QPushButton *SolDTPaste;
    ComboBoxForDB *cbEquip;
    ComboBoxForDB *cbBreak;
    QLabel *label_17;
    QLabel *label_16;
    QLabel *label_18;
    ComboBoxForDB *cbCond;
    QLineEdit *ledtSolutExec;
    QPushButton *SolDTDelete;

    void setupUi(QWidget *Edit)
    {
        if (Edit->objectName().isEmpty())
            Edit->setObjectName(QString::fromUtf8("Edit"));
        Edit->resize(283, 316);
        Edit->setMinimumSize(QSize(264, 293));
        Edit->setMaximumSize(QSize(1000, 1000));
        gbEquip = new QGroupBox(Edit);
        gbEquip->setObjectName(QString::fromUtf8("gbEquip"));
        gbEquip->setGeometry(QRect(10, 10, 261, 261));
        gridLayout_2 = new QGridLayout(gbEquip);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        label = new QLabel(gbEquip);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label);

        leNameEq = new QLineEdit(gbEquip);
        leNameEq->setObjectName(QString::fromUtf8("leNameEq"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, leNameEq);

        label_3 = new QLabel(gbEquip);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_3);

        leDescriptEq = new QTextEdit(gbEquip);
        leDescriptEq->setObjectName(QString::fromUtf8("leDescriptEq"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, leDescriptEq);

        label_2 = new QLabel(gbEquip);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_2);

        cbStructEq = new ComboBoxForDB(gbEquip);
        cbStructEq->setObjectName(QString::fromUtf8("cbStructEq"));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, cbStructEq);


        gridLayout_2->addLayout(formLayout_2, 0, 0, 1, 1);

        gbCond = new QGroupBox(Edit);
        gbCond->setObjectName(QString::fromUtf8("gbCond"));
        gbCond->setGeometry(QRect(10, 10, 261, 261));
        gridLayout_3 = new QGridLayout(gbCond);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label_4 = new QLabel(gbCond);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_4);

        leNameCond = new QLineEdit(gbCond);
        leNameCond->setObjectName(QString::fromUtf8("leNameCond"));

        formLayout->setWidget(0, QFormLayout::FieldRole, leNameCond);

        sbLoadCond = new QSpinBox(gbCond);
        sbLoadCond->setObjectName(QString::fromUtf8("sbLoadCond"));

        formLayout->setWidget(1, QFormLayout::FieldRole, sbLoadCond);

        label_5 = new QLabel(gbCond);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_5);


        gridLayout_3->addLayout(formLayout, 0, 0, 1, 1);

        layoutWidget = new QWidget(Edit);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 280, 254, 24));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        Apply = new QPushButton(layoutWidget);
        Apply->setObjectName(QString::fromUtf8("Apply"));

        horizontalLayout->addWidget(Apply);

        Delete = new QPushButton(layoutWidget);
        Delete->setObjectName(QString::fromUtf8("Delete"));

        horizontalLayout->addWidget(Delete);

        btLogFile = new QPushButton(layoutWidget);
        btLogFile->setObjectName(QString::fromUtf8("btLogFile"));

        horizontalLayout->addWidget(btLogFile);

        gbSolution = new QGroupBox(Edit);
        gbSolution->setObjectName(QString::fromUtf8("gbSolution"));
        gbSolution->setGeometry(QRect(10, 10, 261, 261));
        gridLayout_4 = new QGridLayout(gbSolution);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        formLayout_3 = new QFormLayout();
        formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
        label_6 = new QLabel(gbSolution);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayout_3->setWidget(0, QFormLayout::LabelRole, label_6);

        leNameSolut = new QLineEdit(gbSolution);
        leNameSolut->setObjectName(QString::fromUtf8("leNameSolut"));

        formLayout_3->setWidget(0, QFormLayout::FieldRole, leNameSolut);

        leDescriptSolut = new QTextEdit(gbSolution);
        leDescriptSolut->setObjectName(QString::fromUtf8("leDescriptSolut"));

        formLayout_3->setWidget(1, QFormLayout::FieldRole, leDescriptSolut);

        label_7 = new QLabel(gbSolution);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        formLayout_3->setWidget(1, QFormLayout::LabelRole, label_7);


        gridLayout_4->addLayout(formLayout_3, 0, 0, 1, 1);

        gbBreak = new QGroupBox(Edit);
        gbBreak->setObjectName(QString::fromUtf8("gbBreak"));
        gbBreak->setGeometry(QRect(10, 10, 261, 261));
        gridLayout = new QGridLayout(gbBreak);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        formLayout_4 = new QFormLayout();
        formLayout_4->setObjectName(QString::fromUtf8("formLayout_4"));
        label_8 = new QLabel(gbBreak);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        formLayout_4->setWidget(1, QFormLayout::LabelRole, label_8);

        leNameBreak = new QLineEdit(gbBreak);
        leNameBreak->setObjectName(QString::fromUtf8("leNameBreak"));

        formLayout_4->setWidget(1, QFormLayout::FieldRole, leNameBreak);

        leDescriptBreak = new QTextEdit(gbBreak);
        leDescriptBreak->setObjectName(QString::fromUtf8("leDescriptBreak"));

        formLayout_4->setWidget(2, QFormLayout::FieldRole, leDescriptBreak);

        label_9 = new QLabel(gbBreak);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        formLayout_4->setWidget(2, QFormLayout::LabelRole, label_9);

        leCodeBreak = new QLineEdit(gbBreak);
        leCodeBreak->setObjectName(QString::fromUtf8("leCodeBreak"));

        formLayout_4->setWidget(0, QFormLayout::FieldRole, leCodeBreak);

        label_10 = new QLabel(gbBreak);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        formLayout_4->setWidget(0, QFormLayout::LabelRole, label_10);


        gridLayout->addLayout(formLayout_4, 0, 0, 1, 1);

        gbLog = new QGroupBox(Edit);
        gbLog->setObjectName(QString::fromUtf8("gbLog"));
        gbLog->setGeometry(QRect(10, 10, 261, 261));
        gridLayout_6 = new QGridLayout(gbLog);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        label_14 = new QLabel(gbLog);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout_5->addWidget(label_14, 0, 0, 1, 1);

        dtCurrTime = new QDateTimeEdit(gbLog);
        dtCurrTime->setObjectName(QString::fromUtf8("dtCurrTime"));
        dtCurrTime->setMinimumSize(QSize(100, 0));
        dtCurrTime->setCalendarPopup(true);
        dtCurrTime->setTimeSpec(Qt::LocalTime);

        gridLayout_5->addWidget(dtCurrTime, 0, 1, 1, 1);

        label_15 = new QLabel(gbLog);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout_5->addWidget(label_15, 2, 0, 1, 1);

        label_11 = new QLabel(gbLog);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout_5->addWidget(label_11, 9, 1, 1, 1);

        cbSolut = new ComboBoxForDB(gbLog);
        cbSolut->setObjectName(QString::fromUtf8("cbSolut"));

        gridLayout_5->addWidget(cbSolut, 5, 1, 1, 2);

        rbUnnormalLog = new QRadioButton(gbLog);
        rbUnnormalLog->setObjectName(QString::fromUtf8("rbUnnormalLog"));

        gridLayout_5->addWidget(rbUnnormalLog, 8, 0, 1, 3);

        label_19 = new QLabel(gbLog);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        gridLayout_5->addWidget(label_19, 6, 0, 1, 1);

        CurrDTPaste = new QPushButton(gbLog);
        CurrDTPaste->setObjectName(QString::fromUtf8("CurrDTPaste"));
        CurrDTPaste->setMaximumSize(QSize(50, 30));

        gridLayout_5->addWidget(CurrDTPaste, 0, 2, 1, 1);

        leDescriptLog = new QTextEdit(gbLog);
        leDescriptLog->setObjectName(QString::fromUtf8("leDescriptLog"));

        gridLayout_5->addWidget(leDescriptLog, 10, 0, 1, 3);

        dtSolutExec = new QDateTimeEdit(gbLog);
        dtSolutExec->setObjectName(QString::fromUtf8("dtSolutExec"));
        dtSolutExec->setMinimumSize(QSize(100, 0));
        dtSolutExec->setDateTime(QDateTime(QDate(1752, 9, 14), QTime(0, 0, 0)));
        dtSolutExec->setCalendarPopup(true);

        gridLayout_5->addWidget(dtSolutExec, 6, 1, 1, 1);

        SolDTPaste = new QPushButton(gbLog);
        SolDTPaste->setObjectName(QString::fromUtf8("SolDTPaste"));
        SolDTPaste->setMaximumSize(QSize(50, 30));

        gridLayout_5->addWidget(SolDTPaste, 6, 2, 1, 1);

        cbEquip = new ComboBoxForDB(gbLog);
        cbEquip->setObjectName(QString::fromUtf8("cbEquip"));

        gridLayout_5->addWidget(cbEquip, 2, 1, 1, 2);

        cbBreak = new ComboBoxForDB(gbLog);
        cbBreak->setObjectName(QString::fromUtf8("cbBreak"));

        gridLayout_5->addWidget(cbBreak, 4, 1, 1, 2);

        label_17 = new QLabel(gbLog);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        gridLayout_5->addWidget(label_17, 4, 0, 1, 1);

        label_16 = new QLabel(gbLog);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        gridLayout_5->addWidget(label_16, 3, 0, 1, 1);

        label_18 = new QLabel(gbLog);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        gridLayout_5->addWidget(label_18, 5, 0, 1, 1);

        cbCond = new ComboBoxForDB(gbLog);
        cbCond->setObjectName(QString::fromUtf8("cbCond"));

        gridLayout_5->addWidget(cbCond, 3, 1, 1, 2);

        ledtSolutExec = new QLineEdit(gbLog);
        ledtSolutExec->setObjectName(QString::fromUtf8("ledtSolutExec"));
        ledtSolutExec->setEnabled(false);

        gridLayout_5->addWidget(ledtSolutExec, 7, 1, 1, 1);

        SolDTDelete = new QPushButton(gbLog);
        SolDTDelete->setObjectName(QString::fromUtf8("SolDTDelete"));
        SolDTDelete->setMaximumSize(QSize(50, 30));

        gridLayout_5->addWidget(SolDTDelete, 7, 2, 1, 1);


        gridLayout_6->addLayout(gridLayout_5, 0, 0, 1, 1);


        retranslateUi(Edit);

        QMetaObject::connectSlotsByName(Edit);
    } // setupUi

    void retranslateUi(QWidget *Edit)
    {
        Edit->setWindowTitle(QApplication::translate("Edit", "\320\240\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\320\275\320\270\320\265", nullptr));
        gbEquip->setTitle(QApplication::translate("Edit", "\320\236\320\261\320\276\321\200\321\203\320\264\320\276\320\262\320\260\320\275\320\270\320\265", nullptr));
        label->setText(QApplication::translate("Edit", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265", nullptr));
        label_3->setText(QApplication::translate("Edit", "\320\236\320\277\320\270\321\201\320\260\320\275\320\270\320\265", nullptr));
        label_2->setText(QApplication::translate("Edit", "\320\222\321\205\320\276\320\264\320\270\321\202 \320\262", nullptr));
        gbCond->setTitle(QApplication::translate("Edit", "\320\241\320\276\321\201\321\202\320\276\321\217\320\275\320\270\320\265", nullptr));
        label_4->setText(QApplication::translate("Edit", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265", nullptr));
        label_5->setText(QApplication::translate("Edit", "\320\235\320\260\320\263\321\200\321\203\320\267\320\272\320\260(%)", nullptr));
        Apply->setText(QApplication::translate("Edit", "\320\237\320\276\320\264\321\202\320\262\320\265\321\200\320\264\320\270\321\202\321\214", nullptr));
        Delete->setText(QApplication::translate("Edit", "\320\236\321\202\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        btLogFile->setText(QApplication::translate("Edit", "\320\244\320\260\320\271\320\273\321\213", nullptr));
        gbSolution->setTitle(QApplication::translate("Edit", "\320\240\320\265\321\210\320\265\320\275\320\270\320\265", nullptr));
        label_6->setText(QApplication::translate("Edit", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265", nullptr));
        label_7->setText(QApplication::translate("Edit", "\320\236\320\277\320\270\321\201\320\260\320\275\320\270\320\265", nullptr));
        gbBreak->setTitle(QApplication::translate("Edit", "\320\236\321\210\320\270\320\261\320\272\320\260", nullptr));
        label_8->setText(QApplication::translate("Edit", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265", nullptr));
        label_9->setText(QApplication::translate("Edit", "\320\236\320\277\320\270\321\201\320\260\320\275\320\270\320\265", nullptr));
        label_10->setText(QApplication::translate("Edit", "\320\232\320\276\320\264", nullptr));
        gbLog->setTitle(QApplication::translate("Edit", "\320\241\320\276\321\201\321\202\320\276\321\217\320\275\320\270\320\265 \320\276\320\261\320\276\321\200\321\203\320\264\320\276\320\262\320\260\320\275\320\270\321\217", nullptr));
        label_14->setText(QApplication::translate("Edit", "<html><head/><body><p>\320\224\320\260\321\202\320\260 \320\270 \320\262\321\200\320\265\320\274\321\217 <br/>\321\201\320\275\321\217\321\202\320\270\321\217 \320\277\320\276\320\272\320\260\320\267\320\260\320\275\320\270\320\271</p></body></html>", nullptr));
        dtCurrTime->setDisplayFormat(QApplication::translate("Edit", "dd.MM.yyyy HH:mm:ss", nullptr));
        label_15->setText(QApplication::translate("Edit", "\320\236\320\261\320\276\321\200\321\203\320\264\320\276\320\262\320\260\320\275\320\270\320\265", nullptr));
        label_11->setText(QApplication::translate("Edit", "\320\236\320\277\320\270\321\201\320\260\320\275\320\270\320\265", nullptr));
        rbUnnormalLog->setText(QApplication::translate("Edit", "\320\236\321\202\320\272\320\273\320\276\320\275\320\265\320\275\320\270\320\265 \320\276\321\202 \320\275\320\276\321\200\320\274\321\213", nullptr));
        label_19->setText(QApplication::translate("Edit", "<html><head/><body><p>\320\224\320\260\321\202\320\260 \320\270 \320\262\321\200\320\265\320\274\321\217<br/>\321\200\320\265\321\210\320\265\320\275\320\270\321\217</p></body></html>", nullptr));
        CurrDTPaste->setText(QApplication::translate("Edit", "\320\222\321\201\321\202\320\260\320\262\320\270\321\202\321\214\n"
"\321\202\320\265\320\272\321\203\321\211\320\265\320\265", nullptr));
        dtSolutExec->setDisplayFormat(QApplication::translate("Edit", "dd.MM.yyyy HH:mm", nullptr));
        SolDTPaste->setText(QApplication::translate("Edit", "\320\222\321\201\321\202\320\260\320\262\320\270\321\202\321\214\n"
"\321\202\320\265\320\272\321\203\321\211\320\265\320\265", nullptr));
        label_17->setText(QApplication::translate("Edit", "\320\236\321\210\320\270\320\261\320\272\320\260", nullptr));
        label_16->setText(QApplication::translate("Edit", "\320\241\320\276\321\201\321\202\320\276\321\217\320\275\320\270\320\265", nullptr));
        label_18->setText(QApplication::translate("Edit", "\320\240\320\265\321\210\320\265\320\275\320\270\320\265", nullptr));
        ledtSolutExec->setText(QApplication::translate("Edit", "NULL", nullptr));
        SolDTDelete->setText(QApplication::translate("Edit", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214\n"
"\320\262\321\200\320\265\320\274\321\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Edit: public Ui_Edit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDIT_H
