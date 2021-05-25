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
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
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
    QAction *RetryConnection;
    QAction *UnloadFrom;
    QAction *HelpMessage;
    QWidget *centralwidget;
    QGridLayout *gridLayout_4;
    QTableView *tvModel;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *cbChooseTable;
    QSpacerItem *horizontalSpacer;
    QFormLayout *formLayout_2;
    QPushButton *SaveButton;
    QPushButton *RevertButton;
    QPushButton *Add;
    QPushButton *Delete;
    QGroupBox *gbTimeScroll;
    QGridLayout *gridLayout_2;
    QPushButton *Retry;
    QPushButton *StartStopScroll;
    QLabel *timelabel;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_3;
    QSlider *LogSlider;
    QDateTimeEdit *dtScroll;
    QGroupBox *gbSearch;
    QGridLayout *gridLayout;
    QFormLayout *formLayout;
    QLabel *label_2;
    ComboBoxForDB *cbSelectColumn;
    QLabel *label_3;
    QTextEdit *teDecript;
    QPushButton *Search;
    QPushButton *RevertTable;
    QRadioButton *rbNormalSelection;
    QRadioButton *rbCascadeSelection;
    QMenuBar *menubar;
    QMenu *menu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(826, 484);
        MainWindow->setMinimumSize(QSize(750, 300));
        QFont font;
        font.setPointSize(10);
        MainWindow->setFont(font);
        RetryConnection = new QAction(MainWindow);
        RetryConnection->setObjectName(QString::fromUtf8("RetryConnection"));
        RetryConnection->setMenuRole(QAction::ApplicationSpecificRole);
        UnloadFrom = new QAction(MainWindow);
        UnloadFrom->setObjectName(QString::fromUtf8("UnloadFrom"));
        HelpMessage = new QAction(MainWindow);
        HelpMessage->setObjectName(QString::fromUtf8("HelpMessage"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_4 = new QGridLayout(centralwidget);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        tvModel = new QTableView(centralwidget);
        tvModel->setObjectName(QString::fromUtf8("tvModel"));
        tvModel->setMinimumSize(QSize(0, 0));
        QFont font1;
        font1.setPointSize(12);
        tvModel->setFont(font1);
        tvModel->setEditTriggers(QAbstractItemView::DoubleClicked);
        tvModel->setSortingEnabled(true);
        tvModel->horizontalHeader()->setStretchLastSection(false);

        gridLayout_4->addWidget(tvModel, 2, 0, 2, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMaximumSize(QSize(120, 22));

        horizontalLayout->addWidget(label);

        cbChooseTable = new QComboBox(centralwidget);
        cbChooseTable->setObjectName(QString::fromUtf8("cbChooseTable"));
        cbChooseTable->setMinimumSize(QSize(200, 22));
        cbChooseTable->setMaximumSize(QSize(200, 22));

        horizontalLayout->addWidget(cbChooseTable);

        horizontalSpacer = new QSpacerItem(25, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        gridLayout_4->addLayout(horizontalLayout, 1, 0, 1, 1);

        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        SaveButton = new QPushButton(centralwidget);
        SaveButton->setObjectName(QString::fromUtf8("SaveButton"));
        SaveButton->setMinimumSize(QSize(80, 22));
        SaveButton->setMaximumSize(QSize(80, 22));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, SaveButton);

        RevertButton = new QPushButton(centralwidget);
        RevertButton->setObjectName(QString::fromUtf8("RevertButton"));
        RevertButton->setMinimumSize(QSize(80, 22));
        RevertButton->setMaximumSize(QSize(80, 22));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, RevertButton);

        Add = new QPushButton(centralwidget);
        Add->setObjectName(QString::fromUtf8("Add"));
        Add->setMinimumSize(QSize(80, 22));
        Add->setMaximumSize(QSize(80, 22));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, Add);

        Delete = new QPushButton(centralwidget);
        Delete->setObjectName(QString::fromUtf8("Delete"));
        Delete->setMinimumSize(QSize(80, 22));
        Delete->setMaximumSize(QSize(80, 22));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, Delete);


        gridLayout_4->addLayout(formLayout_2, 8, 0, 1, 1);

        gbTimeScroll = new QGroupBox(centralwidget);
        gbTimeScroll->setObjectName(QString::fromUtf8("gbTimeScroll"));
        gbTimeScroll->setEnabled(true);
        gbTimeScroll->setMinimumSize(QSize(0, 60));
        gridLayout_2 = new QGridLayout(gbTimeScroll);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        Retry = new QPushButton(gbTimeScroll);
        Retry->setObjectName(QString::fromUtf8("Retry"));
        Retry->setMinimumSize(QSize(80, 22));
        Retry->setMaximumSize(QSize(80, 22));

        gridLayout_2->addWidget(Retry, 1, 1, 1, 1);

        StartStopScroll = new QPushButton(gbTimeScroll);
        StartStopScroll->setObjectName(QString::fromUtf8("StartStopScroll"));
        StartStopScroll->setMinimumSize(QSize(80, 22));
        StartStopScroll->setMaximumSize(QSize(80, 22));

        gridLayout_2->addWidget(StartStopScroll, 1, 0, 1, 1);

        timelabel = new QLabel(gbTimeScroll);
        timelabel->setObjectName(QString::fromUtf8("timelabel"));

        gridLayout_2->addWidget(timelabel, 1, 3, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 1, 2, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 1, 4, 1, 1);

        LogSlider = new QSlider(gbTimeScroll);
        LogSlider->setObjectName(QString::fromUtf8("LogSlider"));
        LogSlider->setEnabled(true);
        LogSlider->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(LogSlider, 0, 2, 1, 3);

        dtScroll = new QDateTimeEdit(gbTimeScroll);
        dtScroll->setObjectName(QString::fromUtf8("dtScroll"));
        dtScroll->setMinimumSize(QSize(0, 22));
        dtScroll->setCalendarPopup(true);

        gridLayout_2->addWidget(dtScroll, 0, 0, 1, 2);


        gridLayout_4->addWidget(gbTimeScroll, 7, 0, 1, 2);

        gbSearch = new QGroupBox(centralwidget);
        gbSearch->setObjectName(QString::fromUtf8("gbSearch"));
        gbSearch->setMaximumSize(QSize(230, 16777215));
        gridLayout = new QGridLayout(gbSearch);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label_2 = new QLabel(gbSearch);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        cbSelectColumn = new ComboBoxForDB(gbSearch);
        cbSelectColumn->setObjectName(QString::fromUtf8("cbSelectColumn"));

        formLayout->setWidget(1, QFormLayout::FieldRole, cbSelectColumn);

        label_3 = new QLabel(gbSearch);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        teDecript = new QTextEdit(gbSearch);
        teDecript->setObjectName(QString::fromUtf8("teDecript"));

        formLayout->setWidget(2, QFormLayout::FieldRole, teDecript);

        Search = new QPushButton(gbSearch);
        Search->setObjectName(QString::fromUtf8("Search"));

        formLayout->setWidget(3, QFormLayout::SpanningRole, Search);

        RevertTable = new QPushButton(gbSearch);
        RevertTable->setObjectName(QString::fromUtf8("RevertTable"));

        formLayout->setWidget(4, QFormLayout::SpanningRole, RevertTable);

        rbNormalSelection = new QRadioButton(gbSearch);
        rbNormalSelection->setObjectName(QString::fromUtf8("rbNormalSelection"));
        rbNormalSelection->setChecked(true);

        formLayout->setWidget(0, QFormLayout::LabelRole, rbNormalSelection);

        rbCascadeSelection = new QRadioButton(gbSearch);
        rbCascadeSelection->setObjectName(QString::fromUtf8("rbCascadeSelection"));

        formLayout->setWidget(0, QFormLayout::FieldRole, rbCascadeSelection);


        gridLayout->addLayout(formLayout, 0, 0, 1, 1);


        gridLayout_4->addWidget(gbSearch, 2, 1, 2, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 826, 23));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menu->addAction(RetryConnection);
        menu->addAction(UnloadFrom);
        menu->addAction(HelpMessage);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\320\221\320\260\320\267\320\260 \320\264\320\260\320\275\320\275\321\213\321\205", nullptr));
        RetryConnection->setText(QApplication::translate("MainWindow", "\320\237\320\276\320\262\321\202\320\276\321\200\320\275\320\276\320\265 \320\277\320\276\320\264\320\272\320\273\321\216\321\207\320\265\320\275\320\270\320\265", nullptr));
        UnloadFrom->setText(QApplication::translate("MainWindow", "\320\222\321\213\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \320\264\320\260\320\275\320\275\321\213\320\265 \320\270\320\267...", nullptr));
        HelpMessage->setText(QApplication::translate("MainWindow", "\320\237\320\276\320\274\320\276\321\211\321\214", nullptr));
