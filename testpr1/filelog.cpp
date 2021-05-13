#include "filelog.h"
#include "ui_filelog.h"
#include <QMessageBox>

/*Конструктор класса по умолчанию
 * Формальный параметр:
 * parent - указатель на родительский элемент.
*/
filelog::filelog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::filelog)
{
    ui->setupUi(this);
}

/*Процедура формирования выборки по данным записи из таблицы "Прием данных" и связывания этого представления с элементами интерфейса
 * Формальные параметры:
 * idLog - идентификатор записи из таблицы "Прием данных";
 * db - экземпляр соединения с базой данных.
 *
 * Локальные переменные:
 * id - данные для записей внешнего ключа в элементе выбора;
 * name - текст, соотвествующий данным, для каждой записи внешнего ключа в элементе выбора.
*/
void filelog::setLog(int idLog, QSqlDatabase *db)
{
    QString id, name;
    this->idLog=idLog;

    filetable=new UpgradedModel(this, *db);//Загрузка таблицы
    filetable->setTable(PARMLOG_L);
    filetable->setJoinMode(QSqlRelationalTableModel::LeftJoin);
    filetable->setRelation(filetable->fieldIndex("parmid"),
                           QSqlRelation(PARM, "idparm", "nameparm"));
    filetable->setRelation(filetable->fieldIndex("fileid"),
                           QSqlRelation(FILE, "idfile", "pathfile"));
    filetable->select();
    filetable->setFilter("recid="+QString("%1").arg(idLog));
    filetable->setEditStrategy(QSqlTableModel::OnManualSubmit);

    filetable->setHeaderData(2, Qt::Orientation::Horizontal, "Параметр");//Настройка внешнего вида таблицы
    filetable->setHeaderData(3, Qt::Orientation::Horizontal, "Состояние");
    filetable->setHeaderData(4, Qt::Orientation::Horizontal, "Файл");
    ui->tvFiles->setModel(filetable);
    ui->tvFiles->horizontalHeader()->show();
    ui->tvFiles->verticalHeader()->show();
    ui->tvFiles->hideColumn(filetable->fieldIndex("idcond"));
    ui->tvFiles->hideColumn(filetable->fieldIndex("recid"));

    tablemapper=new QDataWidgetMapper(this);
    tablemapper->setModel(filetable);

    id="idparm";
    name="nameparm";
    ui->cbNameParm->setForeignKey(&id, &name, filetable->relationModel(filetable->fieldIndex("nameparm")));
    ui->cbCondParm->addItem("норма","норма");
    ui->cbCondParm->addItem("больше","больше");
    ui->cbCondParm->addItem("меньше","меньше");
    on_newRow_clicked();

    tablemapper->addMapping(ui->cbCondParm, filetable->fieldIndex("condmark"));//Соединение элеметов интерфейса с полями таблицы
    tablemapper->addMapping(ui->cbNameParm, filetable->fieldIndex("nameparm"));
    tablemapper->addMapping(ui->leLogID, filetable->fieldIndex("recid"));
    tablemapper->addMapping(ui->leFileParm, filetable->fieldIndex("pathfile"), "plainText");
    tablemapper->addMapping(ui->leFiletableID, filetable->fieldIndex("idcond"));
    tablemapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    //ui->leFiletableID->hide();
    //ui->leLogID->hide();
    on_newRow_clicked();
    ui->leLogID->setText(QString("%1").arg(idLog));
}
/*Функция поиска идентификатора для пути файла
 *
 * Формальный параметр:
 * path - путь к файлу, для которого необходимо найти идентификатор.
 *
 * Локальные переменные:
 * tempmodel - временная таблица для поиска данных.
*/
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
/*Деструктор класса*/
filelog::~filelog()
{
    delete ui;
}

