#include "dbworking.h"
//добавить комментарии для логирования
/*Конструктор класса по умолчанию
 */
dbWorking::dbWorking()
{
}
/*Деструктор класса
 */
dbWorking::~dbWorking(){
    if(db.isOpen()){
        db.close();
    }
    if(choosingmodel!=nullptr){
        qDebug()<<"here";
        delete choosingmodel;
    }
    if(generalmodel!=nullptr){
        qDebug()<<"here";
        delete generalmodel;
    }
    /*for(int i=0; i<errnum.count(); i++){    //Вывод внутреннего массива логирования
        qInfo(loggerInfo())<<"Log"<<errnum[i].time.toString()<<" code: "<<(int)errnum[i].numerr;
    }*/
}
/*Функция создания подключения к базе данных на основании предоставленных реквизитов пользовтеля и загрузки списка доступных таблиц
 *
 * Формальные параметры:
 * log - логин пользователя;
 * pass - пароль пользователя.
*/
Enumerr dbWorking::connection()
{
     db = QSqlDatabase::addDatabase("QPSQL");
     db.setHostName("127.0.0.1");
     db.setDatabaseName("dbequiptesting");
     db.setUserName("postgres");
     db.setPassword("admin123");
     if(db.open()) {//Выполнение подключения к базе данных
         qInfo(loggerInfo())<<"Connection OK";
         choosingmodel=new QSqlTableModel;   //Загрузка списка доступных таблиц из таблицы мета-данных
         choosingmodel->setQuery("select * from synonim");
         if(choosingmodel->rowCount()!=0){   //Проверка наличия записей об отображаемых таблицах
             qInfo(loggerInfo())<<"Reading synonim OK";
             return Enumerr::CONNECTIONOK;  //Установка отметки от корректном подключении загрузке списка таблиц
         }
         else{
             qCritical(loggerCritical())<<"Reading synonim error "<<choosingmodel->lastError().text();
             return  Enumerr::METALOADERROR;   //Установка отметки от некорректной загрузке списка таблиц
         }
     }
     else{
         qCritical(loggerCritical())<<"Connecting error"<<db.lastError().text();
         return Enumerr::CONNECTIONERROR;//Установка отметки о некорректном подключении к базе
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
Enumerr dbWorking::chooseTable(QString *idTable, QString *nameTable, QString *relcol, QString *reltable, QString *relid, QString *reloutcol, int reltype)
{
    generalmodel->setTable(*nameTable);  //Выбор загружаемой таблицы
    if(reltype){    //Определение соединения, если таблица зависимая
        generalmodel->setRelation(generalmodel->fieldIndex(*relcol),
                           QSqlRelation(*reltable, *relid, *reloutcol));
    }
    generalmodel->setJoinMode(QSqlRelationalTableModel::LeftJoin);
    if(generalmodel->select()){ //загрузка данных таблицы
        generalmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);  //Настройка отображения таблицы
        generalmodel->sort(generalmodel->fieldIndex(*idTable), Qt::AscendingOrder);
        //fieldsynonims=fields;
        for(int i=1; i<=fieldsynonims.count(); i++){    //Загрузка данных о столбцах таблицы в элемент интерфейса для осуществления простейшей выборки
            generalmodel->setHeaderData(i, Qt::Horizontal, fieldsynonims[i-1]);
        };
        qInfo(loggerInfo())<<"Reading "<<currtable<<" OK";
        return Enumerr::READINGOK;
    }
    else{
        qCritical(loggerCritical())<<"Connecting error "<<db.lastError().text();
        return Enumerr::READINGERROR;
    }
}
/*Процедура для добавления записи во внутренний журнал логов
 *
 * Формальные параметры:
 * dt - дата и время возникновения события;
 * err - код ошибки.
 *
 * Локальная переменная:
 * currlog - экземпляр структуры для добавления новой записи в массив логов.
*/
/*void dbWorking::setlog(QDateTime dt, Enumerr err)
{
    Logerr currlog;
    currlog.time=dt;
    currlog.numerr=err;
    errnum.push_back(currlog);
}*/

