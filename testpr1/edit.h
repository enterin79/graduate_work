#ifndef EDIT_H
#define EDIT_H

#include <QWidget>
#include <QDateTimeEdit>
#include <QMessageBox>
#include <QDataWidgetMapper>
#include <QtSql/QSqlRelationalTableModel>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlRecord>
#include "filelog.h"

namespace Ui {
class Edit;
}

/*Класс формы редактирования
 * Позволяет редактировать данные данные записи
 *
 * Поле:
 * tablemapper - элемент для связывания данных из таблицы с элементами формы редактирования.
 *
 * Методы:
 * saveYes - событие сохранения изменений через основную форму;
 * Edit - конструктор класса по умолчанию;
 * ~Edit - деструктор класса;
 * setModelTable - метод для соединения данных таблицы с элементами формы редактирования;
 * on_Apply_clicked - событие сохранения текущих изменений и закрытия формы редактирования;
 * on_Delete_clicked - событие закрытия формы редактирования.
 *
*/
class Edit : public QDialog//public QWidget,
{
    Q_OBJECT
signals:
    void saveYes(bool variant);
public:
    explicit Edit(QWidget *parent = nullptr);
    ~Edit();
    bool setModelTable(QSqlRelationalTableModel *model, QString table, int idLog, QSqlDatabase *db=nullptr);
    QDataWidgetMapper *tablemapper;
    void PasteCurrTimeInto(QDateTimeEdit *widget);
    QSqlRelationalTableModel *model;
    filelog *file;
    int curruentLog;
    QSqlDatabase *db;
public slots:
    void on_Apply_clicked();
    void on_Delete_clicked();
    void on_CurrDTPaste_clicked();
    void on_SolDTPaste_clicked();
    void on_dtSolutExec_dateTimeChanged(const QDateTime &dateTime);

private slots:
    void on_ledtSolutExec_textChanged(const QString &arg1);

    void on_SolDTDelete_clicked();

    void on_btLogFile_clicked();

private:
    Ui::Edit *ui;
};

#endif // EDIT_H
