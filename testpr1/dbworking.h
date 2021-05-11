#ifndef DBWORKING_H
#define DBWORKING_H
#include <QDebug>
#include <QtSql>
#include "logger.h"
#include "Enumexec.h"
#include "upgradedmodel.h"
#include "comboboxfordb.h"

/*
 * Класс dbWorking
 * Предназначен для работы с базой данных: хранения данных
 * таблиц, их загрузки в приложение, загрузки изменений в базу данных
 *
 * Поля:
 * db - экзмепляр подключения к базе данных;
 * choosingmodel - таблица мета-данных, предназначенная для выбора переключаемых таблиц базы данных;
 * generalmodel - основная таблица, которая в данный момемнт загружена;
 * currtable - название таблицы, которая выведена в данный момент;
 * fieldsynonims - синонимы для полей текущей таблицы, которые отображаются в заголовках для удобства пользователя;
 * tempmodel - представление для таблицы;
 * tempquery - запрос для загрузки представления;
 * temporder - инструкция для сортировки представления.
 *
 * Методы:
 * dbWorking - конструктор класса по умолчанию;
 * ~dbWorking - деструктор класса, выполняет закрытие соединение и запись отметок в файл логирования;
 * connection - функция создания подключения к базе данных на основании предоставленных реквизитов пользовтеля и загрузки списка доступных таблиц;
 * chooseTable - функция для загрузки данных выбранной таблицы в приложение;
 * saveСhanges - функция для сохранения внесенных в таблицу изменений;
 * setHeadersModel - процедура для установки заголовков столбцов в таблице;
 * loadTemp - функция загрузки представления для таблицы;
 * getId - функция для поиска идентификатора значения в таблице;
 */
class dbWorking
{
public:

    dbWorking();
    ~dbWorking(void);
    Enumerr connection();
    Enumerr chooseTable(QString *idTable, QList<QString> &relcol, QList<QString> &reltable, QList<QString> &relid, QList<QString> &reloutcol, int relcount=0, bool hideFKcol=true);
    Enumerr saveChanges();
    void setHeadersModel(QSqlQueryModel *model, bool hideFKcol);
    Enumerr loadTemp(bool hideFKcol, QString where="");
    QVariant getId(QString *value, QString *nametable);

    QSqlDatabase db;
    QSqlQueryModel *choosingmodel=nullptr;
    UpgradedModel *generalmodel=nullptr;
    QString currtable;
    QList<QString> fieldsynonims;
    QSqlQueryModel *tempmodel=nullptr;
    QString tempquery="";
    QString temporder="";
};

#endif // DBWORKING_H
