#include "upgradedmodel.h"

UpgradedModel::UpgradedModel(QObject *parent, QSqlDatabase db) : QSqlRelationalTableModel(parent, db)
{

}

QVariant UpgradedModel::data(const QModelIndex &item, int role) const
{
    //int colnum=item.column();
    if(role == Qt::BackgroundColorRole&&tableName()=="conditionofparm"){
        qDebug()<<QSqlRelationalTableModel::data(this->index(item.row(), 3)).toString();
        if(QSqlRelationalTableModel::data(this->index(item.row(), 3)).toString()!="норма"){
            return QColor(Qt::red);
        }
    }
    return QSqlRelationalTableModel::data(item, role);
    /*if(role == Qt::DisplayRole && (colnum==1 || colnum==4)&&tableName()=="ReceptionData"){
        QString mydata;
        mydata = QSqlRelationalTableModel::data(this->index(item.row(), colnum)).toString();
        QDateTime dateTime = QDateTime::fromString(mydata,"yyyy-MM-ddThh:mm:ss.zzz");//03.мар.20 10:06:15
        return QVariant(dateTime.toString("dd.MM.yyyy HH:mm:ss"));
    }
    else{
        return QSqlRelationalTableModel::data(item, role);
    }*/
}

bool UpgradedModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    QString nullable=value.toString();
    bool ans;
    if(nullable=="NULL"){
        ans=QSqlTableModel::setData(index, QVariant(), role);
    }
    else {
        ans=QSqlRelationalTableModel::setData(index, value, role);
    }
    refresh();
    return ans;
}

void UpgradedModel::refresh()
{
    while( canFetchMore() )
        fetchMore();
}

bool UpgradedModel::updateRowInTable(int row, const QSqlRecord &record)
{
    return QSqlRelationalTableModel::updateRowInTable(row, record);
}

