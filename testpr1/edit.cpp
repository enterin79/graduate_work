#include "edit.h"
#include "ui_edit.h"
#include <QDebug>

/*Конструктор класса по умолчанию
 *
 * Формальный параметр:
 * parent - указатель на родительский элемент.
*/
Edit::Edit(QWidget *parent) :
    QDialog(parent),
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
 * currmodel - таблица, с которой происходит соединение;
 * table - название таблицы;
 * idLog - идентификатор записи, необходим только при работе с таблицей "Прием данных";
 * db - экземпляр соединения с базой данных.
 *
 * Локальные переменные:
 * id - данные для записей внешнего ключа в элементе выбора;
 * text - текст, соотвествующий данным, для каждой записи внешнего ключа в элементе выбора.
*/
bool Edit::setModelTable(QSqlRelationalTableModel *currmodel, QString table, int idLog, QSqlDatabase *db )
{
        QString id, name;
        model=currmodel;
        curruentLog=idLog;
        this->db=db;

        tablemapper=new QDataWidgetMapper(this);
        tablemapper->setModel(model);

        if(table==_::BLOK){ //Соединение элементов формы редактирования с данными таблицы в зависимости от набора полей этой таблицы
            QSqlTableModel *temptable=new QSqlTableModel(this, *db);
            temptable->setTable(_::KA);
            temptable->select();
            id=_::KAID;
            name=_::KANAME;
            ui->cbBlokKA->setForeignKey(&id, &name, temptable, "STR");
            ui->cbBlokKA->setCurrentIndex(-1);

            tablemapper->addMapping(ui->leNameBlok, model->fieldIndex(_::BLOKNAME));
            tablemapper->addMapping(ui->leBlokSerial, model->fieldIndex(_::BLOKSERIAL));
            tablemapper->addMapping(ui->leBlokBISerial, model->fieldIndex(_::BLOKBI));

            //ui->leBlokBISerial->hide();
            //ui->leBlokBISerialCurr->hide();

            ui->gbParm->hide();
            ui->gbLog->hide();
            ui->gbSolution->hide();
            ui->gbKA->hide();
            ui->gbBlok->show();
            ui->gbBI->hide();
            ui->gbFile->hide();
        }
        else if(table==_::BI){
            id=_::KAID;
            name=_::KANAME;
            ui->cbBIKA->setForeignKey(&id, &name, model->relationModel(model->fieldIndex(_::KANAME)));
            ui->cbBIKA->setCurrentIndex(-1);

            tablemapper->addMapping(ui->leBISerial, model->fieldIndex(_::BISERIAL));
            tablemapper->addMapping(ui->leNameBI, model->fieldIndex(_::BINAME));
            tablemapper->addMapping(ui->cbBIKA, model->fieldIndex(_::KANAME));

            ui->gbParm->hide();
            ui->gbLog->hide();
            ui->gbSolution->hide();
            ui->gbKA->hide();
            ui->gbBlok->hide();
            ui->gbBI->show();
            ui->gbFile->hide();
        }
        else if(table==_::SOL){
            tablemapper->addMapping(ui->leNameSolut, model->fieldIndex(_::SOLNAME));
            tablemapper->addMapping(ui->leDescriptSolut, model->fieldIndex(_::SOLDESC), "plainText");

            ui->gbParm->hide();
            ui->gbLog->hide();
            ui->gbSolution->show();
            ui->gbKA->hide();
            ui->gbBlok->hide();
            ui->gbBI->hide();
            ui->gbFile->hide();
        }
        else if(table==_::PARM){
            tablemapper->addMapping(ui->leNameParm, model->fieldIndex(_::PARMNAME));
            tablemapper->addMapping(ui->leDescriptParm, model->fieldIndex(_::PARMDESC), "plainText");

            ui->gbParm->show();
            ui->gbLog->hide();
            ui->gbSolution->hide();
            ui->gbKA->hide();
            ui->gbBlok->hide();
            ui->gbBI->hide();
            ui->gbFile->hide();
        }
        else if(table==_::KA){
            tablemapper->addMapping(ui->leNumberKA, model->fieldIndex(_::KAID));
            tablemapper->addMapping(ui->leNameKA, model->fieldIndex(_::KANAME));
            tablemapper->addMapping(ui->dtLaunchKA, model->fieldIndex(_::KADATE));

            ui->gbParm->hide();
            ui->gbLog->hide();
            ui->gbSolution->hide();
            ui->gbKA->show();
            ui->gbBlok->hide();
            ui->gbBI->hide();
            ui->gbFile->hide();
        }
        else if(table==_::LOG){

            QSqlTableModel *temptable=new QSqlTableModel(this, *db);
            temptable->setTable(_::BLOK);
            temptable->select();
            id=_::BLOKID;
            name=_::BLOKSERIAL;
            ui->cbEquip->setForeignKey(&id, &name, temptable);

            id=_::SOLID;
            name=_::SOLNAME;
            ui->cbSolut->addItem("<нет>", "NULL");
            ui->cbSolut->setForeignKey(&id, &name, model->relationModel(model->fieldIndex(_::SOLNAME)));


            tablemapper->addMapping(ui->dtCurrTime, model->fieldIndex(_::LOGDATE));
            tablemapper->addMapping(ui->cbEquip, model->fieldIndex(_::LOGBLOK));
            tablemapper->addMapping(ui->cbSolut, model->fieldIndex(_::SOLNAME));
            tablemapper->addMapping(ui->leDescriptLog, model->fieldIndex(_::LOGDESC), "plainText");
            tablemapper->addMapping(ui->ledtSolutExec, model->fieldIndex(_::LOGSOLDATE));

            ui->ledtSolutExec->hide();

            ui->gbParm->hide();
            ui->gbLog->show();
            ui->gbSolution->hide();
            ui->gbKA->hide();
            ui->gbBlok->hide();
            ui->gbBI->hide();
            ui->gbFile->hide();
        }
        else if(table==_::FILELOG){
            tablemapper->addMapping(ui->leFilePath, model->fieldIndex(_::FILELOGNAME), "plainText");

            ui->gbParm->hide();
            ui->gbLog->hide();
            ui->gbSolution->hide();
            ui->gbKA->hide();
            ui->gbBlok->hide();
            ui->gbBI->hide();
            ui->gbFile->show();
        }
        else return 0;
        if(table!=_::LOG){
            ui->btLogFile->hide();
        }
        else{
            ui->btLogFile->show();
        }
        return 1;
}
/*Событие для вставки текущей даты в виджет
 *
 * Формальный параметр:
 * widget - указатель на виджет, куда необходимо вставить текущую дату и время.
*/
void Edit::pasteCurrTimeInto(QDateTimeEdit *widget)
{
    widget->setDateTime(QDateTime::currentDateTime());
}

