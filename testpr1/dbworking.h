#ifndef DBWORKING_H
#define DBWORKING_H
#include <QDebug>
#include <QSqlRecord>
#include <QtSql>
#include <QSqlRelationalDelegate>
#include <QItemSelectionModel>
#include "logger.h"

enum class Enumerr:int
{   OKCONNECTION,
    OKREAD,
    OKSAVE,
    CONNECTIONERROR,
    READERROR,
    SAVEERROR
};

struct Logerr{
    QDateTime time;
    Enumerr numerr;
};
/*
 * Класс dbWorking
 * Предназначен для работы с базой данных: хранения данных
 * таблиц, их загрузки в приложение
 *
 * Поля:
 * db - экзмепляр подключения к базе данных;
 * choosingmodel - таблица мета-данных, предназначенная для выбора переключаемых таблиц базы данных;
 * generalmodel - основная таблица, которая в данный момемнт загружена;
 * fieldsynonims - синонимы для полей текущей таблицы, которые отображаются в заголовках для удобства пользователя.
 *
 * Методы:
 * dbWorking - конструктор класса по умолчанию;
 * ~dbWorking - деструктор класса, выполняет закрытие соединение и запись отметок в файл логирования;
 * connection - функция создания подключения к базе данных на основании предоставленных реквизитов пользовтеля и загрузки списка доступных таблиц;
 * chooseTable - функция для загрузки данных выбранной таблицы в приложение.
 */
class dbWorking
{
public:

    dbWorking();
    ~dbWorking(void);
    bool connection(QString log, QString pass);
    bool chooseTable(QString idTable, QString nameTable, QList<QString> fields, QString relcol="", QString reltable="", QString relid="", QString reloutcol="", int reltype=0);
    void setlog(QDateTime dt, Enumerr err);

    QSqlDatabase db;
    QSqlQueryModel *choosingmodel;
    QSqlRelationalTableModel *generalmodel;
    QString currtable;
    QList<QString> fieldsynonims;

    QList<Logerr> errnum;
};

#endif // DBWORKING_H
