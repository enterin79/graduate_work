/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include "comboboxfordb.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *layoutWidget;
    QFormLayout *formLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *cbChooseTable;
    QSpacerItem *horizontalSpacer_2;
    QTableView *tvModel;
    QFormLayout *formLayout_2;
    QPushButton *SaveButton;
    QPushButton *RevertButton;
    QPushButton *Add;
    QPushButton *Delete;
    QSpacerItem *horizontalSpacer;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    QFormLayout *formLayout;
    QLabel *label_2;
    ComboBoxForDB *cbSelectColumn;
    QTextEdit *teDecript;
    QPushButton *Search;
    QPushButton *RevertTable;
    QLabel *label_3;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(750, 300);
        MainWindow->setMinimumSize(QSize(750, 300));
        MainWindow->setMaximumSize(QSize(750, 300));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 481, 341));
        formLayout_3 = new QFormLayout(layoutWidget);
        formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
        formLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        cbChooseTable = new QComboBox(layoutWidget);
        cbChooseTable->setObjectName(QString::fromUtf8("cbChooseTable"));

        horizontalLayout->addWidget(cbChooseTable);


        formLayout_3->setLayout(0, QFormLayout::LabelRole, horizontalLayout);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        formLayout_3->setItem(0, QFormLayout::FieldRole, horizontalSpacer_2);

        tvModel = new QTableView(layoutWidget);
        tvModel->setObjectName(QString::fromUtf8("tvModel"));
        tvModel->setSortingEnabled(true);
        tvModel->horizontalHeader()->setStretchLastSection(true);

        formLayout_3->setWidget(1, QFormLayout::SpanningRole, tvModel);

        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        SaveButton = new QPushButton(layoutWidget);
        SaveButton->setObjectName(QString::fromUtf8("SaveButton"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, SaveButton);

        RevertButton = new QPushButton(layoutWidget);
        RevertButton->setObjectName(QString::fromUtf8("RevertButton"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, RevertButton);

        Add = new QPushButton(layoutWidget);
        Add->setObjectName(QString::fromUtf8("Add"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, Add);

        Delete = new QPushButton(layoutWidget);
        Delete->setObjectName(QString::fromUtf8("Delete"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, Delete);


        formLayout_3->setLayout(2, QFormLayout::LabelRole, formLayout_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        formLayout_3->setItem(2, QFormLayout::FieldRole, horizontalSpacer);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(500, 10, 231, 181));
        horizontalLayout_2 = new QHBoxLayout(groupBox);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_2);

        cbSelectColumn = new ComboBoxForDB(groupBox);
        cbSelectColumn->setObjectName(QString::fromUtf8("cbSelectColumn"));

        formLayout->setWidget(0, QFormLayout::FieldRole, cbSelectColumn);

        teDecript = new QTextEdit(groupBox);
        teDecript->setObjectName(QString::fromUtf8("teDecript"));

        formLayout->setWidget(1, QFormLayout::FieldRole, teDecript);

        Search = new QPushButton(groupBox);
        Search->setObjectName(QString::fromUtf8("Search"));

        formLayout->setWidget(2, QFormLayout::FieldRole, Search);

        RevertTable = new QPushButton(groupBox);
        RevertTable->setObjectName(QString::fromUtf8("RevertTable"));

        formLayout->setWidget(3, QFormLayout::FieldRole, RevertTable);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_3);


        horizontalLayout_2->addLayout(formLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 750, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\320\221\320\260\320\267\320\260 \320\264\320\260\320\275\320\275\321\213\321\205", nullptr));
        label->setText(QApplication::translate("MainWindow", "\320\242\320\265\321\203\321\211\320\260\321\217 \321\202\320\260\320\261\320\273\320\270\321\206\320\260:", nullptr));
        SaveButton->setText(QApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        RevertButton->setText(QApplication::translate("MainWindow", "\320\236\321\202\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        Add->setText(QApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        Delete->setText(QApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        groupBox->setTitle(QApplication::translate("MainWindow", "\320\222\321\213\320\261\320\276\321\200\320\272\320\260", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "\320\241\321\202\320\276\320\273\320\261\320\265\321\206", nullptr));
        Search->setText(QApplication::translate("MainWindow", "\320\235\320\260\320\271\321\202\320\270", nullptr));
        RevertTable->setText(QApplication::translate("MainWindow", "\320\222\320\276\321\201\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "\320\227\320\275\320\260\321\207\320\265\320\275\320\270\320\265", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
