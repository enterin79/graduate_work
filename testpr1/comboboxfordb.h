#ifndef COMBOBOXFORDB_H
#define COMBOBOXFORDB_H

#include <QComboBox>
#include <QObject>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlRecord>
#include <QtDebug>

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
