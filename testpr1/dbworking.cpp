#include "dbworking.h"
/*Конструктор класса по умолчанию
 */
dbWorking::dbWorking()
{
}
/*Деструктор класса
 */
dbWorking::~dbWorking(){
    db.close();
    //тут будет запись листа с enum в файл логов
    //в файле также будут записи текта ошибок
}
/*Функция создания подключения к базе данных на основании предоставленных реквизитов пользовтеля и загрузки списка доступных таблиц
 *
 * Формальные параметры:
 * log - логин пользователя;
 * pass - пароль пользователя.
*/
bool dbWorking::connection(QString log, QString pass)
{
    try{
        db = QSqlDatabase::addDatabase("QPSQL");
        db.setHostName("127.0.0.1");
        db.setDatabaseName("dbequiptesting");
        db.setUserName(log);
        db.setPassword(pass);
        if(db.open()) {//Выполнение подключения к базе данных
            errnum.push_back(Enumerr::OKCONNECTION);    //Установка отметки о корректном подключении к базе
            choosingmodel=new QSqlTableModel;   //Загрузка списка доступных таблиц из таблицы мета-данных
            choosingmodel->setQuery("select * from synonim");
            if(choosingmodel->rowCount()!=0){   //Проверка наличия записей об отображаемых таблицах
                errnum.push_back(Enumerr::OKREAD);  //Установка отметки от корректной загрузке списка таблиц
            }
            else{
                errnum.push_back(Enumerr::READERROR);   //Установка отметки от некорректной загрузке списка таблиц
                throw std::runtime_error("reading failed");
            }
            return 1;
        }
        else{
            qDebug()<<"Error"<<db.lastError().text();
            errnum.push_back(Enumerr::CONNECTIONERROR); //Установка отметки о некорректном подключении к базе
            throw std::runtime_error("connection failed");
        }
    }
    catch(...){
        return 0;
    }
}
/*Функция для загрузки данных выбранной таблицы в приложение
 *
 * Формальные параметры:
 * idTable - название атрибута первичного ключа загружаемой таблицы;
 * nameTable - название загружаемой таблицы;
 * fields - синонимы полей, которые будут отображены в заголовках таблицы;
 * relcol - название атрибута внешнего ключа загружаемой таблицы;
 * reltable - название таблицы, от которой зависит загружаемая таблица;
 * relid - название поля, от которого зависит внешний ключ;
 * reloutcol - название поля, которое будет отображаться вместо поля внешнего ключа в загружаемой таблицы;
 * reltype - тип зависмости (есть/нет).
*/
bool dbWorking::chooseTable(QString idTable, QString nameTable, QList<QString> fields, QString relcol, QString reltable, QString relid, QString reloutcol, int reltype)
{
    try{
        generalmodel->setTable(nameTable);  //Выбор загружаемой таблицы
        if(reltype){    //Определение соединения, если таблица зависимая
            generalmodel->setRelation(generalmodel->fieldIndex(relcol),
                               QSqlRelation(reltable, relid, reloutcol));
        }
        generalmodel->setJoinMode(QSqlRelationalTableModel::LeftJoin);
        generalmodel->select(); //загрузка данных таблицы

        if(generalmodel->rowCount()!=0){    //Проверка наличия загруженных данных
            errnum.push_back(Enumerr::OKREAD);  //Установка отметки о корректной загрузке данных из таблицы
        }
        else{
            errnum.push_back(Enumerr::READERROR);   //Установка отметки о не корректной загрузке данных из таблицы
            throw std::runtime_error("reading failed");
        }

        generalmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);  //Настройка отображения таблицы
        generalmodel->sort(generalmodel->fieldIndex(idTable), Qt::AscendingOrder);
        fieldsynonims=fields;
        for(int i=1; i<=fieldsynonims.count(); i++){    //Загрузка данных о столбцах таблицы в элемент интерфейса для осуществления простейшей выборки
            generalmodel->setHeaderData(i, Qt::Horizontal, fieldsynonims[i-1]);
        }
        return 1;
    }
    catch(...){
        qDebug()<<"Error"<<db.lastError().text();
        return 0;
    }
}

