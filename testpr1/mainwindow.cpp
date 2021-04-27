#include "mainwindow.h"
#include "ui_mainwindow.h"
/*Конструктор класса по умолчанию
 *
 * Формальный параметр:
 * parent - указатель на родительский элемент.
*/
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timerScroll=new QTimer();
    timerScroll->setInterval(1000);
    connect(timerScroll, SIGNAL(timeout()), this, SLOT(setscroll()));

    ui->LogSlider->setMinimum(0);
    ui->LogSlider->setMaximum(600);
    ui->LogSlider->setTickInterval(1);
    ui->LogSlider->setTickPosition(QSlider::TickPosition::TicksRight);



    tryconnect();
}

/*Деструктор класса
*/
MainWindow::~MainWindow()
{
    if(dbworking!=nullptr)
        delete dbworking;
    delete ui;
}

/*Функция для сохранеия внесенных в таблицу изменений
 *
 * Формальный параметр:
 * message - текст для дополнения сообщения.
*/
bool MainWindow::saveChanges(QString message)
{
    if(dbworking->savechanges()==Enumerr::SAVINGOK){   //Проверка выполнения сохранения изменений
        ui->statusbar->showMessage("Операция ("+message+") выполнена успешно "+QTime::currentTime().toString("HH:mm:ss"));
        return 1;
    }
    else{
        ui->statusbar->showMessage("Ошибка выполнения операции ("+message+") "+QTime::currentTime().toString("HH:mm:ss"));
        QMessageBox::critical(this, "Ошибка", "Ошибка изменения данных! Текст ошибки: "+dbworking->generalmodel->lastError().text());
        return 0;
    }
}

void MainWindow::tryconnect()
{
    int answer=QMessageBox::question(this,"Подключение", "Подключение к базе данных. Нажмите Yes, чтобы подключиться.");;
    if(dbworking!=nullptr)
        delete dbworking;
    dbworking=new dbWorking();
    if(dbworking->connection()==Enumerr::CONNECTIONOK&&answer==QMessageBox::Button::Yes){  //Выполнение соединения с базой данных с текущими реквизитами пользователя
        ui->statusbar->showMessage("Соединение установлено");
        dbworking->generalmodel=new UpgradedModel(this,dbworking->db);   //Подготовка интерфейса
        ui->cbChooseTable->setModel(dbworking->choosingmodel);
        ui->cbChooseTable->setModelColumn(2);
        return;
    }
    else {
        if(answer==QMessageBox::Button::Yes){
            QMessageBox::critical(this, "Ошибка подключения", "Произошла ошибка подключения!");
            tryconnect();
        }
        else throw("connecting error");
    }
}

/*Процедура для выполнения выхода из программы при возникновении критической ошибки
*/
void MainWindow::criticalerror(QString message)
{
    //qCritical(loggerCritical())<<"Critical error "<<dbworking->generalmodel->lastError().text();
    QMessageBox::critical(this, "Ошибка", message+" Переподключение к базе данных.");
    tryconnect();
}

void MainWindow::setscroll()
{
    //QMessageBox::information(this,"lol", "lol");
    ui->LogSlider->setValue(ui->LogSlider->value()+1);
}

