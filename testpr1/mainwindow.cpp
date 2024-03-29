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

    timerScroll=new QTimer();//Настройка таймера и элемента прокуртки(скроллера)
    timerScroll->setInterval(1000);
    connect(timerScroll, SIGNAL(timeout()), this, SLOT(setScroll()));
    ui->LogSlider->setMinimum(0);
    ui->LogSlider->setMaximum(30);
    ui->LogSlider->setTickInterval(1);
    ui->LogSlider->setTickPosition(QSlider::TickPosition::TicksRight);

    tryConnect();//Подключение к базе данных
}

/*Деструктор класса
*/
MainWindow::~MainWindow()
{
    if(dbworking!=nullptr)
        delete dbworking;
    if(timerScroll!=nullptr)
        delete timerScroll;
    if(selectedDT!=nullptr)
        delete selectedDT;
    delete ui;
}

/*Функция для сохранеия внесенных в таблицу изменений
 *
 * Формальный параметр:
 * message - текст для дополнения сообщения.
*/
bool MainWindow::saveChanges(QString message)
{
    if(dbworking->saveChangesDB()==Enumerr::SAVINGOK){//Проверка выполнения сохранения изменений
        if(nametable==_::LOG||nametable==_::BLOK) {//Загрузка представления для необходимых таблиц
            dbworking->loadTemp(1);
        }
        ui->statusbar->showMessage("Операция ("+message+") выполнена успешно "+QTime::currentTime().toString("HH:mm:ss"));
        return 1;
    }
    else{
        on_RevertButton_clicked();//Отмена всех изменений и перезагрузка таблиц
        ui->statusbar->showMessage("Ошибка выполнения операции ("+message+") "+QTime::currentTime().toString("HH:mm:ss"));
        QMessageBox::critical(this, "Ошибка", "Ошибка изменения данных! Текст ошибки: "+dbworking->generalmodel->lastError().text());
        return 0;
    }
}
/*Процедура для подключения к базе данных
 *
 * Локальная переменная:
 * answer - индикатор ответа пользователя на вопрос о подключении к базе.
*/
void MainWindow::tryConnect()
{
    int answer=QMessageBox::question(this,"Подключение", "Подключение к базе данных. Нажмите Yes, чтобы подключиться.");//Получение подтверждения на подключение БД
    if(dbworking!=nullptr)//Удаление предыдущего указателя класс работы с базой
        delete dbworking;
    dbworking=new dbWorking();//Создание нового экземпляра класса работы с базой
    if(dbworking->connection()==Enumerr::CONNECTIONOK&&answer==QMessageBox::Button::Yes){  //Выполнение соединения с базой данных
        ui->statusbar->showMessage("Соединение установлено");
        dbworking->generalmodel=new UpgradedModel(this,dbworking->db);//Подготовка интерфейса и загрузка таблиц
        dbworking->tempmodel=new QSqlQueryModel;
        ui->cbChooseTable->setModel(dbworking->choosingmodel);
        ui->cbChooseTable->setModelColumn(2);
        return;
    }
    else {
        if(answer==QMessageBox::Button::Yes){//Повтор попытки подключения при возникновлении ошибки подключения
            QMessageBox::critical(this, "Ошибка подключения", "Произошла ошибка подключения!");
            tryConnect();
        }
        else throw("connecting error");//Выход из программы после подтверждения пользователя
    }
}

/*Процедура для выполнения переподключения при возникновении критической ошибки
*/
void MainWindow::criticalError(QString message)
{
    QMessageBox::critical(this, "Ошибка", message+" Переподключение к базе данных.");
    tryConnect();
}

