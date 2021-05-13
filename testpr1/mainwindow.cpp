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
    if(dbworking->saveChanges()==Enumerr::SAVINGOK){//Проверка выполнения сохранения изменений
        if(nametable==LOG||nametable==BLOK) {//Загрузка представления для необходимых таблиц
            dbworking->loadTemp(1);
        }
        ui->statusbar->showMessage("Операция ("+message+") выполнена успешно "+QTime::currentTime().toString("HH:mm:ss"));
        return 1;
    }
    else{
        ui->statusbar->showMessage("Ошибка выполнения операции ("+message+") "+QTime::currentTime().toString("HH:mm:ss"));
        QMessageBox::critical(this, "Ошибка", "Ошибка изменения данных! Текст ошибки: "+dbworking->generalmodel->lastError().text());
        on_RevertButton_clicked();//Отмена всех изменений и перезагрузка таблиц
        return 0;
    }
}
/*Процедура для подключения к базе данных
 *
 * Локальные переменные:
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
                            dbworking->generalmodel->fieldIndex("idrec")).data().toInt(),
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
    ui->cbSelectColumn->clear();

    if(nametable==LOG){//Определение таблицы и настройка ее отображения
        dbworking->fieldsynonims.push_back("Дата и время получения");
        dbworking->fieldsynonims.push_back("Блок");
        dbworking->fieldsynonims.push_back("Решение");
        dbworking->fieldsynonims.push_back("Дата выполнения");
        dbworking->fieldsynonims.push_back("Описание");

        primkey="daterec";

        forgnkey.push_back("solid");
        forgntable.push_back("solution");
        forgnprimkey.push_back("idsol");
        forgntext.push_back("namesol");

        relstatus=1;

        dbworking->tempquery="select idrec, daterec, nameka, namebi, nameblok, serialnumberblok, namesol, datesol, descrrec "
        "from receptiondata "
        "left join blok on idblok=blokid "
        "left join bi on idbi=biid "
        "left join ka on numberka=kanumber "
        "left join solution on idsol=solid ";
        dbworking->temporder="order by daterec asc";

    }
    else if(nametable==KA){
        dbworking->fieldsynonims.push_back("Номер");
        dbworking->fieldsynonims.push_back("Название");
        dbworking->fieldsynonims.push_back("Дата запуска");
        primkey="launchdateka";
        hideFKcol=false;
    }
    else if(nametable==BI){
        dbworking->fieldsynonims.push_back("Серийный номер");
        dbworking->fieldsynonims.push_back("Название");
        dbworking->fieldsynonims.push_back("Входит в");
        primkey="idBI";
        forgnkey.push_back("kanumber");
        forgntable.push_back("ka");
        forgnprimkey.push_back("numberka");
        forgntext.push_back("nameka");

        relstatus=1;
        ui->tvModel->setItemDelegate(new QSqlRelationalDelegate(ui->tvModel));
    }
    else if(nametable==BLOK){
        dbworking->fieldsynonims.push_back("Серийный номер");
        dbworking->fieldsynonims.push_back("Название");
        dbworking->fieldsynonims.push_back("БИ");
        primkey="idblok";
        dbworking->tempquery="select idblok, serialnumberblok, nameblok, namebi, nameka "
        "from blok "
        "left join bi on idbi=biid "
        "left join ka on numberka=kanumber ";
        dbworking->temporder="order by idblok asc";
    }
    else if(nametable==SOL){
        dbworking->fieldsynonims.push_back("Название");
        dbworking->fieldsynonims.push_back("Описание");
        primkey="idsol";
    }
    else if(nametable==PARM){
        dbworking->fieldsynonims.push_back("Название");
        dbworking->fieldsynonims.push_back("Описание");
        primkey="idparm";
    }
    else if(nametable==FILE){
        dbworking->fieldsynonims.push_back("Путь");
        primkey="idfile";
    }
    else {
        criticalError("Ошибка загрузки таблицы!");//Попытка переподключения при обнаружении неизвестной таблицы
        return;
    }

    if(dbworking->chooseTable(&primkey, forgnkey, forgntable, forgnprimkey, forgntext, relstatus, hideFKcol)==Enumerr::READINGERROR) {//Проверка корректности загрузки исходной таблицы
        criticalError("Ошибка загрузки таблицы!");
        return;
    }

    if(nametable!=LOG&&nametable!=BLOK){//Определение отображаемых данных
        ui->tvModel->setModel(dbworking->generalmodel);//Вывод исходной таблицы
        fields=dbworking->generalmodel->record();//Выгрузка исходных названий полей таблицы
    }
    else{
        if (nametable==BLOK){//Настройка представлений для определенных таблиц
            dbworking->fieldsynonims.push_back("КА");
        }
        else if(nametable==LOG){
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

    if(nametable==LOG){//Настройка отображения скроллера
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
    if(nametable==LOG||nametable==BLOK) {
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
    if(nametable==LOG||nametable==BLOK){//Выполнение поиска индекса в исходной таблице при отображении представления
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
 * Локлальная переменная:
 * selectionquery - текст выборки;
 * colcount - количество строк, найденных в соответсвтии с выборкой.
*/
void MainWindow::on_Search_clicked()
{
    QString selectionquery;
    int colcount=0;
    selectionquery='"'+ui->cbSelectColumn->currentData().toString()+'"'+"='"+ui->teDecript->toPlainText()+"'";
    if(nametable!=LOG&&nametable!=BLOK){
        dbworking->generalmodel->setFilter(selectionquery.toUtf8());    //Выполнение выборки
        colcount=dbworking->generalmodel->rowCount();
    }
    else {
        selectionquery="where "+selectionquery;
        dbworking->loadTemp(1, selectionquery);
        colcount=dbworking->tempmodel->rowCount();
    }

    if(colcount==0){ //Проверка наличия записей в выборке
        on_cbChooseTable_currentIndexChanged(ui->cbChooseTable->currentIndex());    //Возвращение полного отображения таблицы при отсуствии результатов поиска
        QMessageBox::critical(this, "Ошибка", "Ничего не найдено!");
    }
    else{
        ui->tvModel->scrollTo(dbworking->generalmodel->index(dbworking->generalmodel->rowCount(), 0));
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
    dbworking->loadTemp(1, "where daterec<='"+selectedDT->toString("yyyy-MM-ddThh:mm:ss.zzz")+"' and daterec>='"+ui->dtScroll->dateTime().toString("yyyy-MM-ddThh:mm:ss.zzz")+"'");
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
    ui->LogSlider->setValue(0);
    if(timerScroll->isActive()){
        timerScroll->stop();
    }
    ui->teDecript->clear();
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
    /*QFile file;
    filePath=QFileDialog::getOpenFileName(this,
                                          QString::fromUtf8("Открыть файл"),
                                          QDir::currentPath(),
                                          "*.json"
                                          );
    file.setFileName(filePath);
    if(file.open(QIODevice::ReadOnly|QFile::Text)){
        doc=QJsonDocument::fromJson(QByteArray(file.readAll()),&docError);
    }
    file.close();
    QString table, value;
    QJsonObject json=doc.object();
    QJsonArray data=json["logs"].toArray();
    QJsonObject row;
    QSqlRecord record;
    QString setting=json["setting"].toString();
    int rowcount=data.count();
    QString currdata;
    int colcount;
    //qDebug()<<rowcount;
    for(int i=0; i<rowcount; i++){
        row=data[i].toObject();
        record=dbworking->generalmodel->record();
        record.remove(0);
        //colcount=row.count();
        if(setting=="foreign key"){
            currdata=row["KA"].toString();

        }
        //else if(setting=="primary key"){
            //for(int j=0; j<colcount; j++){
                //qDebug()<<i<<" "<<j<<" "<<row[j].toString();
                //record.setValue(j, QVariant(row[j]));
            //}
        //}

        if(dbworking->generalmodel->insertRecord(-1, record)){
            //if(!dbworking->generalmodel->submitAll()){
                 //QMessageBox::critical(this, "Ошибка", dbworking->generalmodel->lastError().text());
            //}

        }
        else{
            QMessageBox::critical(this, "Ошибка", "Ошибка выбора файла.");
        }
    }*/

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
