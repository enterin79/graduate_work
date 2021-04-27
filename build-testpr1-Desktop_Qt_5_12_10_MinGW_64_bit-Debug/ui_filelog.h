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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_filelog
{
public:
    QGridLayout *gridLayout;
    QPushButton *openFile;
    QTableView *tvFiles;
    QPushButton *deleteFile;
    QPushButton *selectFile;
    QPushButton *copy;

    void setupUi(QWidget *filelog)
    {
        if (filelog->objectName().isEmpty())
            filelog->setObjectName(QString::fromUtf8("filelog"));
        filelog->resize(300, 300);
        filelog->setMinimumSize(QSize(300, 300));
        filelog->setMaximumSize(QSize(300, 300));
        gridLayout = new QGridLayout(filelog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        openFile = new QPushButton(filelog);
        openFile->setObjectName(QString::fromUtf8("openFile"));

        gridLayout->addWidget(openFile, 2, 0, 1, 1);

        tvFiles = new QTableView(filelog);
        tvFiles->setObjectName(QString::fromUtf8("tvFiles"));
        tvFiles->setAutoScroll(true);
        tvFiles->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tvFiles->setSortingEnabled(true);
        tvFiles->setWordWrap(true);
        tvFiles->horizontalHeader()->setVisible(false);
        tvFiles->horizontalHeader()->setStretchLastSection(true);

        gridLayout->addWidget(tvFiles, 1, 0, 1, 3);

        deleteFile = new QPushButton(filelog);
        deleteFile->setObjectName(QString::fromUtf8("deleteFile"));

        gridLayout->addWidget(deleteFile, 2, 2, 1, 1);

        selectFile = new QPushButton(filelog);
        selectFile->setObjectName(QString::fromUtf8("selectFile"));

        gridLayout->addWidget(selectFile, 0, 0, 1, 1);

        copy = new QPushButton(filelog);
        copy->setObjectName(QString::fromUtf8("copy"));

        gridLayout->addWidget(copy, 2, 1, 1, 1);


        retranslateUi(filelog);

        QMetaObject::connectSlotsByName(filelog);
    } // setupUi

    void retranslateUi(QWidget *filelog)
    {
        filelog->setWindowTitle(QApplication::translate("filelog", "\320\237\321\200\320\270\320\272\321\200\320\265\320\277\320\273\320\265\320\275\320\275\321\213\320\265 \321\204\320\260\320\271\320\273\321\213", nullptr));
        openFile->setText(QApplication::translate("filelog", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214", nullptr));
        deleteFile->setText(QApplication::translate("filelog", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        selectFile->setText(QApplication::translate("filelog", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \321\204\320\260\320\271\320\273", nullptr));
        copy->setText(QApplication::translate("filelog", "\320\232\320\276\320\277\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class filelog: public Ui_filelog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILELOG_H