/*Событие сохранения текущих изменений и закрытия формы редактирования
*/
void Edit::on_Apply_clicked()
{
    ui->leBlokBISerial->setText(ui->leBlokBISerialCurr->text());

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

/*Событие для вствки текущей даты в поле для даты получения данных в таблице Прием данных*/
void Edit::on_CurrDTPaste_clicked()
{
    pasteCurrTimeInto(ui->dtCurrTime);
}
/*Событие для вствки текущей даты в поле для даты выполнения решения в таблице Прием данных*/
void Edit::on_SolDTPaste_clicked()
{
    pasteCurrTimeInto(ui->dtSolutExec);
}

/*Заполнение элемента, связанного с ячейкой даты выполнения решения в таблице Прием данных
это необходимо ввиду отсутствия прямой связи между этой ячейкой и полем для даты.
связь через mapper не позволяет удалить данные из этого поля,
например при случайном заполнении
* Формальный параметр:
* dateTime - текущее значение элемента.
*/
void Edit::on_dtSolutExec_dateTimeChanged(const QDateTime &dateTime)
{
    ui->ledtSolutExec->setText(dateTime.toString("yyyy-MM-ddThh:mm:ss.zzz"));
}
/*Событие для изменения даты в элементе datetimepicker
 * Формальный параметр:
 * arg1 - текущее значение элемента.
*/
void Edit::on_ledtSolutExec_textChanged(const QString &arg1)
{
    if(arg1!="NULL"){
        QDateTime dateTime = QDateTime::fromString(ui->ledtSolutExec->text(),"yyyy-MM-ddThh:mm:ss.zzz");
        ui->dtSolutExec->setDateTime(dateTime);
    }
}
/*событие для удаления значения даты*/
void Edit::on_SolDTDelete_clicked()
{
    ui->ledtSolutExec->setText("NULL");
    ui->dtSolutExec->setDateTime(QDateTime::fromString("01.01.1900 0:00:00","dd.MM.yyyy hh:mm:ss"));
}
/*Событие загрузки записей из таблицы "Состояние параметров" для выбранной записи таблицы "Прием данных"*/
void Edit::on_btLogFile_clicked()
{
    file=new filelog;
    file->setParent(this, Qt::Window);
    file->setLog(curruentLog, db);
    file->setModal(true);
    file->show();
}
/*Событие для загрзки списка БИ, соответствующих указанному КА
 * Формальный параметр:
 * index - индекс выбранного значения.
*/
void Edit::on_cbBlokKA_currentIndexChanged(int index)
{
    if(index!=-1){//Выполнение загрузки, если КА выбран
        QString id, name;
        QSqlTableModel *temptable=new QSqlTableModel(this, *db);
        temptable->setTable(_::BI);
        temptable->select();
        temptable->setFilter(QString(_::BIKA)+"='"+ui->cbBlokKA->currentData().toString()+"'");
        ui->cbBlokBI->clear();
        id=_::BIID;
        name=_::BINAME;
        ui->cbBlokBI->setForeignKey(&id, &name, temptable);
        ui->cbBlokBI->setCurrentIndex(-1);
        ui->cbBlokBI->newSetData(ui->leBlokBISerial->text());
    }
    else{//Очистка списка доступных БИ
        ui->cbBlokBI->clear();
    }
}
/*Событие изменения данных в элементе, свзанном со столбцом родительского устройства в таблице "Блок"
 * Формальный параметр:
 * index - индекс выбранного значения.
*/
void Edit::on_cbBlokBI_currentIndexChanged(int index)
{
    QString currdata=ui->cbBlokBI->currentData().toString();
    ui->leBlokBISerialCurr->setText(currdata);
}
/*Событие для загрузки данных о родительских устройствах по данным выбранной записи таблицы "Блок"
 * Формальный параметр:
 * arg1 - текущее значение элемента.
*/
void Edit::on_leBlokBISerial_textChanged(const QString &arg1)
{
    if(arg1!="NULL"&&arg1!=ui->cbBlokBI->currentData().toString()){
        ui->cbBlokKA->setCurrentIndex(-1);
        QString name;
        QSqlTableModel *temptable=new QSqlTableModel(this, *db);
        temptable->setTable(_::BI);
        temptable->select();
        temptable->setFilter(QString(_::BIID)+"="+ui->leBlokBISerial->text());
        name=temptable->index(0, temptable->fieldIndex(_::BIKA)).data().toString();
        ui->cbBlokKA->newSetData(name);
    }
}

/*Событие для выбора загружаемого файла*/
void Edit::on_ChooseFile_clicked()
{
    QString file=QFileDialog::getOpenFileName(this,
                                              QString::fromUtf8("Открыть файл"),
                                              QDir::currentPath(),
                                              "(*.txt);;All files (*.*)"
                                              );
    ui->leFilePath->setText(file);
}
