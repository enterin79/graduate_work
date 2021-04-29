#include "filelog.h"
#include "ui_filelog.h"

filelog::filelog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::filelog)
{
    ui->setupUi(this);
}

void filelog::setLog(int idLog, QSqlDatabase *db)
{
    //ui->textEdit->setText(QString("%1").arg(idLog));
    this->idLog=idLog;
    filetable=new FileTableModel(this, *db);
    filetable->setTable("filesforlog");
    filetable->select();
    filetable->setFilter("logid="+QString("%1").arg(idLog));
    filetable->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tvFiles->setModel(filetable);
    ui->tvFiles->hideColumn(filetable->fieldIndex("idfile"));
    ui->tvFiles->hideColumn(filetable->fieldIndex("logid"));
    //ui->tvFiles->resizeRowToContents(filetable->fieldIndex("filelog"));
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
    //ui->textEdit->setText(file);
    if(file!=""){
        QByteArray byarr=file.toUtf8();
        QSqlRecord record=filetable->record();
        record.remove(0);
        record.setValue("logid", idLog);
        record.setValue("filelog", byarr);
        if(filetable->insertRecord(-1, record)){
            if(!filetable->submitAll()){
                 QMessageBox::critical(this, "Ошибка", filetable->lastError().text());
            }
        }
        else{
            QMessageBox::critical(this, "Ошибка", "Ошибка выбора файла.");
        }
    }
}


void filelog::on_openFile_clicked()
{
    QString file=ui->tvFiles->currentIndex().data().toString();
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
    QString file=ui->tvFiles->currentIndex().data().toString();
    QApplication::clipboard()->setText(file);
    QMessageBox::information(this, "Копирование", "Путь к файлу скопирован.");
}
