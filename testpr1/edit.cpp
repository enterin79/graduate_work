#include "edit.h"
#include "ui_edit.h"
#include <QDebug>

/*Конструктор класса по умолчанию
*/
Edit::Edit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Edit)
{
    ui->setupUi(this);

}

/*Деструктор класса
*/
Edit::~Edit()
{
    delete ui;
}


/*Метод для соединения данных таблицы с элементами формы редактирования
 *
 * Формальные параметры:
 * model - таблица, с которой происходит соединение;
 * table - название таблицы.
*/
bool Edit::setModelTable(QSqlRelationalTableModel *model, QString table)
{
    try {
        tablemapper=new QDataWidgetMapper(this);
        tablemapper->setModel(model);
        if(table=="equipment"){ //Соединение элементов формы редактирования с данными таблицы в зависимости от набора полей этой таблицы
            tablemapper->addMapping(ui->leNameEq, model->fieldIndex("nameequip"));
            tablemapper->addMapping(ui->leNote, model->fieldIndex("note"), "plainText");
            tablemapper->addMapping(ui->deFirstExpDate, model->fieldIndex("firstexpldate"));
            ui->gbTest->hide();
            ui->gbEquip->show();
        }
        else if(table=="test"){
            ui->cbEquipId->setForeignKey("id", "nameequip", model->relationModel(model->fieldIndex("nameequip")));
            tablemapper->addMapping(ui->leNameTest, model->fieldIndex("nametest"));
            tablemapper->addMapping(ui->deDateTest, model->fieldIndex("datetest"));
            tablemapper->addMapping(ui->leDescript, model->fieldIndex("description"), "plainText");
            tablemapper->addMapping(ui->cbEquipId, model->fieldIndex("nameequip"));
            ui->gbTest->show();
            ui->gbEquip->hide();
        }
        return 1;
    }  catch (...) {
        return 0;
    }
}

/*Событие сохранения текущих изменений и закрытия формы редактирования
*/
void Edit::on_Apply_clicked()
{
    //qDebug()<<ui->cbEquipId->currentData().toString();
    tablemapper->submit();  //Сохранение изменений в локальном экземпляре таблицы
    emit saveYes(true); //Отправка сигнала о внесении изменений основной форме
    close();
}

/*Событие закрытия формы редактирования
*/
void Edit::on_Delete_clicked()
{
    close();
}
