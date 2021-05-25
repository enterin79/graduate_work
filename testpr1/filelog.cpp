#include "filelog.h"
#include "ui_filelog.h"
#include <QMessageBox>

/*Конструктор класса по умолчанию
 *
 * Формальный параметр:
 * parent - указатель на родительский элемент.
*/
FileLog::FileLog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::filelog)
{
    ui->setupUi(this);
}

/*Процедура формирования выборки по данным записи из таблицы "Прием данных" и связывания этого представления с элементами интерфейса
 * Формальные параметры:
 * idLog - идентификатор записи из таблицы "Прием данных";
 * db - экземпляр соединения с базой данных.
*/
void FileLog::setLog(int idLog, QSqlDatabase *db)
{
    this->idLog=idLog;

    filetable=new UpgradedModel(this, *db);//Загрузка таблицы
    loadTable();

    tablemapper=new QDataWidgetMapper(this);
    tablemapper->setModel(filetable);

    ui->cbCondParm->addItem("норма","норма");
    ui->cbCondParm->addItem("больше","больше");
    ui->cbCondParm->addItem("меньше","меньше");

    tablemapper->addMapping(ui->cbCondParm, filetable->fieldIndex(_::PARMLOGCOND));//Соединение элеметов интерфейса с полями таблицы
    tablemapper->addMapping(ui->cbNameParm, filetable->fieldIndex(_::PARMNAME));
    tablemapper->addMapping(ui->leLogID, filetable->fieldIndex(_::PARMLOGLOG));
    tablemapper->addMapping(ui->leFileParm, filetable->fieldIndex(_::FILELOGNAME), "plainText");
    tablemapper->addMapping(ui->leFiletableID, filetable->fieldIndex(_::PARMLOGID));
    tablemapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    ui->leFiletableID->hide();
    ui->leLogID->hide();
    on_newRow_clicked();
    ui->leLogID->setText(QString("%1").arg(idLog));
}
/*Функция поиска идентификатора для пути файла
 *
 * Формальный параметр:
 * path - путь к файлу, для которого необходимо найти идентификатор.
 *
 * Локальная переменная:
 * tempmodel - временная таблица для поиска данных.
*/
int FileLog::getFileID(QByteArray *path)
{
    QSqlQueryModel *tempmodel=new QSqlQueryModel();
    tempmodel->setQuery("select "+_::FILELOGID+" "
    "from "+_::FILELOG+" "
    "where "+_::FILELOGNAME+"='"+*path+"'");
    if(tempmodel->rowCount()==0){
        return -1;
    }
    else{
        int fileid=tempmodel->index(0, 0).data().toInt();
        return fileid;
    }
}


/*Процедура загрузки и настройки отображения таблицы
 *
 * Локальные переменные:
 * id - данные для записей внешнего ключа в элементе выбора;
 * name - текст, соотвествующий данным, для каждой записи внешнего ключа в элементе выбора.
*/
void FileLog::loadTable()
{
    QString id, name;
    filetable->setTable(_::PARMLOG);
    filetable->setJoinMode(QSqlRelationalTableModel::LeftJoin);
    filetable->setRelation(filetable->fieldIndex(_::PARMLOGPARM),
                           QSqlRelation(_::PARM, _::PARMID, _::PARMNAME));
    filetable->setRelation(filetable->fieldIndex(_::PARMLOGFILE),
                           QSqlRelation(_::FILELOG, _::FILELOGID, _::FILELOGNAME));
    if(filetable->select()){
        filetable->setFilter(QString(_::PARMLOGLOG)+"="+QString("%1").arg(idLog));
        filetable->setEditStrategy(QSqlTableModel::OnManualSubmit);
        filetable->setHeaderData(2, Qt::Orientation::Horizontal, "Параметр");//Настройка внешнего вида таблицы
        filetable->setHeaderData(3, Qt::Orientation::Horizontal, "Состояние");
        filetable->setHeaderData(4, Qt::Orientation::Horizontal, "Файл");
        ui->tvFiles->setModel(filetable);
        ui->tvFiles->horizontalHeader()->show();
        ui->tvFiles->verticalHeader()->show();
        ui->tvFiles->hideColumn(filetable->fieldIndex(_::PARMLOGID));
        ui->tvFiles->hideColumn(filetable->fieldIndex(_::PARMLOGLOG));

        id=_::PARMID;
        name=_::PARMNAME;
        ui->cbNameParm->setForeignKey(&id, &name, filetable->relationModel(filetable->fieldIndex(_::PARMNAME)));
        qInfo(loggerInfo())<<"Reading conditionofparm OK";
    }
    else{
        QMessageBox::critical(this, "Ошибка подключения", "Произошла ошибка подключения!");
        close();
    }
}

