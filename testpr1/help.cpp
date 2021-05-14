#include "help.h"
#include "ui_help.h"

Help::Help(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Help)
{
    ui->setupUi(this);
}

Help::~Help()
{
    delete ui;
}

void Help::setText(QString *text)
{
    ui->leHelpText->setText(*text);
}

void Help::on_btHelpOK_clicked()
{
    close();
}
