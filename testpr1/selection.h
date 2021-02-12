#ifndef SELECTION_H
#define SELECTION_H

#include <QWidget>
#include <QtSql/QSqlRecord>
#include "dbworking.h"

//потом удалить
namespace Ui {
class Selection;
}

class Selection : public QWidget
{
    Q_OBJECT

public:
    explicit Selection(QWidget *parent = nullptr);
    ~Selection();
    void setdb(dbWorking *currdb, int currtable);

private slots:
    void on_cbSelectTable_currentIndexChanged(int index);

    void on_cbSelectColumn_activated(int index);

    void on_Search_clicked();

    void on_RevertTable_clicked();

private:
    Ui::Selection *ui;
    dbWorking *db;
    QString currtable;
    QSqlRecord fields;
};

#endif // SELECTION_H
