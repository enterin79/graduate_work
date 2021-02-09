#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "dbworking.h"
#include "edit.h"

/*#include <QDebug>
#include <QSqlRecord>
#include <QtSql>
#include <QDataWidgetMapper>
#include <QSqlRelationalDelegate>
#include <QItemSelectionModel>*/

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //bool connection(QString log, QString pass);
    //bool chooseTable(QString nameTable, QString relcol="", QString reltable="", QString relid="", QString reloutcol="", int reltype=0);
    //bool loadCBTable(QSqlQueryModel *model, QString id, QString data, QString table);

private slots:
    void on_tvModel_clicked(const QModelIndex &index);

    void on_cbChooseTable_currentIndexChanged(int index);

    void on_SaveButton_clicked();

    void on_RevertButton_clicked();

    void on_tvModel_doubleClicked(const QModelIndex &index);

    void on_Add_clicked();

    void takesave(bool yes);

private:
    Ui::MainWindow *ui;
    dbWorking *dbworking;
    Edit *edit;
//
    //QSqlDatabase db;
    //QSqlQueryModel *choosingmodel;
    //QSqlQueryModel *tempmodel;
    //QSqlRelationalTableModel *generalmodel;
    //QDataWidgetMapper *tablemapper;
    //QString currtable;
    //enum class Enum{OK, CONNECTIONERROR, READERROR};
};
#endif // MAINWINDOW_H
