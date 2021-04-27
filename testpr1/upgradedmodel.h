#ifndef UPGRADEDMODEL_H
#define UPGRADEDMODEL_H

#include <QSqlRelationalTableModel>
#include <QSqlTableModel>
#include <QObject>
#include <QDateTime>
#include <QDebug>
#include <QSqlRecord>
#include <QColor>

class UpgradedModel : public QSqlRelationalTableModel
{
     Q_OBJECT
public:
    explicit UpgradedModel(QObject *parent = nullptr, QSqlDatabase db = QSqlDatabase());
    QVariant data(const QModelIndex &item, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
};

#endif // UPGRADEDMODEL_H