/*Процедура для создания окна редактирования выбранной записи
 *
 * Формальный параметр:
 * index - индекс записи в таблице, для которой создается окно редактирования.
*/
void MainWindow::createEdit(QModelIndex index)
{
    edit=new Edit();//Создание нового экземпляра формы редактирования
    edit->setParent(this, Qt::Window);
    connect(edit, SIGNAL(saveYes(bool)), this, SLOT(takeSave(bool)));   //Соединение сигнала с формы редактирования и основной формы для сохранения изменений
    if(!edit->setModelTable(dbworking->generalmodel,
                            dbworking->currtable,
                            dbworking->generalmodel->index(index.row(),
                            dbworking->generalmodel->fieldIndex(_::LOGID)).data().toInt(),
                            &dbworking->db)){//Передача в форму реактирования данных о текущей таблице
      criticalError("Невозможно редактировать запись.");
    }
    edit->tablemapper->setCurrentModelIndex(index);//Передача в форму редактирования данных о текущей записи для взаимодействии элементов в разных окнах
    edit->setModal(true);
    edit->show();//Отображение формы редактирования
}

/*Слот для передвижения каретки скроллера в соответствии с таймером
*/
void MainWindow::setScroll()
{
    ui->LogSlider->setValue(ui->LogSlider->value()+1);
}

