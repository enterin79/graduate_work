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
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "comboboxfordb.h"

QT_BEGIN_NAMESPACE

class Ui_Edit
{
public:
    QGroupBox *gbBlok;
    QGridLayout *gridLayout_2;
    QFormLayout *formLayout_2;
    QLabel *label_12;
    ComboBoxForDB *cbBlokKA;
    QLabel *label_2;
    ComboBoxForDB *cbBlokBI;
    QLabel *label;
    QLineEdit *leNameBlok;
    QLineEdit *leBlokBISerial;
    QLineEdit *leBlokBISerialCurr;
    QLineEdit *leBlokSerial;
    QLabel *label_3;
    QGroupBox *gbParm;
    QGridLayout *gridLayout_3;
    QFormLayout *formLayout;
    QPlainTextEdit *leDescriptParm;
    QLineEdit *leNameParm;
    QLabel *label_4;
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
    QGroupBox *gbKA;
    QGridLayout *gridLayout;
    QFormLayout *formLayout_4;
    QLabel *label_10;
    QLineEdit *leNumberKA;
    QLabel *label_8;
    QLineEdit *leNameKA;
    QDateTimeEdit *dtLaunchKA;
    QLabel *label_9;
    QGroupBox *gbLog;
    QGridLayout *gridLayout_6;
    QGridLayout *gridLayout_5;
    QLineEdit *ledtSolutExec;
    QDateTimeEdit *dtCurrTime;
    QLabel *label_15;
    QLabel *label_11;
    QDateTimeEdit *dtSolutExec;
    QLabel *label_18;
    ComboBoxForDB *cbEquip;
    QPushButton *CurrDTPaste;
    QPushButton *SolDTDelete;
    QLabel *label_14;
    QLabel *label_19;
    ComboBoxForDB *cbSolut;
    QPushButton *SolDTPaste;
    QTextEdit *leDescriptLog;
    QGroupBox *gbBI;
    QGridLayout *gridLayout_7;
    QFormLayout *formLayout_5;
    QLabel *label_13;
    ComboBoxForDB *cbBIKA;
    QLabel *label_16;
    QLineEdit *leNameBI;
    QLineEdit *leBISerial;
    QLabel *label_17;
    QGroupBox *gbFile;
    QVBoxLayout *verticalLayout;
    QTextEdit *leFilePath;
    QPushButton *ChooseFile;

    void setupUi(QWidget *Edit)
    {
        if (Edit->objectName().isEmpty())
            Edit->setObjectName(QString::fromUtf8("Edit"));
        Edit->resize(281, 314);
        Edit->setMinimumSize(QSize(281, 314));
        Edit->setMaximumSize(QSize(281, 314));
        gbBlok = new QGroupBox(Edit);
        gbBlok->setObjectName(QString::fromUtf8("gbBlok"));
        gbBlok->setGeometry(QRect(10, 10, 261, 261));
        gridLayout_2 = new QGridLayout(gbBlok);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        label_12 = new QLabel(gbBlok);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_12);

        cbBlokKA = new ComboBoxForDB(gbBlok);
        cbBlokKA->setObjectName(QString::fromUtf8("cbBlokKA"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, cbBlokKA);

        label_2 = new QLabel(gbBlok);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_2);

