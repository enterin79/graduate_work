#ifndef COMBOBOXFORDB_H
#define COMBOBOXFORDB_H

#include <QComboBox>
#include <QObject>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlRecord>
#include <QtDebug>

/*Класс ComboBoxForDB
 * Расширяет возможности элемента QComboBox для
 * комфортной работы с базой данных
 *
 * Методы:
 * ComboBoxForDB - конструктор класса по умолчанию;
 * setForeignKey - функция для загрузки данных в элемент при работе с внешними ключами таблиц;
 * setData - процедура для определения текущего значения, отображаемого элементом;
 * dataChanged - сигнал об изменении данных в элементе.
 *
*/

class ComboBoxForDB : public QComboBox
{
    Q_OBJECT
    Q_PROPERTY(QVariant Data READ currentData WRITE setData NOTIFY DataChanged USER true)
public:
    ComboBoxForDB(QWidget *parent=nullptr);
    bool setForeignKey(QString id, QString name, QSqlTableModel *temp);
signals:
    void dataChanged();
private:
    void setData(QVariant value);
};

#endif // COMBOBOXFORDB_H
