#include "help.h"
#include "ui_help.h"
#include <QMessageBox>

/*Конструктор класса по умолчанию
 *
 * Формальный параметр:
 * parent - указатель на родительский элемент.
*/
Help::Help(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Help)
{
    ui->setupUi(this);
}

/*Деструктор класса*/
Help::~Help()
{
    delete ui;
}

/*Процедура установки текста в элемент
 *
 * Формальный параметр:
 * text - вставляемый текст.
*/
void Help::setText(QString *text)
{
    ui->leHelpText->setText(*text);
}

/*Событие закрытия формы*/
void Help::on_btHelpOK_clicked()
{
    close();
}