        cbBlokBI = new ComboBoxForDB(gbBlok);
        cbBlokBI->setObjectName(QString::fromUtf8("cbBlokBI"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, cbBlokBI);

        label = new QLabel(gbBlok);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout_2->setWidget(5, QFormLayout::LabelRole, label);

        leNameBlok = new QLineEdit(gbBlok);
        leNameBlok->setObjectName(QString::fromUtf8("leNameBlok"));
        leNameBlok->setMaxLength(50);

        formLayout_2->setWidget(5, QFormLayout::FieldRole, leNameBlok);

        leBlokBISerial = new QLineEdit(gbBlok);
        leBlokBISerial->setObjectName(QString::fromUtf8("leBlokBISerial"));
        leBlokBISerial->setEnabled(false);

        formLayout_2->setWidget(4, QFormLayout::FieldRole, leBlokBISerial);

        leBlokBISerialCurr = new QLineEdit(gbBlok);
        leBlokBISerialCurr->setObjectName(QString::fromUtf8("leBlokBISerialCurr"));
        leBlokBISerialCurr->setEnabled(false);

        formLayout_2->setWidget(3, QFormLayout::FieldRole, leBlokBISerialCurr);

        leBlokSerial = new QLineEdit(gbBlok);
        leBlokSerial->setObjectName(QString::fromUtf8("leBlokSerial"));
        leBlokSerial->setMaxLength(15);

        formLayout_2->setWidget(2, QFormLayout::FieldRole, leBlokSerial);

        label_3 = new QLabel(gbBlok);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_3);


        gridLayout_2->addLayout(formLayout_2, 0, 0, 1, 1);

        gbParm = new QGroupBox(Edit);
        gbParm->setObjectName(QString::fromUtf8("gbParm"));
        gbParm->setGeometry(QRect(10, 10, 261, 261));
        gridLayout_3 = new QGridLayout(gbParm);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        leDescriptParm = new QPlainTextEdit(gbParm);
        leDescriptParm->setObjectName(QString::fromUtf8("leDescriptParm"));

        formLayout->setWidget(1, QFormLayout::FieldRole, leDescriptParm);

        leNameParm = new QLineEdit(gbParm);
        leNameParm->setObjectName(QString::fromUtf8("leNameParm"));
        leNameParm->setMaxLength(50);

        formLayout->setWidget(0, QFormLayout::FieldRole, leNameParm);

