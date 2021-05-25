/********************************************************************************
** Form generated from reading UI file 'help.ui'
**
** Created by: Qt User Interface Compiler version 5.12.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HELP_H
#define UI_HELP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Help
{
public:
    QVBoxLayout *verticalLayout;
    QTextEdit *leHelpText;
    QPushButton *btHelpOK;

    void setupUi(QDialog *Help)
    {
        if (Help->objectName().isEmpty())
            Help->setObjectName(QString::fromUtf8("Help"));
        Help->resize(400, 300);
        QFont font;
        font.setPointSize(12);
        Help->setFont(font);
        verticalLayout = new QVBoxLayout(Help);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        leHelpText = new QTextEdit(Help);
        leHelpText->setObjectName(QString::fromUtf8("leHelpText"));
        leHelpText->setReadOnly(true);

        verticalLayout->addWidget(leHelpText);

        btHelpOK = new QPushButton(Help);
        btHelpOK->setObjectName(QString::fromUtf8("btHelpOK"));
        btHelpOK->setMinimumSize(QSize(80, 20));
        btHelpOK->setMaximumSize(QSize(80, 20));

        verticalLayout->addWidget(btHelpOK);


        retranslateUi(Help);

        QMetaObject::connectSlotsByName(Help);
    } // setupUi

    void retranslateUi(QDialog *Help)
    {
        Help->setWindowTitle(QApplication::translate("Help", "\320\232\321\200\320\260\321\202\320\272\320\276\320\265 \321\200\321\203\320\272\320\276\320\262\320\276\320\264\321\201\321\202\320\262\320\276 \320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\217", nullptr));
        btHelpOK->setText(QApplication::translate("Help", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Help: public Ui_Help {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HELP_H
