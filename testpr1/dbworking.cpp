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
    if(tempmodel!=nullptr){
        delete tempmodel;
    }
}
/*Функция создания подключения к базе данных на основании предоставленных реквизитов пользовтеля и загрузки списка доступных таблиц
*/
Enumerr dbWorking::connection()
{
     db = QSqlDatabase::addDatabase("QPSQL");
     db.setHostName("127.0.0.1");
     db.setDatabaseName("testing");
     db.setUserName("postgres");
     db.setPassword("admin123");
     if(db.open()) {//Выполнение подключения к базе данных с текущими реквизитами
         qInfo(loggerInfo())<<"Connection OK";
         choosingmodel=new QSqlQueryModel;   //Загрузка списка доступных таблиц из таблицы мета-данных
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
 * relcol - названия атрибутов внешнего ключа загружаемой таблицы;
 * reltable - названия таблиц, от которых зависит загружаемая таблица;
 * relid - названия полей, от которых зависит внешний ключ;
 * reloutcol - названия полей, которые будут отображаться вместо полей внешнего ключа в загружаемой таблице;
 * relcount - количество зависимых полей;
 * hideFKcol - наличие скрываемого ключевого поля;
 *
 * Локальная переменная:
 * i - счетчик для перебора названий столбцов таблицы и их синонимов.
*/
Enumerr dbWorking::chooseTable(QString *idTable, QList<QString> &relcol, QList<QString> &reltable, QList<QString> &relid, QList<QString> &reloutcol, int relcount, bool hideFKcol)
{
    generalmodel->setTable(currtable.toLower());  //Выбор загружаемой таблицы
    for(int i=0; i<relcount; i++){    //Определение соединения, если таблица зависимая
        generalmodel->setRelation(generalmodel->fieldIndex(relcol.at(i)),
                           QSqlRelation(reltable.at(i), relid.at(i), reloutcol.at(i)));
    }
    generalmodel->setJoinMode(QSqlRelationalTableModel::LeftJoin);
    if(generalmodel->select()){ //Загрузка данных таблицы
        generalmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);  //Настройка отображения таблицы
        generalmodel->sort(generalmodel->fieldIndex(*idTable), Qt::AscendingOrder);
        setHeadersModel(generalmodel, hideFKcol);
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
Enumerr dbWorking::saveChanges()
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

/*Процедура для установки заголовков столбцов в таблице
 *
 * Локальная переменная:
 * i - счетчик для перебора названий столбцов таблицы и их синонимов.
*/
void dbWorking::setHeadersModel(QSqlQueryModel *model, bool hideFKcol)
{
    for(int i=0; i<fieldsynonims.count(); i++){//Установка заголовков полей таблицы
        model->setHeaderData(i+hideFKcol, Qt::Horizontal, fieldsynonims[i]);
    };
}

/*Функция загрузки представления для таблицы
 *
 * Формальные параметры:
 * hideFKcol - наличие скрываемого ключевого поля;
 * where - необязательное условие выборки для представления.
*/
Enumerr dbWorking::loadTemp(bool hideFKcol, QString where)
{
    if(tempquery!=""){//Проверка наличия основного запроса для представления
        tempmodel->setQuery(tempquery+" "+where+" "+temporder);//Загрузка прелставления
        if(generalmodel->rowCount()==tempmodel->rowCount()||tempmodel->rowCount()>0){//Проверка наличия загруженных данных
             qInfo(loggerInfo())<<"Reading temp for "+currtable+" OK";
             setHeadersModel(tempmodel, hideFKcol);
             return Enumerr::READINGOK;
        }
        else {
            qCritical(loggerCritical())<<"Reading temp for "+currtable+" error "<<tempmodel->lastError().text();
            return Enumerr::READINGERROR;
        }
    }
    else{
        return Enumerr::READINGERROR;
    }
}
/*Функция для поиска идентификатора значения в таблице*/
//В РАЗРАБОТКЕ
QVariant dbWorking::getId(QString *value, QString *nametable)
{
    QString idcol, valuecol;
    if((*nametable).toLower()==KA){
        idcol="NumberKA";
        valuecol="NameKA";
    }
    else if((*nametable).toLower()==BI){
        idcol="idSol";
        valuecol="NameSol";
    }
    else if((*nametable).toLower()==BLOK){
        idcol="idCond";
        valuecol="Type";
    }
    else if((*nametable).toLower()==SOL){
        idcol="Code";
        valuecol="NameBreak";
    }
    else if((*nametable).toLower()==PARM){
        idcol="Code";
        valuecol="NameBreak";
    }
    else if((*nametable).toLower()==FILE){
        idcol="Code";
        valuecol="NameBreak";
    }
    else return QVariant();
    QSqlQuery *tempquery=new QSqlQuery();
    tempquery->prepare("select "+idcol+" from "+*nametable+" where "+valuecol+"='"+*value+"'");
    tempquery->exec();
    tempquery->first();
    return QVariant(tempquery->value(0));
}

