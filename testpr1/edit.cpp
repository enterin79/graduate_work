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

    //QMessageBox::aboutQt(this, "num log="+QString("%1").arg(curruentLog));
    try {
        QString id, name;
        model=currmodel;
        curruentLog=idLog;
        this->db=db;

        tablemapper=new QDataWidgetMapper(this);
        tablemapper->setModel(model);
        if(table=="equipment"){ //Соединение элементов формы редактирования с данными таблицы в зависимости от набора полей этой таблицы
            /*tablemapper->addMapping(ui->leNameEq, model->fieldIndex("nameequip"));
            tablemapper->addMapping(ui->leNote, model->fieldIndex("note"), "plainText");
            tablemapper->addMapping(ui->deFirstExpDate, model->fieldIndex("firstexpldate"));
            ui->gbTest->hide();
            ui->gbEquip->show();*/
            QSqlTableModel *temptable=new QSqlTableModel(this, *db);
            temptable->setTable("equipment");
            temptable->select();
            id="idequip";
            name="nameequip";
            ui->cbStructEq->setForeignKey(&id, &name, temptable);
            ui->cbStructEq->addItem("<нет>", "NULL");
            tablemapper->addMapping(ui->leNameEq, model->fieldIndex("nameequip"));
            tablemapper->addMapping(ui->leDescriptEq, model->fieldIndex("descriptionequip"), "plainText");
            tablemapper->addMapping(ui->cbStructEq, model->fieldIndex("equipment_nameequip_2"));
            ui->gbCond->hide();
            ui->gbLog->hide();
            ui->gbSolution->hide();
            ui->gbBreak->hide();
            ui->gbEquip->show();
        }
        else if(table=="condition"){
            /*id="id";
            text="nameequip";
            ui->cbEquipId->setForeignKey(&id, &text, model->relationModel(model->fieldIndex("nameequip")));
            tablemapper->addMapping(ui->leNameTest, model->fieldIndex("nametest"));
            tablemapper->addMapping(ui->deDateTest, model->fieldIndex("datetest"));
            tablemapper->addMapping(ui->leDescript, model->fieldIndex("description"), "plainText");
            tablemapper->addMapping(ui->cbEquipId, model->fieldIndex("nameequip"));
            ui->gbTest->show();
            ui->gbEquip->hide();*/
            tablemapper->addMapping(ui->leNameCond, model->fieldIndex("type"));
            tablemapper->addMapping(ui->sbLoadCond, model->fieldIndex("load"));
            ui->gbCond->show();
            ui->gbLog->hide();
            ui->gbSolution->hide();
            ui->gbBreak->hide();
            ui->gbEquip->hide();
        }
        else if(table=="solution"){
            tablemapper->addMapping(ui->leNameSolut, model->fieldIndex("namesol"));
            tablemapper->addMapping(ui->leDescriptSolut, model->fieldIndex("descriptionsol"), "plainText");
            ui->gbCond->hide();
            ui->gbLog->hide();
            ui->gbSolution->show();
            ui->gbBreak->hide();
            ui->gbEquip->hide();
        }
        else if(table=="breaking"){
            tablemapper->addMapping(ui->leCodeBreak, model->fieldIndex("code"));
            tablemapper->addMapping(ui->leNameBreak, model->fieldIndex("namebreak"));
            tablemapper->addMapping(ui->leDescriptBreak, model->fieldIndex("descriptionbreak"), "plainText");
            ui->gbCond->hide();
            ui->gbLog->hide();
            ui->gbSolution->hide();
            ui->gbBreak->show();
            ui->gbEquip->hide();
        }
        else if(table=="conditionlog"){
            /*temptable->setTable("equipment");
            temptable->select();*/
            id="idequip";
            name="nameequip";
            ui->cbEquip->setForeignKey(&id, &name, model->relationModel(model->fieldIndex("nameequip")));

            id="code";
            name="namebreak";
            ui->cbBreak->addItem("<нет>", "NULL");
            ui->cbBreak->setForeignKey(&id, &name, model->relationModel(model->fieldIndex("namebreak")), "STR");


            id="idcond";
            name="type";
            ui->cbCond->setForeignKey(&id, &name, model->relationModel(model->fieldIndex("type")));

            id="idsol";
            name="namesol";
            ui->cbSolut->addItem("<нет>", "NULL");
            ui->cbSolut->setForeignKey(&id, &name, model->relationModel(model->fieldIndex("namesol")));


            tablemapper->addMapping(ui->dtCurrTime, model->fieldIndex("currdatetime"));
            tablemapper->addMapping(ui->cbEquip, model->fieldIndex("nameequip"));
            tablemapper->addMapping(ui->cbBreak, model->fieldIndex("namebreak"));
            tablemapper->addMapping(ui->cbCond, model->fieldIndex("type"));
            tablemapper->addMapping(ui->cbSolut, model->fieldIndex("namesol"));
            tablemapper->addMapping(ui->rbUnnormalLog, model->fieldIndex("unnormal"));
            tablemapper->addMapping(ui->leDescriptLog, model->fieldIndex("descriptionlog"), "plainText");
            tablemapper->addMapping(ui->ledtSolutExec, model->fieldIndex("solutiondatetime"));

            ui->ledtSolutExec->hide();
            /*if(!ui->ledtSolutExec->text().isEmpty()){
                QDateTime dateTime = QDateTime::fromString(ui->ledtSolutExec->text(),"yyyy-MM-ddThh:mm:ss.zzz");
                ui->dtSolutExec->setDateTime(dateTime);
            }*/

            /*if(havesoldate){

            }*/

            ui->gbCond->hide();
            ui->gbLog->show();
            ui->gbSolution->hide();
            ui->gbBreak->hide();
            ui->gbEquip->hide();
        }
        if(table!="conditionlog"){
            ui->btLogFile->hide();
        }
        else{
            ui->btLogFile->show();
        }
        return 1;
    }  catch (...) {
        return 0;
    }
}

void Edit::PasteCurrTimeInto(QDateTimeEdit *widget)
{
    widget->setDateTime(QDateTime::currentDateTime());
}

/*Событие сохранения текущих изменений и закрытия формы редактирования
*/
void Edit::on_Apply_clicked()
{
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

void Edit::on_CurrDTPaste_clicked()
{
    PasteCurrTimeInto(ui->dtCurrTime);
}

void Edit::on_SolDTPaste_clicked()
{
    PasteCurrTimeInto(ui->dtSolutExec);
}


void Edit::on_dtSolutExec_dateTimeChanged(const QDateTime &dateTime)
{
    //QMessageBox::aboutQt(this, "dt");
    ui->ledtSolutExec->setText(dateTime.toString("yyyy-MM-ddThh:mm:ss.zzz"));
    //tablemapper->addMapping(ui->ledtSolutExec, ui->dtSolutExec);
    //QMessageBox::aboutQt(this);
}

void Edit::on_ledtSolutExec_textChanged(const QString &arg1)
{
    //QMessageBox::aboutQt(this, "le");
    if(ui->ledtSolutExec->text()!="NULL"){//&&ui->dtSolutExec->dateTime().toString()!=
        QDateTime dateTime = QDateTime::fromString(ui->ledtSolutExec->text(),"yyyy-MM-ddThh:mm:ss.zzz");
        ui->dtSolutExec->setDateTime(dateTime);
    }
}

void Edit::on_SolDTDelete_clicked()
{
    ui->ledtSolutExec->setText("NULL");
}

void Edit::on_btLogFile_clicked()
{
    file=new filelog;
    file->setParent(this, Qt::Window);
    file->setLog(curruentLog, db);
    file->setModal(true);
    file->show();
}