/*Событие для загрузки новой таблицы после ее выбора
 *
 * Формальный параметр:
 * index - индекс записи о выбранной таблице в элементе выбора.
 *
 * Локальные переменные:
 * currfields - массив синонимов полей для выбранной таблицы;
 * fields - набор данных о реальных полях таблицы.
*/
void MainWindow::on_cbChooseTable_currentIndexChanged(int index)
{
    QSqlRecord fields;
    QString primkey;
    QList<QString> forgnkey, forgntable, forgnprimkey, forgntext;
    int relstatus=0;
    bool hideFKcol=true;
    //Enumerr loadok=Enumerr::CONNECTIONERROR;
    dbworking->currtable=dbworking->choosingmodel->record(index).value("nametable").toString();
    dbworking->fieldsynonims.clear();
    on_Retry_clicked();
    /*if(dbworking->currtable=="equipment"){  //Определение выбранной таблицы
        dbworking->fieldsynonims.push_back("Название оборудования");  //Запись синонимов названий полей
        dbworking->fieldsynonims.push_back("Дата запуска");
        dbworking->fieldsynonims.push_back("Описание");
        primkey="id";
        //loadok=dbworking->chooseTable(&primkey, &table);
    }
    else if(dbworking->currtable=="test"){
        dbworking->fieldsynonims.push_back("Название теста");
        dbworking->fieldsynonims.push_back("Дата тестирования");
        dbworking->fieldsynonims.push_back("Описание");
        dbworking->fieldsynonims.push_back("Тестируемое оборудование");
        primkey="id";
        forgnkey="ideqip";
        forgntable="equipment";
        forgnprimkey="id";
        forgntext="nameequip";
        relstatus=1;
        ui->tvModel->setItemDelegate(new QSqlRelationalDelegate(ui->tvModel));
    }*/


    if(dbworking->currtable=="conditionlog"){
        dbworking->fieldsynonims.push_back("Дата и время");
        dbworking->fieldsynonims.push_back("Оборудование");
        dbworking->fieldsynonims.push_back("Состояние");
        dbworking->fieldsynonims.push_back("Ошибка");
        dbworking->fieldsynonims.push_back("Решение");
        dbworking->fieldsynonims.push_back("Время решения");
        dbworking->fieldsynonims.push_back("Отклонение от нормы");
        dbworking->fieldsynonims.push_back("Примечание");

        /*dbworking->realfieldnames.push_back("CurrDateTime");
        dbworking->realfieldnames.push_back("Equipment");
        dbworking->realfieldnames.push_back("Condition");
        dbworking->realfieldnames.push_back("Breaking");
        dbworking->realfieldnames.push_back("Solution");
        dbworking->realfieldnames.push_back("SolutionDateTime");*/

        primkey="CurrDateTime";

        forgnkey.push_back("EquipmentId");
        forgntable.push_back("Equipment");
        forgnprimkey.push_back("idEquip");
        forgntext.push_back("NameEquip");

        forgnkey.push_back("conditionid");
        forgntable.push_back("Condition");
        forgnprimkey.push_back("idcond");
        forgntext.push_back("type");

        forgnkey.push_back("breakingid");
        forgntable.push_back("Breaking");
        forgnprimkey.push_back("Code");
        forgntext.push_back("namebreak");

        forgnkey.push_back("solutionid");
        forgntable.push_back("Solution");
        forgnprimkey.push_back("idsol");
        forgntext.push_back("namesol");

        relstatus=4;
        //relstatus=3;
        //hideFKcol=false;
        ui->tvModel->setItemDelegate(new QSqlRelationalDelegate(ui->tvModel));

    }
    else if(dbworking->currtable=="equipment"){
        dbworking->fieldsynonims.push_back("Название");
        dbworking->fieldsynonims.push_back("Описание");
        dbworking->fieldsynonims.push_back("Входит в");
        primkey="idequip";
        forgnkey.push_back("equipstruct");
        forgntable.push_back("equipment");
        forgnprimkey.push_back("idequip");
        forgntext.push_back("nameequip");
        relstatus=1;
        ui->tvModel->setItemDelegate(new QSqlRelationalDelegate(ui->tvModel));
    }
    else if(dbworking->currtable=="condition"){
        dbworking->fieldsynonims.push_back("Состояние");
        dbworking->fieldsynonims.push_back("Загрузка(%)");
        primkey="id";
    }
    else if(dbworking->currtable=="breaking"){
        dbworking->fieldsynonims.push_back("Название");
        dbworking->fieldsynonims.push_back("Описание");
        primkey="code";
    }
    else if(dbworking->currtable=="solution"){
        dbworking->fieldsynonims.push_back("Название");
        dbworking->fieldsynonims.push_back("Описание");
        primkey="id";
    }
    else{
        criticalerror("Ошибка загрузки таблицы!");
        return;
    }
    if(dbworking->chooseTable(&primkey, forgnkey, forgntable, forgnprimkey, forgntext, relstatus, hideFKcol)==Enumerr::READINGERROR) {   //Проверка корректности загрузки данных
        //dbworking->setlog(QDateTime::currentDateTime(), Enumerr::READERROR);
        criticalerror("Ошибка загрузки таблицы!");
        return;
    }

    ui->tvModel->setModel(dbworking->generalmodel); //Отображение загруженной таблицы

    if(hideFKcol){
        ui->tvModel->hideColumn(0);
    }
    ui->tvModel->resizeColumnsToContents();

    fields=dbworking->generalmodel->record();
    ui->cbSelectColumn->clear();
    for(int i=hideFKcol; i<fields.count();i++){ //Заполнение элемента определения столбца для операции выборки текущими названиями полей
        ui->cbSelectColumn->addItem(dbworking->fieldsynonims[i-hideFKcol], fields.fieldName(i));//dbworking->fieldsynonims[i-hideFKcol] fields.fieldName(i)
        ui->cbSelectColumn->setCurrentIndex(0);
    }

    if(dbworking->currtable=="conditionlog"){
        /*QSqlTableModel *temptable=new QSqlTableModel(this, dbworking->db);
        temptable->setTable("equipment");
        temptable->select();
        QString id, name;
        id="idequip";
        name="nameequip";
        /ComboBoxDelegate *cbtable=new ComboBoxDelegate();
        cbtable->model=temptable;
        cbtable->data=id;
        cbtable->text=name;
        ui->tvModel->setItemDelegateForColumn(1, cbtable);/
        //ui->cbEquipment->clear();
        ui->cbEquipment->setForeignKey(&id, &name, temptable);
        mapper=new QDataWidgetMapper(this);
        mapper->setModel(dbworking->generalmodel);
        mapper->addMapping(ui->cbEquipment, dbworking->generalmodel->fieldIndex("equipmentid"));
        mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
        connect(ui->tvModel->selectionModel(), &QItemSelectionModel::currentChanged,
                this, &MainWindow::on_tvModel_clicked);
        ui->gbEquipShow->show();*/
        ui->gbEquipShow->hide();
        //ui->gbTimeScroll->show();
        //ui->cbEquipment->setCurrentIndex(-1);
        ui->dtScroll->setDateTime(QDateTime::currentDateTime());
        ui->LogSlider->setValue(0);
        scrollingValue=0;
    }
    else{
       ui->gbEquipShow->hide();
       ui->gbTimeScroll->hide();
    }

    //qDebug()<<dbworking->currtable;
}

