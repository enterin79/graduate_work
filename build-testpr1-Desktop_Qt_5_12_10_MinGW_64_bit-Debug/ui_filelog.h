/********************************************************************************
** Form generated from reading UI file 'filelog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILELOG_H
#define UI_FILELOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>
#include "comboboxfordb.h"

QT_BEGIN_NAMESPACE

class Ui_filelog
{
public:
    QGridLayout *gridLayout;
    QLabel *lrownum;
    QLabel *label;
    QComboBox *cbCondParm;
    QLineEdit *leLogID;
    ComboBoxForDB *cbNameParm;
    QLineEdit *leFiletableID;
    QPlainTextEdit *leFileParm;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *newRow;
    QPushButton *selectFile;
    QPushButton *saveParm;
    QLabel *label_3;
    QPushButton *deleteFile;
    QPushButton *copy;
    QPushButton *openFile;
    QTableView *tvFiles;

    void setupUi(QWidget *filelog)
    {
        if (filelog->objectName().isEmpty())
            filelog->setObjectName(QString::fromUtf8("filelog"));
        filelog->resize(600, 300);
        filelog->setMinimumSize(QSize(600, 300));
        filelog->setMaximumSize(QSize(600, 300));
        gridLayout = new QGridLayout(filelog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        lrownum = new QLabel(filelog);
        lrownum->setObjectName(QString::fromUtf8("lrownum"));
        lrownum->setMaximumSize(QSize(200, 16777215));

        gridLayout->addWidget(lrownum, 3, 9, 1, 1);

        label = new QLabel(filelog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(55, 20));
        label->setMaximumSize(QSize(55, 20));

        gridLayout->addWidget(label, 4, 8, 1, 1);

        cbCondParm = new QComboBox(filelog);
        cbCondParm->setObjectName(QString::fromUtf8("cbCondParm"));
        cbCondParm->setMaximumSize(QSize(200, 16777215));

        gridLayout->addWidget(cbCondParm, 6, 9, 1, 1);

        leLogID = new QLineEdit(filelog);
        leLogID->setObjectName(QString::fromUtf8("leLogID"));
        leLogID->setEnabled(false);
        leLogID->setMinimumSize(QSize(0, 0));
        leLogID->setMaximumSize(QSize(55, 16777215));

        gridLayout->addWidget(leLogID, 3, 8, 1, 1);

        cbNameParm = new ComboBoxForDB(filelog);
        cbNameParm->setObjectName(QString::fromUtf8("cbNameParm"));
        cbNameParm->setMaximumSize(QSize(200, 16777215));

        gridLayout->addWidget(cbNameParm, 4, 9, 1, 1);

        leFiletableID = new QLineEdit(filelog);
        leFiletableID->setObjectName(QString::fromUtf8("leFiletableID"));
        leFiletableID->setEnabled(false);
        leFiletableID->setMaximumSize(QSize(200, 16777215));

        gridLayout->addWidget(leFiletableID, 12, 9, 1, 1);

        leFileParm = new QPlainTextEdit(filelog);
        leFileParm->setObjectName(QString::fromUtf8("leFileParm"));
        leFileParm->setMaximumSize(QSize(200, 16777215));
        leFileParm->setReadOnly(true);

        gridLayout->addWidget(leFileParm, 8, 9, 1, 1);

        label_2 = new QLabel(filelog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(55, 20));
        label_2->setMaximumSize(QSize(55, 20));

        gridLayout->addWidget(label_2, 6, 8, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        newRow = new QPushButton(filelog);
        newRow->setObjectName(QString::fromUtf8("newRow"));

        horizontalLayout_2->addWidget(newRow);

        selectFile = new QPushButton(filelog);
        selectFile->setObjectName(QString::fromUtf8("selectFile"));

        horizontalLayout_2->addWidget(selectFile);

        saveParm = new QPushButton(filelog);
        saveParm->setObjectName(QString::fromUtf8("saveParm"));

        horizontalLayout_2->addWidget(saveParm);


        gridLayout->addLayout(horizontalLayout_2, 13, 8, 1, 2);

        label_3 = new QLabel(filelog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(55, 20));
        label_3->setMaximumSize(QSize(55, 20));

        gridLayout->addWidget(label_3, 8, 8, 1, 1);

        deleteFile = new QPushButton(filelog);
        deleteFile->setObjectName(QString::fromUtf8("deleteFile"));

        gridLayout->addWidget(deleteFile, 13, 3, 1, 1);

        copy = new QPushButton(filelog);
        copy->setObjectName(QString::fromUtf8("copy"));

        gridLayout->addWidget(copy, 13, 2, 1, 1);

        openFile = new QPushButton(filelog);
        openFile->setObjectName(QString::fromUtf8("openFile"));

        gridLayout->addWidget(openFile, 13, 1, 1, 1);

        tvFiles = new QTableView(filelog);
        tvFiles->setObjectName(QString::fromUtf8("tvFiles"));
        tvFiles->setEnabled(true);
        tvFiles->setAutoScroll(true);
        tvFiles->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tvFiles->setSortingEnabled(true);
        tvFiles->setWordWrap(true);
        tvFiles->horizontalHeader()->setVisible(false);
        tvFiles->horizontalHeader()->setStretchLastSection(true);
        tvFiles->verticalHeader()->setVisible(false);

        gridLayout->addWidget(tvFiles, 1, 0, 12, 8);


        retranslateUi(filelog);

        QMetaObject::connectSlotsByName(filelog);
    } // setupUi

    void retranslateUi(QWidget *filelog)
    {
        filelog->setWindowTitle(QApplication::translate("filelog", "\320\237\321\200\320\270\320\272\321\200\320\265\320\277\320\273\320\265\320\275\320\275\321\213\320\265 \321\204\320\260\320\271\320\273\321\213", nullptr));
        lrownum->setText(QApplication::translate("filelog", "TextLabel", nullptr));
        label->setText(QApplication::translate("filelog", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200", nullptr));
        leLogID->setText(QApplication::translate("filelog", "NULL", nullptr));
        leFiletableID->setText(QApplication::translate("filelog", "NULL", nullptr));
        label_2->setText(QApplication::translate("filelog", "\320\241\320\276\321\201\321\202\320\276\321\217\320\275\320\270\320\265", nullptr));
        newRow->setText(QApplication::translate("filelog", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214", nullptr));
        selectFile->setText(QApplication::translate("filelog", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214 \321\204\320\260\320\271\320\273", nullptr));
        saveParm->setText(QApplication::translate("filelog", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        label_3->setText(QApplication::translate("filelog", "\320\244\320\260\320\271\320\273", nullptr));
        deleteFile->setText(QApplication::translate("filelog", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        copy->setText(QApplication::translate("filelog", "\320\232\320\276\320\277\320\270\321\200\320\276\320\262\320\260\321\202\321\214\n"
"\320\277\321\203\321\202\321\214", nullptr));
        openFile->setText(QApplication::translate("filelog", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214\n"
"\321\204\320\260\320\271\320\273", nullptr));
    } // retranslateUi

};

namespace Ui {
    class filelog: public Ui_filelog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILELOG_H