#ifndef QT_NO_TOOLTIP
        HelpMessage->setToolTip(QApplication::translate("MainWindow", "\320\237\320\276\320\274\320\276\321\211\321\214", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        HelpMessage->setShortcut(QApplication::translate("MainWindow", "Ctrl+H", nullptr));
#endif // QT_NO_SHORTCUT
        label->setText(QApplication::translate("MainWindow", "\320\242\320\265\321\203\321\211\320\260\321\217 \321\202\320\260\320\261\320\273\320\270\321\206\320\260:", nullptr));
        SaveButton->setText(QApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        RevertButton->setText(QApplication::translate("MainWindow", "\320\236\321\202\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        Add->setText(QApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        Delete->setText(QApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        gbTimeScroll->setTitle(QString());
        Retry->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\275\320\276\320\262\320\276", nullptr));
        StartStopScroll->setText(QApplication::translate("MainWindow", "\320\241\321\202\320\260\321\200\321\202/\320\241\321\202\320\276\320\277", nullptr));
        timelabel->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        dtScroll->setDisplayFormat(QApplication::translate("MainWindow", "dd.MM.yyyy H:mm:ss", nullptr));
        gbSearch->setTitle(QApplication::translate("MainWindow", "\320\222\321\213\320\261\320\276\321\200\320\272\320\260", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "\320\241\321\202\320\276\320\273\320\261\320\265\321\206", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "\320\227\320\275\320\260\321\207\320\265\320\275\320\270\320\265", nullptr));
        Search->setText(QApplication::translate("MainWindow", "\320\235\320\260\320\271\321\202\320\270", nullptr));
        RevertTable->setText(QApplication::translate("MainWindow", "\320\222\320\276\321\201\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214", nullptr));
        rbNormalSelection->setText(QApplication::translate("MainWindow", "\320\236\320\261\321\213\321\207\320\275\320\260\321\217", nullptr));
        rbCascadeSelection->setText(QApplication::translate("MainWindow", "\320\232\320\260\321\201\320\272\320\260\320\264\320\275\320\260\321\217", nullptr));
        menu->setTitle(QApplication::translate("MainWindow", "\320\234\320\265\320\275\321\216", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
