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
#include "DAT.h"


namespace Ui {
class Edit;
}

/*Класс формы редактирования
 * Позволяет редактировать данные записи
 *
 * Поле:
 * ui - указатель на экземпляр формы графического интерфейса;
 * db - указатель на экземпляр подключения к БД;
 * model - указатель на редактируемую таблицу;
 * file - указатеель на экземпляр формы просмотра записей из таблицы "Состоние параметров" для выбранной записи "Приема данных";
 * tablemapper - элемент для связывания данных из таблицы с элементами формы редактирования;
 * curruentLog - идентификатор записи для таблицы "Прием данных".
 *
 * Методы:
 * saveYes - событие сохранения изменений через основную форму;
 * Edit - конструктор класса по умолчанию;
 * ~Edit - деструктор класса;
 * setModelTable - процедура для соединения данных таблицы с элементами формы;
 * pasteCurrTimeInto - процедура для вставки текущей даты и времени в выбранный элемент;
 * on_Apply_clicked - событие сохранения текущих изменений и закрытия формы редактирования;
 * on_Delete_clicked - событие закрытия формы редактирования;
 * on_CurrDTPaste_clicked, on_SolDTPaste_clicked - события для вставки даты в элемент datetimepicker;
 * on_dtSolutExec_dateTimeChanged - событие для изменения даты в элементе, связанном с таблицей;
 * on_ledtSolutExec_textChanged - событие для изменения даты в элементе datetimepicker;
 * on_SolDTDelete_clicked - событие для удаления значения даты;
 * on_btLogFile_clicked - событие просмотра записей из таблицы "Состояние параметров" для выбранной записи таблицы "Прием данных";
 * on_cbBlokKA_currentIndexChanged - событие для загрзки списка БИ, соответствующих указанному КА;
 * on_cbBlokBI_currentIndexChanged - событие изменения данных в элементе, свзанном со столбцом родительского устройства в таблице "Блок";
 * on_leBlokBISerial_textChanged - событие для загрузки данных о родительских устройствах по данным выбранной записи таблицы "Блок";
 * on_ChooseFile_clicked - событие для выбора загружаемого файла.
*/
class Edit : public QDialog
{
    Q_OBJECT
signals:
    void saveYes(bool variant);
public:
    explicit Edit(QWidget *parent = nullptr);
    ~Edit();
    bool setModelTable(QSqlRelationalTableModel *model, QString table, int idLog, QSqlDatabase *db=nullptr);
    void pasteCurrTimeInto(QDateTimeEdit *widget);

    QSqlDatabase *db=nullptr;
    QDataWidgetMapper *tablemapper=nullptr;
    QSqlRelationalTableModel *model=nullptr;
    FileLog *file=nullptr;
    int curruentLog;

public slots:
    void on_Apply_clicked();
    void on_Delete_clicked();
    void on_CurrDTPaste_clicked();
    void on_SolDTPaste_clicked();
    void on_dtSolutExec_dateTimeChanged(const QDateTime &dateTime);
    void on_ledtSolutExec_textChanged(const QString &arg1);
    void on_SolDTDelete_clicked();
    void on_btLogFile_clicked();
    void on_cbBlokKA_currentIndexChanged(int index);
    void on_cbBlokBI_currentIndexChanged(int index);
    void on_leBlokBISerial_textChanged(const QString &arg1);
    void on_ChooseFile_clicked();

private:
    Ui::Edit *ui;
};

#endif // EDIT_H