/*Событие для сохранения внесенных изменений
*/
void MainWindow::on_SaveButton_clicked()
{
    saveChanges("добавление/обновление");
}

/*Событие для отмены внесенных изменений
*/
void MainWindow::on_RevertButton_clicked()
{
    dbworking->generalmodel->revertAll();
}

/*Событие для вызова формы редактирования записи
 *
 * Формальный параметр:
 * index - индекс записи, на которой произошло событие.
*/
void MainWindow::on_tvModel_doubleClicked(const QModelIndex &index)
{
    edit=new Edit();    //Создание нового экземпляра формы редактирования
    edit->setParent(this, Qt::Window);
    connect(edit, SIGNAL(saveYes(bool)), this, SLOT(takesave(bool)));   //Соединение сигнала с формы редактирования и основной формы для сохранения изменений
    //if(index.column()!=dbworking->generalmodel->fieldIndex("nameequip")||(dbworking->currtable!="test")){   //Проверка столбца, на котором произошло событие. Это необходимо, чтобы не возникало проблемы про смене значения внешнего ключа в записи без вызова формы редактирования
        edit->setModelTable(dbworking->generalmodel, dbworking->currtable, dbworking->generalmodel->index(index.row(), dbworking->generalmodel->fieldIndex("idLog")).data().toInt() ,&dbworking->db); //Передача в форму реактирования данных о текущей таблице
        edit->tablemapper->setCurrentModelIndex(index); //Передача в форму редактирования данных о текущей записи для взаимодействии элементов в разных окнах
        edit->setModal(true);
        edit->show();   //Отображение формы редактирования
    //}


    /*if(dbworking->currtable=="conditionlog"&&(index.column()==dbworking->generalmodel->fieldIndex("currdatetime")||index.column()==dbworking->generalmodel->fieldIndex("solutiondatetime"))){
         dbworking->generalmodel->setData(index, QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm:ss"));
    }*/
}

/*Событие для добавления строки в текущую таблицу
*/
void MainWindow::on_Add_clicked()
{
    dbworking->generalmodel->insertRow(dbworking->generalmodel->rowCount());
}

/*Слот для сохранения изменений таблицы из формы редактирования
*/
void MainWindow::takesave(bool yes)
{
    //qDebug()<<"here "<<yes;
    if(yes) on_SaveButton_clicked();
}

/*Событие для удаления указанной строки
 *
 * Локальная переменная:
 * row - номер удаляемой строки.
*/
void MainWindow::on_Delete_clicked()
{
    int row=ui->tvModel->currentIndex().row();
    if(row>=0){ //Проверка номера удаляемой строки
        if(!dbworking->generalmodel->removeRow(row)){   //Проверка корректности удаления строки
            QMessageBox::critical(this, "Ошибка", "Ошибка удаления записи!");
        }
        else{
            int answer=QMessageBox::question(this,"Подтверждение удаления", "Вы действительно хотите удалить запись? Действие невозможно отменить.");
            if(answer==QMessageBox::Button::Yes) saveChanges("удаление");
        }
    }
    else{
        QMessageBox::critical(this, "Ошибка", "Удаляемая строка не выбрана.");
    }
}

