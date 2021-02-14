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
    dbworking=new dbWorking();

    if(dbworking->connection("", "")){  //Выполнение соединения с базой данных с текущими реквищитами пользователя
        ui->statusbar->showMessage("Соединение установлено");
        dbworking->generalmodel=new QSqlRelationalTableModel(this,dbworking->db);   //Подготовка интерфейса
        ui->cbChooseTable->setModel(dbworking->choosingmodel);
        ui->cbChooseTable->setModelColumn(2);
        ui->cbChooseTable->setCurrentIndex(0);
    }
    else{
        QMessageBox::critical(this, "Ошибка", "Ошибка соединения с базой данных!"); //Выход из приложения при отсуствии соединения
        delete dbworking;
        throw std::runtime_error("connection failed");
        return;
    }

}

/*Деструктор класса
*/
MainWindow::~MainWindow()
{
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
    if(dbworking->generalmodel->submitAll()){   //Проверка выполнения сохранения изменений
        dbworking->setlog(QDateTime::currentDateTime(), Enumerr::OKSAVE);
        qInfo(loggerInfo())<<"Saving "<<dbworking->currtable<<" OK";
        ui->statusbar->showMessage("Операция ("+message+") выполнена успешно "+QTime::currentTime().toString("HH:mm:ss"));
        return 1;
    }
    else{
        dbworking->setlog(QDateTime::currentDateTime(), Enumerr::SAVEERROR);
        qWarning(loggerWarning())<<"Saving "<<dbworking->currtable<<" error";
        QMessageBox::critical(this, "Ошибка", "Ошибка изменения данных! Текст ошибки: "+dbworking->generalmodel->lastError().text());
        ui->statusbar->showMessage("Ошибка выполнения операции ("+message+") "+QTime::currentTime().toString("HH:mm:ss"));
        return 0;
    }
}

/*Процедура для выполнения выхода из программы при возникновении критической ошибки
*/
void MainWindow::criticalerror(QString message)
{
    QMessageBox::critical(this, "Ошибка", message+" Выход из приложения.");
    qCritical(loggerCritical())<<"Critical error "<<dbworking->generalmodel->lastError().text();
    qApp->quit();
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
    QList<QString> currfields;
    QSqlRecord fields;
    int loadok=0;
    dbworking->currtable=dbworking->choosingmodel->record(index).value("nametable").toString();
    if(dbworking->currtable=="equipment"){  //Определение выбранной таблицы
        currfields.push_back("Название оборудования");  //Запись синонимов названий полей
        currfields.push_back("Дата запуска");
        currfields.push_back("Описание");
        loadok=dbworking->chooseTable("id", "equipment", currfields);  //Выполнение загрузки таблицы
    }
    else if(dbworking->currtable=="test"){
        currfields.push_back("Название теста");
        currfields.push_back("Дата тестирования");
        currfields.push_back("Описание");
        currfields.push_back("Тестируемое оборудование");
        loadok=dbworking->chooseTable("id", "test", currfields, "ideqip", "equipment", "id", "nameequip", 1);
        ui->tvModel->setItemDelegate(new QSqlRelationalDelegate(ui->tvModel));
    }
    if(!loadok) {   //Проверка корректности загрузки данных
        dbworking->setlog(QDateTime::currentDateTime(), Enumerr::READERROR);
        criticalerror("Ошибка загрузки таблицы!");
        return;
    }
    ui->tvModel->setModel(dbworking->generalmodel); //Отображение загруженной таблицы
    ui->tvModel->hideColumn(0);
    ui->tvModel->resizeColumnsToContents();

    fields=dbworking->generalmodel->record();
    ui->cbSelectColumn->clear();
    for(int i=1; i<fields.count();i++){ //Заполнение элемента определения столбца для операции выборки текущими названиями полей
        ui->cbSelectColumn->addItem(dbworking->fieldsynonims[i-1],fields.fieldName(i));
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
    if(index.column()!=dbworking->generalmodel->fieldIndex("nameequip")||(dbworking->currtable!="test")){   //Проверка столбца, на котором произошло событие. Это необходимо, чтобы не возникало проблемы про смене значения внешнего ключа в записи без вызова формы редактирования
        edit->setModelTable(dbworking->generalmodel, dbworking->currtable); //Передача в форму реактирования данных о текущей таблице
        edit->tablemapper->setCurrentModelIndex(index); //Передача в форму редактирования данных о текущей записи для взаимодействии элементов в разных окнах
        edit->show();   //Отображение формы редактирования
    }
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
    QString selectionquery=ui->cbSelectColumn->currentData().toString()+"='"+ui->teDecript->toPlainText()+"'";
    //qDebug()<<selectionquery;
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
