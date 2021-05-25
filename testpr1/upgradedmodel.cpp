#include "upgradedmodel.h"

/*Конструктор класса по умолчанию
 *
 * Формальные параметры:
 * parent - указатель на родительский элемент;
 * db - экземпляр соединения с БД.
*/
UpgradedModel::UpgradedModel(QObject *parent, QSqlDatabase db) : QSqlRelationalTableModel(parent, db)
{

}

/*Функция получения данных из поля таблицы
 * Формальные параметры:
 * item - индекс ячейки с данными в загруженной таблице;
 * role - роль запрашиваемых данных.
*/
QVariant UpgradedModel::data(const QModelIndex &item, int role) const
{
    //int colnum=item.column();
    if(role == Qt::BackgroundColorRole&&tableName()=="conditionofparm"){//Настройка цвета строки для определенной таблицы
        //qDebug()<<QSqlRelationalTableModel::data(this->index(item.row(), 3)).toString();
        if(QSqlRelationalTableModel::data(this->index(item.row(), 3)).toString()!="норма"){
            return QColor(Qt::red);
        }
    }
    /*if(role == Qt::TextAlignmentRole&&
            ((tableName()=="conditionofparm"&&item.column()==4)||
             (tableName()=="FileOfParameter"&&item.column()==1))){
       return Qt::AlignBaseline;
    }*/
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

/*Функция вставки данных в поле таблицы
 * Формальные параметры:
 * index - индекс ячейки с данными в загруженной таблице;
 * role - роль вставляемых данных;
 * value - вставляемые данные.
 *
 * Локальные переменные:
 * nullable - отметка о вставке NULL-значения;
 * ans - отметка о корректности вставки данных.
*/
bool UpgradedModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    QString nullable=value.toString();
    bool ans;
    if(nullable=="NULL"){//Выбор метода вставки в зависимости от наличия вставляемых данных
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
    while(canFetchMore())
        fetchMore();
}
/*Функция вставки строки в таблицу
 * Формальный параметр:
 * record - вставляемая запись.
*/
bool UpgradedModel::updateRowInTable(int row, const QSqlRecord &record)
{
    return QSqlRelationalTableModel::updateRowInTable(row, record);
}

