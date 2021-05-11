#include "filelog.h"
#include "ui_filelog.h"
#include <QMessageBox>

filelog::filelog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::filelog)
{
    ui->setupUi(this);
}

void filelog::setLog(int idLog, QSqlDatabase *db)
{
    QString id, name;
    this->idLog=idLog;
    ui->leLogID->setText(QString("%1").arg(idLog));

    filetable=new UpgradedModel(this, *db);
    filetable->setTable("conditionofparm");
    filetable->setJoinMode(QSqlRelationalTableModel::LeftJoin);
    filetable->setRelation(filetable->fieldIndex("ParmId"),
                           QSqlRelation("ParameterOfBlock", "idParm", "NameParm"));
    filetable->setRelation(filetable->fieldIndex("FileId"),
                           QSqlRelation("FileOfParameter", "idFile", "PathFile"));
    filetable->select();
    filetable->setFilter("RecId="+QString("%1").arg(idLog));
    filetable->setEditStrategy(QSqlTableModel::OnManualSubmit);

    filetable->setHeaderData(2, Qt::Orientation::Horizontal, "Параметр");
    filetable->setHeaderData(3, Qt::Orientation::Horizontal, "Состояние");
    filetable->setHeaderData(4, Qt::Orientation::Horizontal, "Файл");
    ui->tvFiles->setModel(filetable);
    ui->tvFiles->horizontalHeader()->show();
    ui->tvFiles->verticalHeader()->show();
    ui->tvFiles->hideColumn(filetable->fieldIndex("idCond"));
    ui->tvFiles->hideColumn(filetable->fieldIndex("RecId"));

    tablemapper=new QDataWidgetMapper(this);
    tablemapper->setModel(filetable);

    id="idParm";
    name="NameParm";
    ui->cbNameParm->setForeignKey(&id, &name, filetable->relationModel(filetable->fieldIndex("NameParm")));
    ui->cbCondParm->addItem("норма","норма");
    ui->cbCondParm->addItem("больше","больше");
    ui->cbCondParm->addItem("меньше","меньше");
    on_newRow_clicked();

    tablemapper->addMapping(ui->cbCondParm, filetable->fieldIndex("CondMark"));
    tablemapper->addMapping(ui->cbNameParm, filetable->fieldIndex("NameParm"));
    tablemapper->addMapping(ui->leLogID, filetable->fieldIndex("RecId"));
    tablemapper->addMapping(ui->leFileParm, filetable->fieldIndex("PathFile"), "plainText");
    tablemapper->addMapping(ui->leFiletableID, filetable->fieldIndex("idCond"));

    ui->leFiletableID->hide();
    ui->leLogID->hide();
}

int filelog::getFileID(QByteArray *path)
{
    QSqlQueryModel *tempmodel=new QSqlQueryModel();
    tempmodel->setQuery("select idfile "
    "from fileofparameter "
    "where pathfile='"+*path+"'");
    if(tempmodel->rowCount()==0){
        return -1;
    }
    else{
        int fileid=tempmodel->index(0, 0).data().toInt();
        return fileid;
    }
}

filelog::~filelog()
{
    delete ui;
}

void filelog::on_selectFile_clicked()
{

    QString file=QFileDialog::getOpenFileName(this,
                                              QString::fromUtf8("Открыть файл"),
                                              QDir::currentPath(),
                                              "(*.txt);;All files (*.*)"
                                              );
    if(file!=""){
        QByteArray byarr=file.toUtf8();
        int fileid=getFileID(&byarr);
        if(fileid<=0){
            //QMessageBox::information(this, "", QString("%1").arg(fileid));
            QSqlQuery query;
            query.exec("insert into fileofparameter(pathfile) values ('"+byarr+"');");
            fileid=getFileID(&byarr);
        }
        QMessageBox::information(this, "", QString("%1").arg(fileid));
        idFile=fileid;
        ui->leFileParm->setPlainText(file);
    }
}


void filelog::on_openFile_clicked()
{
    int row=ui->tvFiles->currentIndex().row();
    QString file=filetable->index(row, filetable->fieldIndex("PathFile")).data().toString();
    if(!QDesktopServices::openUrl(file)){
        QMessageBox::critical(this, "Ошибка", "Файл не существует или недоступен для просмотра.");
    }
}

void filelog::on_deleteFile_clicked()
{
    int row=ui->tvFiles->currentIndex().row();
    if(row>=0){ //Проверка номера удаляемой строки
        if(!filetable->removeRow(row)){   //Проверка корректности удаления строки
            QMessageBox::critical(this, "Ошибка", "Ошибка удаления записи!");
        }
        else{
            int answer=QMessageBox::question(this,"Подтверждение удаления", "Вы действительно хотите удалить запись? Действие невозможно отменить.");
            if(answer==QMessageBox::Button::Yes) filetable->submitAll();
        }
    }
    else{
        QMessageBox::critical(this, "Ошибка", "Удаляемая строка не выбрана.");
    }
}

void filelog::on_copy_clicked()
{
    int row=ui->tvFiles->currentIndex().row();
    QString file=filetable->index(row, filetable->fieldIndex("PathFile")).data().toString();
    QApplication::clipboard()->setText(file);
    QMessageBox::information(this, "Копирование", "Путь к файлу скопирован.");
}

void filelog::on_saveParm_clicked()
{
    QSqlRecord record=filetable->record();
    if(ui->leFiletableID->text()=="NULL"){
        record.remove(0);
    }
    else{
        record.setValue("idCond", ui->leFiletableID->text().toInt());
    }

    record.setValue("RecId", ui->leLogID->text().toInt());
    record.setValue("NameParm", ui->cbNameParm->currentData());
    record.setValue("CondMark", ui->cbCondParm->currentData());
    record.setValue("PathFile", idFile);

    if(ui->leFiletableID->text()=="NULL"){
        filetable->insertRecord(-1, record);
    }
    else{
        filetable->updateRowInTable(ui->tvFiles->currentIndex().row(), record);
    }

    if(filetable->submitAll()){  //Сохранение изменений таблицы
        qInfo(loggerInfo())<<"Saving ConditionOfParm OK";
    }
    else{
        qWarning(loggerWarning())<<"Saving ConditionOfParm error "<<filetable->lastError().text();
        QMessageBox::critical(this, "Ошибка", "Ошибка изменения данных! Текст ошибки: "+filetable->lastError().text());
    }
    on_newRow_clicked();
}

void filelog::on_tvFiles_doubleClicked(const QModelIndex &index)
{
    tablemapper->setCurrentModelIndex(index);
    QByteArray byarr=ui->leFileParm->toPlainText().toUtf8();
    idFile=getFileID(&byarr);
    ui->lrownum->setText("Запись №"+QString("%1").arg((index.row()+1)));
}

void filelog::on_newRow_clicked()
{
    idFile=-1;
    ui->leFiletableID->setText("NULL");
    ui->cbCondParm->setCurrentIndex(-1);
    ui->cbNameParm->setCurrentIndex(-1);
    ui->leFileParm->clear();
    ui->lrownum->setText("Новая запись");
}
