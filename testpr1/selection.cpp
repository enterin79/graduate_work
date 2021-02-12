#include "selection.h"
#include "ui_selection.h"

//потом удалить
Selection::Selection(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Selection)
{
    ui->setupUi(this);
}

Selection::~Selection()
{
    delete ui;
}

void Selection::setdb(dbWorking *currdb, int currtable)
{
    db=new dbWorking();
    db=currdb;
    //ui->tvSelection->setModel(db->generalmodel);
    fields=db->generalmodel->record();
    for(int i=1; i<fields.count();i++){
        ui->cbSelectColumn->addItem(db->fieldsynonims[i-1],fields.fieldName(i));
    }
}


void Selection::on_Search_clicked()
{
    QString selectionquery=ui->cbSelectColumn->currentData().toString()+"='"+ui->teDecript->toPlainText()+"'";
    qDebug()<<selectionquery;
     qDebug()<<"here";
    db->generalmodel->setFilter(selectionquery.toUtf8());

}

void Selection::on_RevertTable_clicked()
{
    //ui->tvSelection->setModel(db->generalmodel);
}