/*Событие для загрузки новой таблицы после ее выбора
 *
 * Формальный параметр:
 * index - индекс записи выбранной таблицы.
 *
 * Локальные переменные:
 * fields - массив исходных названий столбцов таблицы;
 * primkey - название поля реального или условного первичного ключа, по которому происходит сортировка данных;
 * forgnkey - массив названий полей с внешними ключами;
 * forgntable - массив названий таблиц, с которыми происходит внешнее соединение;
 * forgnprimkey - массив названий полей первичного ключа для внешних таблиц;
 * forgntext - массив названий полей внешней таблицы, данные из которых должны быть отобрадены вместо внешних ключей;
 * relstatus - количество соединений с внешними таблицами;
 * hideFKcol - отметка о сокрытии 1 поля таблицы (как правило, ключевого поля);
 * i - счетчик для перебора названий полей таблицы и их синонимов.
*/
void MainWindow::on_cbChooseTable_currentIndexChanged(int index)
{
    QSqlRecord fields;
    QString primkey;
    QList<QString> forgnkey, forgntable, forgnprimkey, forgntext;
    int relstatus=0;
    bool hideFKcol=true;

    dbworking->currtable=dbworking->choosingmodel->record(index).value("nametable").toString();//Подготовка загрузки таблицы
    nametable=dbworking->currtable;
    dbworking->fieldsynonims.clear();
    dbworking->tempquery.clear();
    dbworking->temporder.clear();
    on_Retry_clicked();
    ui->teDecript->clear();
    selectionquery.clear();
    ui->rbNormalSelection->setChecked(true);
    ui->cbSelectColumn->clear();

    if(nametable==_::LOG){//Определение таблицы и настройка ее отображения
        dbworking->fieldsynonims.push_back("Дата и время получения");
        dbworking->fieldsynonims.push_back("Блок");
        dbworking->fieldsynonims.push_back("Решение");
        dbworking->fieldsynonims.push_back("Дата выполнения");
        dbworking->fieldsynonims.push_back("Описание");

        primkey=_::LOGDATE;

        forgnkey.push_back(_::LOGSOL);
        forgntable.push_back(_::SOL);
        forgnprimkey.push_back(_::SOLID);
        forgntext.push_back(_::SOLNAME);

        relstatus=1;

        dbworking->tempquery="select "+_::LOGID+", "+_::LOGDATE+", "+_::KANAME+", "+_::BINAME+", "+_::BLOKNAME+", "+_::BLOKSERIAL+", "+_::SOLNAME+", "+_::LOGSOLDATE+", "+_::LOGDESC+" "
        "from "+_::LOG+" "
        "left join "+_::BLOK+" on "+_::BLOKID+"="+_::LOGBLOK+" "
        "left join "+_::BI+" on "+_::BIID+"="+_::BLOKBI+" "
        "left join "+_::KA+" on "+_::KAID+"="+_::BIKA+" "
        "left join "+_::SOL+" on "+_::SOLID+"="+_::LOGSOL+" ";
        dbworking->temporder="order by "+_::LOGDATE+" asc";
    }
    else if(nametable==_::KA){
        dbworking->fieldsynonims.push_back("Номер");
        dbworking->fieldsynonims.push_back("Название");
        dbworking->fieldsynonims.push_back("Дата запуска");
        dbworking->fieldsynonims.push_back("Примечание");
        primkey=_::KADATE;
        hideFKcol=false;
    }
    else if(nametable==_::BI){
        dbworking->fieldsynonims.push_back("Серийный номер");
        dbworking->fieldsynonims.push_back("Название");
        dbworking->fieldsynonims.push_back("КА");
        primkey=_::BIID;
        forgnkey.push_back(_::BIKA);
        forgntable.push_back(_::KA);
        forgnprimkey.push_back(_::KAID);
        forgntext.push_back(_::KANAME);

        relstatus=1;
        ui->tvModel->setItemDelegate(new QSqlRelationalDelegate(ui->tvModel));
    }
    else if(nametable==_::BLOK){
        dbworking->fieldsynonims.push_back("Серийный номер");
        dbworking->fieldsynonims.push_back("Название");
        dbworking->fieldsynonims.push_back("БИ");
        primkey=_::BLOKID;
        dbworking->tempquery="select "+_::BLOKID+", "+_::BLOKSERIAL+", "+_::BLOKNAME+", "+_::BINAME+", "+_::KANAME+" "
        "from "+_::BLOK+" "
        "left join "+_::BI+" on "+_::BIID+"="+_::BLOKBI+" "
        "left join "+_::KA+" on "+_::KAID+"="+_::BIKA+" ";
        dbworking->temporder="order by "+_::KANAME+" asc, "+_::BINAME+" asc ";
    }
    else if(nametable==_::SOL){
        dbworking->fieldsynonims.push_back("Название");
        dbworking->fieldsynonims.push_back("Описание");
        primkey=_::SOLID;
    }
    else if(nametable==_::PARM){
        dbworking->fieldsynonims.push_back("Название");
        dbworking->fieldsynonims.push_back("Описание");
        primkey=_::PARMID;
    }
    else if(nametable==_::FILELOG){
        dbworking->fieldsynonims.push_back("Путь");
        primkey=_::FILELOGID;
    }
    else {
        criticalError("Ошибка загрузки таблицы!");//Попытка переподключения при обнаружении неизвестной таблицы
        return;
    }

    if(dbworking->chooseTable(&primkey, forgnkey, forgntable, forgnprimkey, forgntext, relstatus, hideFKcol)==Enumerr::READINGERROR) {//Проверка корректности загрузки исходной таблицы
        criticalError("Ошибка загрузки таблицы!");
        return;
    }

    if(nametable!=_::LOG&&nametable!=_::BLOK){//Определение отображаемых данных
        ui->tvModel->setModel(dbworking->generalmodel);//Вывод исходной таблицы
        fields=dbworking->generalmodel->record();//Выгрузка исходных названий полей таблицы
    }
    else{
        if (nametable==_::BLOK){//Настройка представлений для определенных таблиц
            dbworking->fieldsynonims.push_back("КА");
        }
        else if(nametable==_::LOG){
            dbworking->fieldsynonims.clear();
            dbworking->fieldsynonims.push_back("Дата и время получения");
            dbworking->fieldsynonims.push_back("КА");
            dbworking->fieldsynonims.push_back("БИ");
            dbworking->fieldsynonims.push_back("Блок");
            dbworking->fieldsynonims.push_back("Серийный номер блока");
            dbworking->fieldsynonims.push_back("Решение");
            dbworking->fieldsynonims.push_back("Дата выполнения");
            dbworking->fieldsynonims.push_back("Описание");
        }

        if(dbworking->loadTemp(1)==Enumerr::READINGOK){//Загрузка представлений
            ui->tvModel->setModel(dbworking->tempmodel);//Вывод представления
            fields=dbworking->tempmodel->record();//Выгрузка исходных названий полей представления
        }
        else {
            criticalError("Ошибка загрузки таблицы!");
            return;
        }
    }


    if(hideFKcol==true){//Скрытие 1-го поля таблицы
        ui->tvModel->hideColumn(0);
    }
    else{
        ui->tvModel->showColumn(0);
    }
    ui->tvModel->resizeColumnsToContents();//Настройка размеров ячеек таблицы
    ui->tvModel->resizeRowsToContents();

    for(int i=hideFKcol; i<fields.count();i++){//Заполнение элемента определения столбца для операции выборки текущими названиями полей
        ui->cbSelectColumn->addItem(dbworking->fieldsynonims[i-hideFKcol], fields.fieldName(i));//dbworking->fieldsynonims[i-hideFKcol] fields.fieldName(i)
        ui->cbSelectColumn->setCurrentIndex(0);
    }

    if(nametable==_::LOG){//Настройка отображения скроллера
        ui->gbTimeScroll->show();
        ui->dtScroll->setDateTime(QDateTime::currentDateTime());
        ui->LogSlider->setValue(0);
        scrollingValue=0;
    }
    else{
       ui->gbTimeScroll->hide();
    }
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
    dbworking->generalmodel->select();
    if(nametable==_::LOG||nametable==_::BLOK) {
        dbworking->loadTemp(1);
    }
}

