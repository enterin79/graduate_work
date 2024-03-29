#ifndef COMBOBOXFORDB_H
#define COMBOBOXFORDB_H

#include <QComboBox>
#include <QObject>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlRecord>
#include <QItemDelegate>
#include <QtDebug>

/*Класс ComboBoxForDB
 * Расширяет возможности элемента QComboBox для
 * комфортной работы с базой данных
 *
 * Методы:
 * ComboBoxForDB - конструктор класса по умолчанию;
 * setForeignKey - функция для загрузки данных в элемент при работе с внешними ключами таблиц;
 * newSetData - процедура для определения текущего значения, отображаемого элементом;
 * dataChanged - сигнал об изменении данных в элементе.
 *
*/

class ComboBoxForDB : public QComboBox
{
    Q_OBJECT
    Q_PROPERTY(QVariant Data READ currentData WRITE newSetData NOTIFY dataChanged USER true)
public:
    ComboBoxForDB(QWidget *parent=nullptr);
    bool setForeignKey(const QString *id, const QString *name, QSqlTableModel *temp, QString typeofkey="INT");
    void newSetData(QVariant value);
signals:
    void dataChanged();
};

#endif // COMBOBOXFORDB_H