/*Событие для выбора необходимого файла
 * Локальные переменные:
 * file - путь к файлу;
 * byarr - путь к файлу, преобразованный к массиву байтов.
*/
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
        //QMessageBox::information(this, "", QString("%1").arg(fileid));
        idFile=fileid;
        ui->leFileParm->setPlainText(file);
    }
}

/*Событие для открытия файла из выбранной записи
 * Локальная переменная:
 * row - номер выбранной строки.
*/
void filelog::on_openFile_clicked()
{
    int row=ui->tvFiles->currentIndex().row();
    QString file=filetable->index(row, filetable->fieldIndex("pathfile")).data().toString();
    if(!QDesktopServices::openUrl(file)){
        QMessageBox::critical(this, "Ошибка", "Файл не существует или недоступен для просмотра.");
    }
}

/*Событие для удаления записи из таблицы "Состояние параметров"
 * Локальная переменная:
 * row - номер выбранной строки.
*/
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

/*Событие для копирования пути к файлу
 * Локальная переменная:
 * row - номер выбранной строки.
*/
void filelog::on_copy_clicked()
{
    int row=ui->tvFiles->currentIndex().row();
    QString file=filetable->index(row, filetable->fieldIndex("pathfile")).data().toString();
    QApplication::clipboard()->setText(file);
    QMessageBox::information(this, "Копирование", "Путь к файлу скопирован.");
}

/*Событие для сохранения изменений в записи
 * Локальная переменная:
 * record - запись с данными обновляемой или добавляемой записи.
*/
void filelog::on_saveParm_clicked()
{
    QSqlRecord record=filetable->record();//Получение набора названий полей таблицы
    if(ui->leFiletableID->text()=="NULL"){//Заполнение записи данными
        record.remove(0);
        filetable->setTable(PARMLOG_L);
        filetable->setJoinMode(QSqlRelationalTableModel::LeftJoin);
        filetable->setRelation(filetable->fieldIndex("parmid"),
                               QSqlRelation(PARM, "idparm", "nameparm"));
        filetable->setRelation(filetable->fieldIndex("fileid"),
                               QSqlRelation(FILE, "idfile", "pathfile"));
        filetable->select();
        filetable->setFilter("recid="+QString("%1").arg(idLog));
        filetable->setEditStrategy(QSqlTableModel::OnManualSubmit);
    }
    else{
        record.setValue("idcond", ui->leFiletableID->text().toInt());

    }

    record.setValue("recid", ui->leLogID->text().toInt());
    record.setValue("nameparm", ui->cbNameParm->currentData());
    record.setValue("condmark", ui->cbCondParm->currentData());
    record.setValue("pathfile", idFile);


    if(ui->leFiletableID->text()=="NULL"){//Проверка наличия идентификатора записи
        QMessageBox::information(this, "", QString("%1").arg(record.fieldName(3)));
        QMessageBox::information(this, "", QString("%1").arg(record.value("pathfile").toString()));
        filetable->insertRecord(-1, record);//Вставка записи
    }
    else{
        filetable->updateRowInTable(ui->tvFiles->currentIndex().row(), record);//Обновление записи
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

/*Событие вывода выбранной данных записи в свзанные элементы
 * Формальный параметр:
 * index - индекс записи, на которой произошло событие.
*/
void filelog::on_tvFiles_doubleClicked(const QModelIndex &index)
{
    tablemapper->setCurrentModelIndex(index);
    QByteArray byarr=ui->leFileParm->toPlainText().toUtf8();
    idFile=getFileID(&byarr);
    ui->lrownum->setText("Запись №"+QString("%1").arg((index.row()+1)));
}

/*Событие очистки свзанных с таблицей элементов*/
void filelog::on_newRow_clicked()
{
    idFile=-1;
    ui->leFiletableID->setText("NULL");
    ui->cbCondParm->setCurrentIndex(-1);
    ui->cbNameParm->setCurrentIndex(-1);
    ui->leFileParm->clear();
    ui->lrownum->setText("Новая запись");
}