/*Событие для вызова формы редактирования записи
 *
 * Формальный параметр:
 * index - индекс записи, на которой произошло событие.
 *
 * Локальные переменные:
 * startindex - индекс, используемый для работы формы редактирования;
 * id - общий идентификатор записи для представления и исходной таблицы;
 * indexlist - вспомогательный массив индексов.
*/
void MainWindow::on_tvModel_doubleClicked(const QModelIndex &index)
{
    QModelIndex startindex=index;
    if(nametable==_::LOG||nametable==_::BLOK){//Выполнение поиска индекса в исходной таблице при отображении представления
        QVariant id=dbworking->tempmodel->index(index.row(), 0).data();
        startindex=dbworking->generalmodel->index(0, 0);
        QModelIndexList indexlist=dbworking->generalmodel->match(startindex, Qt::DisplayRole, id);
        if(!indexlist.isEmpty()){//Проверка результата поиска на наличие данных
            startindex=indexlist.first();
        }
        else{
           criticalError("Невозможно редактировать запись.");
           return;
        }
    }
    createEdit(startindex);//Создание формы редактирования
}

/*Событие для добавления строки в текущую таблицу
*/
void MainWindow::on_Add_clicked()
{
    dbworking->generalmodel->insertRow(dbworking->generalmodel->rowCount());
    createEdit(dbworking->generalmodel->index(dbworking->generalmodel->rowCount()-1, 0));
}

/*Слот для сохранения изменений таблицы из формы редактирования
*/
void MainWindow::takeSave(bool yes)
{
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
            if(answer==QMessageBox::Button::Yes) {
                saveChanges("удаление");
            }
            else{
                on_RevertButton_clicked();
            }
        }
    }
    else{
        QMessageBox::critical(this, "Ошибка", "Удаляемая строка не выбрана.");
    }
}