/*Событие для создания выборки в сооствиии с указанными условиями
 *
 * Локлальная переменная:
 * selectionquery - текст выборки.
*/
void MainWindow::on_Search_clicked()
{
    QString selectionquery;

    QSqlQuery *tempquery=new QSqlQuery();
    tempquery->prepare("select idequip from equipment where nameequip='"+ui->teDecript->toPlainText()+"'");
    //tempquery->bindValue(":nameequipment", ui->teDecript->toPlainText());
    tempquery->exec();
    tempquery->first();

    if(dbworking->currtable=="equipment"){
        selectionquery="equipment.";
        if(ui->cbSelectColumn->currentText()!="Входит в"){
            selectionquery=selectionquery+'"'+ui->cbSelectColumn->currentData().toString()+'"'+"='"+ui->teDecript->toPlainText()+"'";//dbworking->currtable+"."+
        }
        else{

            selectionquery=selectionquery+"equipstruct="+tempquery->value(0).toString();

        }
    }
    else if(dbworking->currtable=="conditionlog"){
        if(ui->cbSelectColumn->currentText()=="Оборудование"&&tempquery->isValid()){
            selectionquery="equipmentid="+tempquery->value(0).toString();
        }
        else{
            selectionquery='"'+ui->cbSelectColumn->currentData().toString()+'"'+"='"+ui->teDecript->toPlainText()+"'";//dbworking->currtable+"."+
        }
    }
    else{
        selectionquery='"'+ui->cbSelectColumn->currentData().toString()+'"'+"='"+ui->teDecript->toPlainText()+"'";//dbworking->currtable+"."+
    }

    qDebug()<<selectionquery;
    //qDebug()<<"here";
    dbworking->generalmodel->setFilter(selectionquery.toUtf8());    //Выполнение выборки
    if(dbworking->generalmodel->rowCount()==0){ //Проверка наличия записей в выборке
        on_cbChooseTable_currentIndexChanged(ui->cbChooseTable->currentIndex());    //Возвращение полного отображения таблицы при отсуствии результатов поиска
        QMessageBox::critical(this, "Ошибка", "Ничего не найдено!");
        ui->teDecript->setText("");
    }
}

/*Событие для восстановления полного отображения таблицы после выборки
*/
void MainWindow::on_RevertTable_clicked()
{
    on_cbChooseTable_currentIndexChanged(ui->cbChooseTable->currentIndex());
}

/*void MainWindow::on_Reconnect_clicked()
{
    tryconnect();
    QMessageBox::information(this, "Уведомление", "Переподключение выполнено.");
}*/

void MainWindow::on_tvModel_clicked(const QModelIndex &index)
{
    //mapper->setCurrentIndex(index.row());
}

void MainWindow::on_LogEqSave_clicked()
{
    //mapper->submit();
    saveChanges("обновление");
}

void MainWindow::on_StartStopScroll_clicked()
{
    if(!timerScroll->isActive()){
        timerScroll->start();
    }
    else{
        timerScroll->stop();
    }
}

void MainWindow::on_LogSlider_valueChanged(int value)
{
    /*QDateTime dtcurr=ui->dtScroll->dateTime();
    dtcurr=dtcurr.addSecs(1);*/
    //QMessageBox::information(this,"lol", dtcurr.toString("dd.MMM.YYYY hh:mm:ss"));
    if(value>scrollingValue){
        //ui->dtScroll->setDateTime(selectedDT->addSecs(3));
        *selectedDT=ui->dtScroll->dateTime().addSecs(value);
    }
    else if(value<scrollingValue){
        //ui->dtScroll->setDateTime(selectedDT->addSecs(-3));
        *selectedDT=ui->dtScroll->dateTime().addSecs(-value);
    }
    scrollingValue=value;
    QString str="currdatetime<='"+selectedDT->toString("yyyy-MM-ddThh:mm:ss.zzz")+"' and currdatetime>='"+ui->dtScroll->dateTime().toString("yyyy-MM-ddThh:mm:ss.zzz")+"'";
    //qDebug()<<str;
    dbworking->generalmodel->setFilter(str);
    ui->timelabel->setText(selectedDT->toString("dd.MM.yyyy hh:mm:ss"));

}

void MainWindow::on_dtScroll_dateTimeChanged(const QDateTime &dateTime)
{
    selectedDT=new QDateTime(dateTime);
    on_Retry_clicked();
    ui->timelabel->setText(selectedDT->toString("dd.MM.yyyy hh:mm:ss"));

}

void MainWindow::on_Retry_clicked()
{
    //ui->dtScroll->setDateTime(selectedDT->addSecs(-(ui->LogSlider->value())+1));
    ui->LogSlider->setValue(0);
    if(timerScroll->isActive()){
        timerScroll->stop();
    }
}

void MainWindow::on_RetryConnection_triggered()
{
    tryconnect();
    QMessageBox::information(this, "Уведомление", "Переподключение выполнено.");
}