/*Деструктор класса*/
FileLog::~FileLog()
{
    delete ui;
}

/*Событие для выбора необходимого файла
 *
 * Локальные переменные:
 * file - путь к файлу;
 * byarr - путь к файлу, преобразованный к массиву байтов.
*/
void FileLog::on_selectFile_clicked()
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
            query.exec("insert into "+_::FILELOG+"("+_::FILELOGNAME+") values ('"+byarr+"');");
            fileid=getFileID(&byarr);
        }
        //QMessageBox::information(this, "", QString("%1").arg(fileid));
        idFile=fileid;
        ui->leFileParm->setPlainText(file);
    }
}

/*Событие для открытия файла из выбранной записи
 *
 * Локальная переменная:
 * row - номер выбранной строки.
*/
void FileLog::on_openFile_clicked()
{
    int row=ui->tvFiles->currentIndex().row();
    QString file=filetable->index(row, filetable->fieldIndex(_::FILELOGNAME)).data().toString();
    if(!QDesktopServices::openUrl(file)){
        QMessageBox::critical(this, "Ошибка", "Файл не существует или недоступен для просмотра.");
    }
}

/*Событие для удаления записи из таблицы "Состояние параметров"
 *
 * Локальная переменная:
 * row - номер выбранной строки.
*/
void FileLog::on_deleteFile_clicked()
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
 *
 * Локальные переменные:
 * row - номер выбранной строки;
 * file - путь к файлу в выбранной записи.
*/
void FileLog::on_copy_clicked()
{
    int row=ui->tvFiles->currentIndex().row();
    if(row>=0){
        QString file=filetable->index(row, filetable->fieldIndex(_::FILELOGNAME)).data().toString();
        QApplication::clipboard()->setText(file);
        QMessageBox::information(this, "Копирование", "Путь к файлу скопирован.");
    }
    else{
        QMessageBox::information(this, "Копирование", "Запись не выбрана.");
    }

}

/*Событие для сохранения изменений в записи
 * Локальная переменная:
 * record - запись с данными обновляемой или добавляемой записи.
*/
void FileLog::on_saveParm_clicked()
{
    QSqlRecord record=filetable->record();//Получение набора названий полей таблицы
    if(ui->leFiletableID->text()=="NULL"){//Заполнение записи данными
        record.remove(0);
        loadTable();
    }
    else{
        record.setValue(_::PARMLOGID, ui->leFiletableID->text().toInt());

    }

    record.setValue(_::PARMLOGLOG, ui->leLogID->text().toInt());
    record.setValue(_::PARMNAME, ui->cbNameParm->currentData());
    record.setValue(_::PARMLOGCOND, ui->cbCondParm->currentData());
    record.setValue(_::FILELOGNAME, idFile);


    if(ui->leFiletableID->text()=="NULL"){//Проверка наличия идентификатора записи
        //QMessageBox::information(this, "", QString("%1").arg(record.fieldName(3)));
        //QMessageBox::information(this, "", QString("%1").arg(record.value(_::FILELOGNAME).toString()));
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
void FileLog::on_tvFiles_doubleClicked(const QModelIndex &index)
{
    tablemapper->setCurrentModelIndex(index);
    QByteArray byarr=ui->leFileParm->toPlainText().toUtf8();
    idFile=getFileID(&byarr);
    ui->lrownum->setText("Запись №"+QString("%1").arg((index.row()+1)));
}

/*Событие очистки свзанных с таблицей элементов*/
void FileLog::on_newRow_clicked()
{
    idFile=-1;
    ui->leFiletableID->setText("NULL");
    ui->cbCondParm->setCurrentIndex(-1);
    ui->cbNameParm->setCurrentIndex(-1);
    ui->leFileParm->clear();
    ui->lrownum->setText("Новая запись");
}