/*Событие для создания выборки в сооствиии с указанными условиями
 *
 * Локлальные переменные:
 * colcount - количество строк, найденных в соответсвтии с выборкой;
 * selecting - текст условия выборки.
*/
void MainWindow::on_Search_clicked()
{
    int colcount=0;
    QString selecting='"'+ui->cbSelectColumn->currentData().toString()+'"'+"='"+ui->teDecript->toPlainText()+"'";//Определение условия выборки
    if(ui->rbNormalSelection->isChecked()){//Изменение условия в соответствии с типом выборки
        selectionquery.clear();
    }
    else if(ui->rbCascadeSelection->isChecked()){
        if(!selectionquery.isEmpty()){
            if(!selectionquery.contains(selecting)){
                selecting=" and "+selecting;
            }
            else{
                selecting.clear();
            }
        }
    }

    selectionquery+=selecting;
    if(nametable!=_::LOG&&nametable!=_::BLOK){
        dbworking->generalmodel->setFilter(selectionquery.toUtf8());    //Выполнение выборки
        colcount=dbworking->generalmodel->rowCount();
    }
    else {
        dbworking->loadTemp(1, "where "+selectionquery);
        colcount=dbworking->tempmodel->rowCount();
    }

    if(colcount==0){ //Проверка наличия записей в выборке
        on_cbChooseTable_currentIndexChanged(ui->cbChooseTable->currentIndex());    //Возвращение полного отображения таблицы при отсуствии результатов поиска
        QMessageBox::critical(this, "Ошибка", "Ничего не найдено!");
    }
}

/*Событие для восстановления полного отображения таблицы после выборки
*/
void MainWindow::on_RevertTable_clicked()
{
    on_cbChooseTable_currentIndexChanged(ui->cbChooseTable->currentIndex());
}

/*Событие запуска и остановки движения каретки скроллера*/
void MainWindow::on_StartStopScroll_clicked()
{
    if(!timerScroll->isActive()){
        timerScroll->start();
    }
    else{
        timerScroll->stop();
    }
}

/*Событие для выборки данных по текущему времени на скроллере*/
void MainWindow::on_LogSlider_valueChanged(int value)
{
    if(value>scrollingValue){//Изменение конечного значения даты для отображаемых записей
        *selectedDT=ui->dtScroll->dateTime().addDays(value);
    }
    else if(value<scrollingValue){
        *selectedDT=ui->dtScroll->dateTime().addDays(-value);
    }
    scrollingValue=value;
    //Загрузка записей, соответствующих текущему временному промежутку
    dbworking->loadTemp(1, "where "+_::LOGDATE+"<='"+selectedDT->toString("yyyy-MM-ddThh:mm:ss.zzz")+"' and "+_::LOGDATE+">='"+ui->dtScroll->dateTime().toString("yyyy-MM-ddThh:mm:ss.zzz")+"'");
    ui->tvModel->scrollTo(dbworking->generalmodel->index(dbworking->generalmodel->rowCount()-1, 1));
    ui->timelabel->setText(selectedDT->toString("dd.MM.yyyy hh:mm:ss"));
}

/*Событие изменения времени начала отсчета для скроллера*/
void MainWindow::on_dtScroll_dateTimeChanged(const QDateTime &dateTime)
{
    selectedDT=new QDateTime(dateTime);
    on_Retry_clicked();
    ui->timelabel->setText(selectedDT->toString("dd.MM.yyyy hh:mm:ss"));
}

/*Событие для перезапуска скроллера*/
void MainWindow::on_Retry_clicked()
{
    if(timerScroll->isActive()){
        timerScroll->stop();
    }
    ui->LogSlider->setValue(0);
    //ui->teDecript->clear();
}

/*Событие для выполнения переподключения к базе*/
void MainWindow::on_RetryConnection_triggered()
{
    tryConnect();
    QMessageBox::information(this, "Уведомление", "Переподключение выполнено.");
}

