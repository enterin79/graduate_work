//Это не относится к текущей версии проекта
#ifndef FILETABLEMODEL_H
#define FILETABLEMODEL_H
#include <QSqlTableModel>

class FileTableModel:public QSqlTableModel
{
    Q_OBJECT
public:
    explicit FileTableModel(QObject *parent = nullptr, QSqlDatabase db = QSqlDatabase());
    QVariant data(const QModelIndex &item, int role) const;
};

#endif // FILETABLEMODEL_H