        label_4 = new QLabel(gbParm);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_4);

        label_5 = new QLabel(gbParm);
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
        leNameSolut->setMaxLength(50);

        formLayout_3->setWidget(0, QFormLayout::FieldRole, leNameSolut);

        leDescriptSolut = new QTextEdit(gbSolution);
        leDescriptSolut->setObjectName(QString::fromUtf8("leDescriptSolut"));

        formLayout_3->setWidget(1, QFormLayout::FieldRole, leDescriptSolut);

        label_7 = new QLabel(gbSolution);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        formLayout_3->setWidget(1, QFormLayout::LabelRole, label_7);


        gridLayout_4->addLayout(formLayout_3, 0, 0, 1, 1);

        gbKA = new QGroupBox(Edit);
        gbKA->setObjectName(QString::fromUtf8("gbKA"));
        gbKA->setGeometry(QRect(10, 10, 261, 261));
        gridLayout = new QGridLayout(gbKA);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        formLayout_4 = new QFormLayout();
        formLayout_4->setObjectName(QString::fromUtf8("formLayout_4"));
        label_10 = new QLabel(gbKA);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        formLayout_4->setWidget(0, QFormLayout::LabelRole, label_10);

        leNumberKA = new QLineEdit(gbKA);
        leNumberKA->setObjectName(QString::fromUtf8("leNumberKA"));
        leNumberKA->setMaxLength(3);

        formLayout_4->setWidget(0, QFormLayout::FieldRole, leNumberKA);

        label_8 = new QLabel(gbKA);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        formLayout_4->setWidget(1, QFormLayout::LabelRole, label_8);

        leNameKA = new QLineEdit(gbKA);
        leNameKA->setObjectName(QString::fromUtf8("leNameKA"));
        leNameKA->setMaxLength(50);

        formLayout_4->setWidget(1, QFormLayout::FieldRole, leNameKA);

        dtLaunchKA = new QDateTimeEdit(gbKA);
        dtLaunchKA->setObjectName(QString::fromUtf8("dtLaunchKA"));
        dtLaunchKA->setCalendarPopup(true);

        formLayout_4->setWidget(2, QFormLayout::FieldRole, dtLaunchKA);

        label_9 = new QLabel(gbKA);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        formLayout_4->setWidget(2, QFormLayout::LabelRole, label_9);


        gridLayout->addLayout(formLayout_4, 0, 0, 1, 1);

        gbLog = new QGroupBox(Edit);
        gbLog->setObjectName(QString::fromUtf8("gbLog"));
        gbLog->setGeometry(QRect(10, 10, 261, 261));
        gridLayout_6 = new QGridLayout(gbLog);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        ledtSolutExec = new QLineEdit(gbLog);
        ledtSolutExec->setObjectName(QString::fromUtf8("ledtSolutExec"));
        ledtSolutExec->setEnabled(false);

        gridLayout_5->addWidget(ledtSolutExec, 5, 1, 1, 1);

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

        gridLayout_5->addWidget(label_11, 6, 1, 1, 1);

        dtSolutExec = new QDateTimeEdit(gbLog);
        dtSolutExec->setObjectName(QString::fromUtf8("dtSolutExec"));
        dtSolutExec->setMinimumSize(QSize(100, 0));
        dtSolutExec->setDateTime(QDateTime(QDate(1900, 9, 14), QTime(0, 0, 0)));
        dtSolutExec->setMinimumDateTime(QDateTime(QDate(1900, 1, 1), QTime(0, 0, 0)));
        dtSolutExec->setCalendarPopup(true);

        gridLayout_5->addWidget(dtSolutExec, 4, 1, 1, 1);

        label_18 = new QLabel(gbLog);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        gridLayout_5->addWidget(label_18, 3, 0, 1, 1);

        cbEquip = new ComboBoxForDB(gbLog);
        cbEquip->setObjectName(QString::fromUtf8("cbEquip"));

        gridLayout_5->addWidget(cbEquip, 2, 1, 1, 2);

        CurrDTPaste = new QPushButton(gbLog);
        CurrDTPaste->setObjectName(QString::fromUtf8("CurrDTPaste"));
        CurrDTPaste->setMaximumSize(QSize(50, 30));

        gridLayout_5->addWidget(CurrDTPaste, 0, 2, 1, 1);

        SolDTDelete = new QPushButton(gbLog);
        SolDTDelete->setObjectName(QString::fromUtf8("SolDTDelete"));
        SolDTDelete->setMaximumSize(QSize(50, 30));

        gridLayout_5->addWidget(SolDTDelete, 5, 2, 1, 1);

        label_14 = new QLabel(gbLog);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout_5->addWidget(label_14, 0, 0, 1, 1);

        label_19 = new QLabel(gbLog);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        gridLayout_5->addWidget(label_19, 4, 0, 1, 1);

        cbSolut = new ComboBoxForDB(gbLog);
        cbSolut->setObjectName(QString::fromUtf8("cbSolut"));

        gridLayout_5->addWidget(cbSolut, 3, 1, 1, 2);

        SolDTPaste = new QPushButton(gbLog);
        SolDTPaste->setObjectName(QString::fromUtf8("SolDTPaste"));
        SolDTPaste->setMaximumSize(QSize(50, 30));

        gridLayout_5->addWidget(SolDTPaste, 4, 2, 1, 1);

        leDescriptLog = new QTextEdit(gbLog);
        leDescriptLog->setObjectName(QString::fromUtf8("leDescriptLog"));

        gridLayout_5->addWidget(leDescriptLog, 7, 0, 1, 3);


        gridLayout_6->addLayout(gridLayout_5, 0, 0, 1, 1);

        gbBI = new QGroupBox(Edit);
        gbBI->setObjectName(QString::fromUtf8("gbBI"));
        gbBI->setGeometry(QRect(10, 10, 261, 261));
        gridLayout_7 = new QGridLayout(gbBI);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        formLayout_5 = new QFormLayout();
        formLayout_5->setObjectName(QString::fromUtf8("formLayout_5"));
        label_13 = new QLabel(gbBI);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        formLayout_5->setWidget(0, QFormLayout::LabelRole, label_13);

        cbBIKA = new ComboBoxForDB(gbBI);
        cbBIKA->setObjectName(QString::fromUtf8("cbBIKA"));

        formLayout_5->setWidget(0, QFormLayout::FieldRole, cbBIKA);

        label_16 = new QLabel(gbBI);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        formLayout_5->setWidget(2, QFormLayout::LabelRole, label_16);

        leNameBI = new QLineEdit(gbBI);
        leNameBI->setObjectName(QString::fromUtf8("leNameBI"));
        leNameBI->setMaxLength(50);

        formLayout_5->setWidget(2, QFormLayout::FieldRole, leNameBI);

        leBISerial = new QLineEdit(gbBI);
        leBISerial->setObjectName(QString::fromUtf8("leBISerial"));
        leBISerial->setMaxLength(15);

        formLayout_5->setWidget(1, QFormLayout::FieldRole, leBISerial);

        label_17 = new QLabel(gbBI);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        formLayout_5->setWidget(1, QFormLayout::LabelRole, label_17);


        gridLayout_7->addLayout(formLayout_5, 0, 0, 1, 1);

        gbFile = new QGroupBox(Edit);
        gbFile->setObjectName(QString::fromUtf8("gbFile"));
        gbFile->setGeometry(QRect(10, 10, 261, 261));
        verticalLayout = new QVBoxLayout(gbFile);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        leFilePath = new QTextEdit(gbFile);
        leFilePath->setObjectName(QString::fromUtf8("leFilePath"));
        leFilePath->setReadOnly(true);

        verticalLayout->addWidget(leFilePath);

        ChooseFile = new QPushButton(gbFile);
        ChooseFile->setObjectName(QString::fromUtf8("ChooseFile"));

        verticalLayout->addWidget(ChooseFile);


        retranslateUi(Edit);

        QMetaObject::connectSlotsByName(Edit);
    } // setupUi

    void retranslateUi(QWidget *Edit)
    {
        Edit->setWindowTitle(QApplication::translate("Edit", "\320\240\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\320\275\320\270\320\265", nullptr));
        gbBlok->setTitle(QApplication::translate("Edit", "\320\221\320\273\320\276\320\272", nullptr));
        label_12->setText(QApplication::translate("Edit", "\320\232\320\220", nullptr));
        label_2->setText(QApplication::translate("Edit", "\320\221\320\230", nullptr));
        label->setText(QApplication::translate("Edit", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265", nullptr));
        leBlokBISerial->setText(QApplication::translate("Edit", "NULL", nullptr));
        label_3->setText(QApplication::translate("Edit", "\320\241\320\265\321\200\320\270\320\271\320\275\321\213\320\271\n"
"\320\275\320\276\320\274\320\265\321\200", nullptr));
        gbParm->setTitle(QApplication::translate("Edit", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200", nullptr));
        label_4->setText(QApplication::translate("Edit", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265", nullptr));
        label_5->setText(QApplication::translate("Edit", "\320\236\320\277\320\270\321\201\320\260\320\275\320\270\320\265", nullptr));
        Apply->setText(QApplication::translate("Edit", "\320\237\320\276\320\264\321\202\320\262\320\265\321\200\320\264\320\270\321\202\321\214", nullptr));
        Delete->setText(QApplication::translate("Edit", "\320\236\321\202\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        btLogFile->setText(QApplication::translate("Edit", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213", nullptr));
        gbSolution->setTitle(QApplication::translate("Edit", "\320\240\320\265\321\210\320\265\320\275\320\270\320\265", nullptr));
        label_6->setText(QApplication::translate("Edit", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265", nullptr));
        label_7->setText(QApplication::translate("Edit", "\320\236\320\277\320\270\321\201\320\260\320\275\320\270\320\265", nullptr));
        gbKA->setTitle(QApplication::translate("Edit", "\320\232\320\276\321\201\320\274\320\270\321\207\320\265\321\201\320\272\320\270\320\271 \320\260\320\277\320\277\320\260\321\200\320\260\321\202", nullptr));
        label_10->setText(QApplication::translate("Edit", "\320\232\320\276\320\264", nullptr));
        label_8->setText(QApplication::translate("Edit", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265", nullptr));
        label_9->setText(QApplication::translate("Edit", "\320\224\320\260\321\202\320\260 \320\267\320\260\320\277\321\203\321\201\320\272\320\260", nullptr));
        gbLog->setTitle(QApplication::translate("Edit", "\320\241\320\276\321\201\321\202\320\276\321\217\320\275\320\270\320\265 \320\276\320\261\320\276\321\200\321\203\320\264\320\276\320\262\320\260\320\275\320\270\321\217", nullptr));
        ledtSolutExec->setText(QApplication::translate("Edit", "NULL", nullptr));
        dtCurrTime->setDisplayFormat(QApplication::translate("Edit", "dd.MM.yyyy HH:mm:ss", nullptr));
        label_15->setText(QApplication::translate("Edit", "\320\236\320\261\320\276\321\200\321\203\320\264\320\276\320\262\320\260\320\275\320\270\320\265", nullptr));
        label_11->setText(QApplication::translate("Edit", "\320\236\320\277\320\270\321\201\320\260\320\275\320\270\320\265", nullptr));
        dtSolutExec->setDisplayFormat(QApplication::translate("Edit", "dd.MM.yyyy HH:mm", nullptr));
        label_18->setText(QApplication::translate("Edit", "\320\240\320\265\321\210\320\265\320\275\320\270\320\265", nullptr));
        CurrDTPaste->setText(QApplication::translate("Edit", "\320\222\321\201\321\202\320\260\320\262\320\270\321\202\321\214\n"
"\321\202\320\265\320\272\321\203\321\211\320\265\320\265", nullptr));
        SolDTDelete->setText(QApplication::translate("Edit", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214\n"
"\320\262\321\200\320\265\320\274\321\217", nullptr));
        label_14->setText(QApplication::translate("Edit", "<html><head/><body><p>\320\224\320\260\321\202\320\260 \320\270 \320\262\321\200\320\265\320\274\321\217 <br/>\321\201\320\275\321\217\321\202\320\270\321\217 \320\277\320\276\320\272\320\260\320\267\320\260\320\275\320\270\320\271</p></body></html>", nullptr));
        label_19->setText(QApplication::translate("Edit", "<html><head/><body><p>\320\224\320\260\321\202\320\260 \320\270 \320\262\321\200\320\265\320\274\321\217<br/>\321\200\320\265\321\210\320\265\320\275\320\270\321\217</p></body></html>", nullptr));
        SolDTPaste->setText(QApplication::translate("Edit", "\320\222\321\201\321\202\320\260\320\262\320\270\321\202\321\214\n"
"\321\202\320\265\320\272\321\203\321\211\320\265\320\265", nullptr));
        gbBI->setTitle(QApplication::translate("Edit", "\320\221\320\276\321\200\321\202\320\276\320\262\320\276\320\265 \320\270\320\267\320\264\320\265\320\273\320\270\320\265", nullptr));
        label_13->setText(QApplication::translate("Edit", "\320\232\320\220", nullptr));
        label_16->setText(QApplication::translate("Edit", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265", nullptr));
        label_17->setText(QApplication::translate("Edit", "\320\241\320\265\321\200\320\270\320\271\320\275\321\213\320\271\n"
"\320\275\320\276\320\274\320\265\321\200", nullptr));
        gbFile->setTitle(QApplication::translate("Edit", "\320\244\320\260\320\271\320\273", nullptr));
        ChooseFile->setText(QApplication::translate("Edit", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214 \321\204\320\260\320\271\320\273", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Edit: public Ui_Edit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDIT_H
