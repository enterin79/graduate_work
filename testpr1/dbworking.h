#ifndef DBWORKING_H
#define DBWORKING_H
#include <QDebug>
#include <QSqlRecord>
#include <QtSql>
#include <QSqlRelationalDelegate>
#include <QItemSelectionModel>


class dbWorking
{
public:
    dbWorking();
    bool connection(QString log, QString pass);
    bool chooseTable(QString idTable, QString nameTable, QString relcol="", QString reltable="", QString relid="", QString reloutcol="", int reltype=0);
//private:
    QSqlDatabase db;
    QSqlQueryModel *choosingmodel;
    QSqlRelationalTableModel *generalmodel;
    QString currtable;
    enum class Enum{OK, CONNECTIONERROR, READERROR};
};

#endif // DBWORKING_H
