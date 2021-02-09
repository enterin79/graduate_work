#include "edit.h"
#include "ui_edit.h"
#include <QDebug>

Edit::Edit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Edit)
{
    ui->setupUi(this);

}

Edit::~Edit()
{
    delete ui;
}

bool Edit::setModelTable(QSqlRelationalTableModel *model, QString table)
{
    //tablemapper=new QDataWidgetMapper(this);
    try {
        tablemapper=new QDataWidgetMapper(this);
        tablemapper->setModel(model);
        if(table=="equipment"){
            tablemapper->addMapping(ui->leNameEq, model->fieldIndex("nameequip"));
            tablemapper->addMapping(ui->leNote, model->fieldIndex("note"), "plainText");
            tablemapper->addMapping(ui->deFirstExpDate, model->fieldIndex("firstexpldate"));
            ui->gbTest->hide();
            ui->gbEquip->show();
        }
        else if(table=="test"){
            //QSqlTableModel *temp=new QSqlTableModel();
            //temp=model->relationModel(model->fieldIndex("nameequip"));
            //ui->cbEquipId->setModel(temp);
            /*for(int i=1; i<=temp->rowCount();i++){
                QString text=temp->record(i-1).value(temp->fieldIndex("nameequip")).toString();
                qDebug()<<"now text"<<text;
                ui->cbEquipId->addItem(text, temp->record(i-1).value(0).toInt());
            }*/
            //ui->cbEquipId->setModelColumn(1);
            ui->cbEquipId->setForeignKey("id", "nameequip", model->relationModel(model->fieldIndex("nameequip")));
            tablemapper->addMapping(ui->leNameTest, model->fieldIndex("nametest"));
            tablemapper->addMapping(ui->deDateTest, model->fieldIndex("datetest"));
            tablemapper->addMapping(ui->leDescript, model->fieldIndex("description"), "plainText");
            tablemapper->addMapping(ui->cbEquipId, model->fieldIndex("nameequip"));
            //tablemapper->addMapping(ui->unshowing, model->fieldIndex("nameequip"));
            ui->gbTest->show();
            ui->gbEquip->hide();
        }
        return 1;
    }  catch (...) {
        return 0;
    }
}


void Edit::on_Apply_clicked()
{
    //ui->unshowing->setText(ui->cbEquipId->currentData().toString());
    //qDebug()<<ui->cbEquipId->currentData().toString();
    tablemapper->submit();
    emit saveYes(true);
    qDebug()<<"here yes";
    close();
}

void Edit::on_Delete_clicked()
{
    close();
}

void Edit::on_cbEquipId_currentIndexChanged(const QString &arg1)
{

}

void Edit::on_unshowing_textChanged(const QString &arg1)
{
    //ui->cbEquipId->setCurrentText(arg1);
}