/*Событие для выполнения загрузки данных из .json файла в базу*/
//В РАЗРАБОТКЕ
void MainWindow::on_UnloadFrom_triggered()
{
    QFile file;
    int recid;
    filePath=QFileDialog::getOpenFileName(this,
                                          QString::fromUtf8("Открыть файл"),
                                          QDir::currentPath(),
                                          "*.json"
                                          );
    file.setFileName(filePath);
    if(file.open(QIODevice::ReadOnly|QFile::Text)){
        doc=QJsonDocument::fromJson(QByteArray(file.readAll()),&docError);
    }
    else{
        QMessageBox::critical(this, "Ошибка", "Ошибка выбора файла.");
        return;
    }
    file.close();
    if (docError.error != QJsonParseError::NoError) {
        QMessageBox::critical(this, "Ошибка", "Ошибка чтения файла.");
        return;
    }
    //QString table, value;
    QJsonObject json=doc.object();
    QJsonArray data=json["logs"].toArray();
    QJsonObject row;
    QSqlRecord record;
    QByteArray path;
    QSqlQuery query;
    int insertcount=0;
    int rowcount=data.count();
    QString currdata;
    QJsonArray parms, parm;
    for(int i=0; i<rowcount; i++){
        row=data[i].toObject();
        record=dbworking->generalmodel->record();
        record.remove(0);
        QSqlQueryModel *temp=new QSqlQueryModel();
        temp->setQuery("select "+_::BLOKID+" "
        "from "+_::BLOK+" "
        "left join "+_::BI+" on "+_::BIID+"="+_::BLOKBI+" "
        "left join "+_::KA+" on "+_::KAID+"="+_::BIKA+" "
        "where "+_::KAID+"='"+ row["KA"].toString()+"' and "+_::BINAME+"='"+row["BI"].toString()+"' and "+_::BLOKNAME+"='"+row["Blok"].toString()+"'");
        record.setValue(_::LOGBLOK, temp->index(0, 0).data());
        record.setValue(_::LOGDATE, row["datetime"].toString());
        if(dbworking->currtable==_::LOG){
            if(dbworking->generalmodel->insertRecord(-1, record)){
                if(!dbworking->generalmodel->submitAll()){
                     QMessageBox::critical(this, "Ошибка", dbworking->generalmodel->lastError().text());
                     return;
                }
                else{
                    insertcount++;
                    //QMessageBox::information(this, "ИНформация", "Выгрузка данных в базу прошла успешно.");
                    parms=row["data"].toArray();
                    query.exec("select CURRVAL(pg_get_serial_sequence('"+_::LOG+"', '"+_::LOGID+"'))");
                    query.first();
                    recid=query.value(0).toInt();
                    for(int l=0; l<parms.count(); l++){
                        currdata="insert into "+_::PARMLOG+" ("+_::PARMLOGLOG+", "+_::PARMLOGPARM+", "+_::PARMLOGCOND+", "+_::PARMLOGFILE+") values (";
                        parm=parms[l].toArray()+", ";
                        currdata+=QString("%1").arg(recid)+", ";
                        query.exec("select "+_::PARMID+" from "+_::PARM+" where "+_::PARMNAME+"='"+parm[0].toString()+"'");
                        query.first();
                        currdata+=QString("%1").arg(query.value(0).toInt())+", ";
                        //record.setValue(3, QVariant(parm[1].toString()));
                        currdata+="'"+parm[1].toString()+"', ";
                        path=parm[2].toString().replace("\\", "\\\\").toUtf8();
                        if(FileLog::getFileID(&path)<=0){
                            query.exec("insert into "+_::FILELOG+"("+_::FILELOGNAME+") values ('"+path+"')");
                        }
                        //record.setValue(4, QVariant(FileLog::getFileID(&path)));
                        currdata+=QString("%1").arg(FileLog::getFileID(&path))+")";
                        //QString message="rec-"+record.value(1).toString()+" parm-"+record.value(2).toString()+" cond-"+record.value(3).toString()+" file-"+record.value(4).toString();
                        //QMessageBox::information(this, "", currdata);
                        if(!query.exec(currdata)){
                            QMessageBox::critical(this, "Ошибка", query.lastError().text());
                            return;
                        }
                    }
                }
            }
        }
    }
    dbworking->loadTemp(1);
    ui->tvModel->resizeColumnsToContents();
    QMessageBox::information(this, "Добавление записей", "Автоматически добавлено "+QString("%1").arg(insertcount)+" из "+QString("%1").arg(rowcount)+" записей.");
    /*QString table, value;
    QSqlRecord record=dbworking->generalmodel->record();
    record.remove(0);
    record.setValue(0, QDateTime::currentDateTime());
    table="equipment";
    value="основное оборудование 1";
    record.setValue(1, dbworking->getId(&value, &table));
    table="condition";
    value="ок";
    record.setValue(2, dbworking->getId(&value, &table));
    if(dbworking->generalmodel->insertRecord(-1, record)){
        if(!dbworking->generalmodel->submitAll()){
             QMessageBox::critical(this, "Ошибка", dbworking->generalmodel->lastError().text());
        }
    }
    else{
        QMessageBox::critical(this, "Ошибка", "Ошибка выбора файла.");
    }*/
}


