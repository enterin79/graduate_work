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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_filelog
{
public:
    QTextEdit *textEdit;
    QPushButton *selectFile;
    QTableView *tvFiles;
    QPushButton *openFile;

    void setupUi(QWidget *filelog)
    {
        if (filelog->objectName().isEmpty())
            filelog->setObjectName(QString::fromUtf8("filelog"));
        filelog->resize(400, 300);
        textEdit = new QTextEdit(filelog);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(10, 60, 104, 70));
        selectFile = new QPushButton(filelog);
        selectFile->setObjectName(QString::fromUtf8("selectFile"));
        selectFile->setGeometry(QRect(10, 20, 80, 22));
        tvFiles = new QTableView(filelog);
        tvFiles->setObjectName(QString::fromUtf8("tvFiles"));
        tvFiles->setGeometry(QRect(130, 60, 256, 192));
        tvFiles->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tvFiles->setSortingEnabled(true);
        tvFiles->horizontalHeader()->setVisible(false);
        tvFiles->horizontalHeader()->setStretchLastSection(false);
        openFile = new QPushButton(filelog);
        openFile->setObjectName(QString::fromUtf8("openFile"));
        openFile->setGeometry(QRect(130, 260, 80, 22));

        retranslateUi(filelog);

        QMetaObject::connectSlotsByName(filelog);
    } // setupUi

    void retranslateUi(QWidget *filelog)
    {
        filelog->setWindowTitle(QApplication::translate("filelog", "Form", nullptr));
        selectFile->setText(QApplication::translate("filelog", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214 \321\204\320\260\320\271\320\273", nullptr));
        openFile->setText(QApplication::translate("filelog", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class filelog: public Ui_filelog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILELOG_H
