#include "upgradedmodel.h"

UpgradedModel::UpgradedModel(QObject *parent, QSqlDatabase db) : QSqlRelationalTableModel(parent, db)
{

}

QVariant UpgradedModel::data(const QModelIndex &item, int role) const
{
    int colnum=item.column();
    if(role == Qt::BackgroundColorRole&&tableName()=="conditionlog"){
        if(!QSqlRelationalTableModel::data(this->index(item.row(), 4)).isNull()){
            //qDebug()<<checkbreak;
            return QColor(Qt::red);
        }
        else if(QSqlRelationalTableModel::data(this->index(item.row(), 3)).toString() != "ок"){
            return QColor(Qt::yellow);
        }
    }
    if(role == Qt::DisplayRole && (colnum==1 || colnum==6 || colnum==7)&&tableName()=="conditionlog"){
        QString mydata;
        if(colnum==7){
            if(QSqlRelationalTableModel::data(this->index(item.row(), colnum)).toBool()){
                mydata="Да";
            }
            else{
                mydata="Нет";
            }
            return mydata;
        }
        else if(colnum==1||colnum==6){
            mydata = QSqlRelationalTableModel::data(this->index(item.row(), colnum)).toString();
            QDateTime dateTime = QDateTime::fromString(mydata,"yyyy-MM-ddThh:mm:ss.zzz");//03.мар.20 10:06:15
            return QVariant(dateTime.toString("dd.MM.yyyy HH:mm:ss"));
        }
    }
    else{
        return QSqlRelationalTableModel::data(item, role);
    }
    //return QVariant();
}

bool UpgradedModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    QString nullable=value.toString();
    //qDebug()<<nullable;
    if(nullable=="NULL"){
        return QSqlTableModel::setData(index, QVariant(), role);
    }
    else {
        return QSqlRelationalTableModel::setData(index, value, role);
    }
}

