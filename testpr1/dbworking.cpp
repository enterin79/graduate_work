#include "dbworking.h"
/*Конструктор класса по умолчанию
 */
dbWorking::dbWorking()
{
}
/*Деструктор класса
 */
dbWorking::~dbWorking(){
    if(db.isOpen()){    //Закрытие соединения
        db.close();
    }
    if(choosingmodel!=nullptr){ //Очистка памяти, определенной под таблицу мета-данных
        delete choosingmodel;
    }
    if(generalmodel!=nullptr){  //Очистка памяти, определенной под основную таблицу
        delete generalmodel;
    }
}
/*Функция создания подключения к базе данных на основании предоставленных реквизитов пользовтеля и загрузки списка доступных таблиц
*/
Enumerr dbWorking::connection()
{
     db = QSqlDatabase::addDatabase("QPSQL");
     db.setHostName("127.0.0.1");
     db.setDatabaseName("equipmentstatus");
     db.setUserName("postgres");
     db.setPassword("");
     if(db.open()) {//Выполнение подключения к базе данных с текущими реквизитами
         qInfo(loggerInfo())<<"Connection OK";
         choosingmodel=new QSqlTableModel;   //Загрузка списка доступных таблиц из таблицы мета-данных
         choosingmodel->setQuery("select * from synonim");
         if(choosingmodel->rowCount()!=0){   //Проверка наличия записей об отображаемых таблицах
             qInfo(loggerInfo())<<"Reading synonim OK";
             return Enumerr::CONNECTIONOK;  //Возврат кода успешного подключения и загрузки списка таблиц
         }
         else{
             qCritical(loggerCritical())<<"Reading synonim error "<<choosingmodel->lastError().text();
             return  Enumerr::METALOADERROR;   //Возврат кода ошибки загрузки списка таблиц
         }
     }
     else{
         qCritical(loggerCritical())<<"Connection error"<<db.lastError().text();
         return Enumerr::CONNECTIONERROR;//Возврат кода ошибки подключения к базе
     }
}
/*Функция для загрузки данных выбранной таблицы в приложение
 *
 * Формальные параметры:
 * idTable - название атрибута первичного ключа загружаемой таблицы;
 * relcol - название атрибута внешнего ключа загружаемой таблицы;
 * reltable - название таблицы, от которой зависит загружаемая таблица;
 * relid - название поля, от которого зависит внешний ключ;
 * reloutcol - название поля, которое будет отображаться вместо поля внешнего ключа в загружаемой таблицы;
 * relcount - количество зависимых полей;
 * hideFKcol - наличие скрываемого ключевого поля;
 * i - счетчик для перебора названий столбцов таблицы и их синонимов.
*/
Enumerr dbWorking::chooseTable(QString *idTable, QList<QString> &relcol, QList<QString> &reltable, QList<QString> &relid, QList<QString> &reloutcol, int relcount, bool hideFKcol)
{
    generalmodel->setTable(currtable);  //Выбор загружаемой таблицы
    for(int i=0; i<relcount; i++){    //Определение соединения, если таблица зависимая
        generalmodel->setRelation(generalmodel->fieldIndex(relcol.at(i)),
                           QSqlRelation(reltable.at(i), relid.at(i), reloutcol.at(i)));
    }
    generalmodel->setJoinMode(QSqlRelationalTableModel::LeftJoin);
    if(generalmodel->select()){ //Загрузка данных таблицы
        generalmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);  //Настройка отображения таблицы
        generalmodel->sort(generalmodel->fieldIndex(*idTable), Qt::AscendingOrder);
        for(int i=0; i<fieldsynonims.count(); i++){    //Загрузка данных о столбцах таблицы в элемент интерфейса для осуществления простейшей выборки
            generalmodel->setHeaderData(i+hideFKcol, Qt::Horizontal, fieldsynonims[i]);
        };
        qInfo(loggerInfo())<<"Reading "<<currtable<<" OK";
        return Enumerr::READINGOK;  //Возврат кода успешной загрузки таблицы
    }
    else{
        qCritical(loggerCritical())<<"Reading "<<currtable<<" error "<<generalmodel->lastError().text();
        return Enumerr::READINGERROR;   //Возврат кода ошибки загрузки таблицы
    }
}
/*Процедура для сохранения внесенных в таблицу изменений
*/
Enumerr dbWorking::savechanges()
{
    if(generalmodel->submitAll()){  //Сохранение изменений таблицы
        qInfo(loggerInfo())<<"Saving "<<currtable<<" OK";
        return Enumerr::SAVINGOK;   //Возврат кода успешного сохранения измений
    }
    else{
        qWarning(loggerWarning())<<"Saving "<<currtable<<" error "<<generalmodel->lastError().text();
        return Enumerr::SAVINGERROR;    //Возврат кода ошибки сохранения
    }
}

