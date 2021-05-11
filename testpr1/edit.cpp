#include "edit.h"
#include "ui_edit.h"
#include <QDebug>

/*Конструктор класса по умолчанию
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
    /*if(db!=nullptr)
        delete db;
    if(tablemapper!=nullptr)
        delete tablemapper;
    if(model!=nullptr)
        delete model;*/
    delete ui;
}


/*Метод для соединения данных таблицы с элементами формы редактирования
 *
 * Формальные параметры:
 * model - таблица, с которой происходит соединение;
 * table - название таблицы.
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

        if(table==BLOK){ //Соединение элементов формы редактирования с данными таблицы в зависимости от набора полей этой таблицы
            QSqlTableModel *temptable=new QSqlTableModel(this, *db);
            temptable->setTable("KA");
            temptable->select();
            id="NumberKA";
            name="NameKA";
            ui->cbBlokKA->setForeignKey(&id, &name, temptable, "STR");
            ui->cbBlokKA->setCurrentIndex(-1);

            tablemapper->addMapping(ui->leNameBlok, model->fieldIndex("NameBlok"));
            tablemapper->addMapping(ui->leBlokSerial, model->fieldIndex("SerialNumberBlok"));
            tablemapper->addMapping(ui->leBlokBISerial, model->fieldIndex("BIid"));

            ui->leBlokBISerial->hide();
            ui->leBlokBISerialCurr->hide();

            ui->gbParm->hide();
            ui->gbLog->hide();
            ui->gbSolution->hide();
            ui->gbKA->hide();
            ui->gbBlok->show();
            ui->gbBI->hide();
        }
        else if(table==BI){
            id="NumberKA";
            name="NameKA";
            ui->cbBIKA->setForeignKey(&id, &name, model->relationModel(model->fieldIndex("NameKA")));
            ui->cbBIKA->setCurrentIndex(-1);

            tablemapper->addMapping(ui->leBISerial, model->fieldIndex("SerialNumberBI"));
            tablemapper->addMapping(ui->leNameBI, model->fieldIndex("NameBI"));
            tablemapper->addMapping(ui->cbBIKA, model->fieldIndex("NameKA"));

            ui->gbParm->hide();
            ui->gbLog->hide();
            ui->gbSolution->hide();
            ui->gbKA->hide();
            ui->gbBlok->hide();
            ui->gbBI->show();
        }
        else if(table==SOL){
            tablemapper->addMapping(ui->leNameSolut, model->fieldIndex("NameSol"));
            tablemapper->addMapping(ui->leDescriptSolut, model->fieldIndex("DescrSol"), "plainText");

            ui->gbParm->hide();
            ui->gbLog->hide();
            ui->gbSolution->show();
            ui->gbKA->hide();
            ui->gbBlok->hide();
            ui->gbBI->hide();
        }
        else if(table==PARM){
            tablemapper->addMapping(ui->leNameParm, model->fieldIndex("NameParm"));
            tablemapper->addMapping(ui->leDescriptParm, model->fieldIndex("DescrParm"), "plainText");

            ui->gbParm->show();
            ui->gbLog->hide();
            ui->gbSolution->hide();
            ui->gbKA->hide();
            ui->gbBlok->hide();
            ui->gbBI->hide();
        }
        else if(table==KA){
            tablemapper->addMapping(ui->leNumberKA, model->fieldIndex("NumberKA"));
            tablemapper->addMapping(ui->leNameKA, model->fieldIndex("NameKA"));
            tablemapper->addMapping(ui->dtLaunchKA, model->fieldIndex("LaunchDateKA"));
            ui->gbParm->hide();
            ui->gbLog->hide();
            ui->gbSolution->hide();
            ui->gbKA->show();
            ui->gbBlok->hide();
            ui->gbBI->hide();
        }
        else if(table==LOG){

            QSqlTableModel *temptable=new QSqlTableModel(this, *db);
            temptable->setTable("Blok");
            temptable->select();
            id="idBlok";
            name="SerialNumberBlok";
            ui->cbEquip->setForeignKey(&id, &name, temptable);

            id="idSol";
            name="NameSol";
            ui->cbSolut->addItem("<нет>", "NULL");
            ui->cbSolut->setForeignKey(&id, &name, model->relationModel(model->fieldIndex("NameSol")));


            tablemapper->addMapping(ui->dtCurrTime, model->fieldIndex("DateRec"));
            tablemapper->addMapping(ui->cbEquip, model->fieldIndex("BlokId"));
            tablemapper->addMapping(ui->cbSolut, model->fieldIndex("NameSol"));
            tablemapper->addMapping(ui->leDescriptLog, model->fieldIndex("DescrRec"), "plainText");
            tablemapper->addMapping(ui->ledtSolutExec, model->fieldIndex("DateSol"));

            ui->ledtSolutExec->hide();

            ui->gbParm->hide();
            ui->gbLog->show();
            ui->gbSolution->hide();
            ui->gbKA->hide();
            ui->gbBlok->hide();
            ui->gbBI->hide();
        }
        else return 0;
        if(table!=LOG){
            ui->btLogFile->hide();
        }
        else{
            ui->btLogFile->show();
        }
        return 1;
}
/*Событие для вставки текущей даты в виджет*/
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
например при случайном заполнении*/
void Edit::on_dtSolutExec_dateTimeChanged(const QDateTime &dateTime)
{
    ui->ledtSolutExec->setText(dateTime.toString("yyyy-MM-ddThh:mm:ss.zzz"));
}
/*Заполнение элемента datetimepicker датой из ячейки даты выполнения решения в таблице Прием данных*/
void Edit::on_ledtSolutExec_textChanged(const QString &arg1)
{
    if(arg1!="NULL"){
        QDateTime dateTime = QDateTime::fromString(ui->ledtSolutExec->text(),"yyyy-MM-ddThh:mm:ss.zzz");
        ui->dtSolutExec->setDateTime(dateTime);
    }
}
/*Удаление даты из элемента, связанного с ячейкой даты выполнения решения в таблице Прием данных*/
void Edit::on_SolDTDelete_clicked()
{
    ui->ledtSolutExec->setText("NULL");
}
/*Просмотр данных таблицы Состояние парамеров для выбранной записи Прием данных*/
void Edit::on_btLogFile_clicked()
{
    file=new filelog;
    file->setParent(this, Qt::Window);
    file->setLog(curruentLog, db);
    file->setModal(true);
    file->show();
}
/*Событие загрузки БИ для выбранного КА*/
void Edit::on_cbBlokKA_currentIndexChanged(int index)
{
    if(index!=-1){
        QString id, name;
        QSqlTableModel *temptable=new QSqlTableModel(this, *db);
        temptable->setTable("BI");
        temptable->select();
        temptable->setFilter("kanumber='"+ui->cbBlokKA->currentData().toString()+"'");
        ui->cbBlokBI->clear();
        id="idBI";
        name="NameBI";
        ui->cbBlokBI->setForeignKey(&id, &name, temptable);
        ui->cbBlokBI->setCurrentIndex(-1);
        ui->cbBlokBI->setData(ui->leBlokBISerial->text());
    }
    else{
        ui->cbBlokBI->clear();
    }
}
/*Событие изменения */
void Edit::on_cbBlokBI_currentIndexChanged(int index)
{
    QString currdata=ui->cbBlokBI->currentData().toString();
    ui->leBlokBISerialCurr->setText(currdata);
}
/*Событие для выбора КА по идентификатору указанного БИ*/
void Edit::on_leBlokBISerial_textChanged(const QString &arg1)
{
    if(arg1!="NULL"&&arg1!=ui->cbBlokBI->currentData().toString()){
        ui->cbBlokKA->setCurrentIndex(-1);
        QString name;
        QSqlTableModel *temptable=new QSqlTableModel(this, *db);
        temptable->setTable("BI");
        temptable->select();
        temptable->setFilter("idBI="+ui->leBlokBISerial->text());
        name=temptable->index(0, temptable->fieldIndex("kanumber")).data().toString();
        ui->cbBlokKA->setData(name);
    }
}
