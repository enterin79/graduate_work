#include "filetablemodel.h"

FileTableModel::FileTableModel(QObject *parent, QSqlDatabase db): QSqlTableModel(parent, db)
{

}

QVariant FileTableModel::data(const QModelIndex &item, int role) const
{
    if(item.column()==2){
        if (role == Qt::TextAlignmentRole)
           {
                return Qt::AlignBaseline;
           }
    }
    return QSqlTableModel::data(item, role);
}