/*Событие для вызова окна помощи*/
void MainWindow::on_HelpMessage_triggered()
{
    help=new Help();//Создание нового экземпляра формы руководства
    help->setParent(this, Qt::Window);
    help->setModal(true);
    QString text="Данное программное обеспечение предназначено для работы с базой данных.\n\n"
"База предусматривает некоторые ограничения.\n"
"•Таблица 'Журнал приема данных': дата получения данных должна быть меньше или равной дате выполнения решения.\nНедопустимо существование записи для одного и того же блока с одинаковым временем приема.\n"
"•Таблица 'Космические аппараты'(КА): каждый аппарат должен иметь уникальный номер из 3 знаков и название.\n"
"•Таблица 'Бортовые изделия'(БИ): в один и тот же КА не могут входить БИ с одинаковыми названиями.\nСуществование двух БИ с одинаковыми названиями, но в разных КА, допустимо.\nКаждое БИ обладает уникальным серийным номером.\n"
"•Таблица 'Блоки': в один и тот же БИ не могут входить блоки с одинаковыми названиями.\nСуществование двух блоков с одинаковыми названиями, но в разных БИ, допустимо.\nКаждый блок обладает уникальным серийным номером.\nВыбор БИ будет доступен только после выбора целевого КА.\n"
"•Таблицы 'Параметры', 'Решения', 'Файлы': названия('Файлы' - путь) должны быть уникальными.\n"
"•Таблица 'Прикрепленные файлы': вызывается по кнопке 'Параметры', находящейся на форме редактирования таблицы\n"
"'Журнал приема данных'. Одна запись журнала может содержать только по одной записи для каждого параметра.\n\n"
"Все названия, указанные для записей, не могут превышать 50 символов(исключение - 'Файлы').\n"
"Серийные номер - не более 15 символов.\n"
"Описания - не более 300 символов.\n"
"Путь к файлу - не ограничено.\n\n"
"Каждая запись редактируется отдельно. Для редактирования записи или вывода ее в отдельное окно необходим двойное\n"
"нажатие клавиши мыши на любой ячейке необходимой записи.\n\n"
"Для каждой таблицы возможно произвести выборку по значению указанного поля.\n"
"В результат выборки войдут записи, значение указанного поля которых будет равным\n"
"введенному тексту. Текст вводится без кавычек.\n\n"
"Временная шкала для таблицы 'Журнал приема данных' позволяет просмотривать\n"
"Записи за 30 дней, начиная с указанной даты. При прохождении одного деления временной шкалы,\n"
"в таблицу добавляются все записи за дату, соответствующую делению.\n\n"
"Вернуть таблицу в полное отображение можно нажатием кнопки 'Восстановить'.\n\n"
"Будьте осторожны при редактировании таблицы 'Файлы'! Данная таблица автоматически дополняется файлами\n"
"при их выборе для таблицы 'Прикрепленные файлы'. При изменении пути к файлу он изменится для всех записей\n"
"записей, к которым был прикреплен данный путь. Для изменения конкретного пути в конкретной записи\n"
"таблицы 'Журнал приема данных' используйте форму редактирования этой записи.";
    help->setText(&text);
    help->show();//Отображение формы
}

void MainWindow::on_rbCascadeSelection_clicked()
{
    selectionquery.clear();
}
