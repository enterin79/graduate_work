#ifndef UPGRADEDMODEL_H
#define UPGRADEDMODEL_H

#include <QSqlRelationalTableModel>
#include <QSqlTableModel>
#include <QObject>
#include <QDateTime>
#include <QDebug>
#include <QSqlRecord>
#include <QColor>

/*Класс модели-отображения для SQL таблицы
 *
 * Методы
 * UpgradedModel - конструктор класса по умолчанию;
 * data - функция получения данных из поля таблицы;
 * setData - функция вставки данных в поле таблицы;
 * updateRowInTable - функция вставки строки в таблицу.
*/
class UpgradedModel : public QSqlRelationalTableModel
{
     Q_OBJECT
public:
    explicit UpgradedModel(QObject *parent = nullptr, QSqlDatabase db = QSqlDatabase());
    QVariant data(const QModelIndex &item, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    bool updateRowInTable(int row, const QSqlRecord &record);

    void refresh();
};

#endif // UPGRADEDMODEL_H
