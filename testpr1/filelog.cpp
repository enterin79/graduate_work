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
    filetable=new QSqlTableModel(this, *db);
    filetable->setTable("filesforlog");
    filetable->select();
    filetable->setFilter("logid="+QString("%1").arg(idLog));
    filetable->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tvFiles->setModel(filetable);
    ui->tvFiles->hideColumn(0);
    ui->tvFiles->hideColumn(1);
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
        record.setValue("idfile", filetable->rowCount());
        record.setValue("logid", idLog);
        record.setValue("filelog", byarr);
        if(filetable->insertRecord(-1, record)){
            if(!filetable->submitAll()){
                 QMessageBox::information(this, "none", filetable->lastError().text());
            }
        }
        else{
            QMessageBox::information(this, "none", filetable->lastError().text());
        }
    }
}


void filelog::on_openFile_clicked()
{
    QString file=ui->tvFiles->currentIndex().data().toString();
    QDesktopServices::openUrl(file);
}
