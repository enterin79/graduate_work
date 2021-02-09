#include "comboboxfordb.h"

ComboBoxForDB::ComboBoxForDB(QWidget *parent):QComboBox(parent)
{
    connect(this, SIGNAL(currentIndexChanged(int)),
            SIGNAL(dataChanged()));
}

bool ComboBoxForDB::setForeignKey(QString id, QString name, QSqlTableModel *temp)
{
    for(int i=1; i<=temp->rowCount();i++){
                QString text=temp->record(i-1).value(temp->fieldIndex(name)).toString();
                qDebug()<<"now text"<<text;
                addItem(text, temp->record(i-1).value(temp->fieldIndex(id)).toInt());
                }
    return 1;
}

void ComboBoxForDB::setData(QVariant value)
{
    int row=findText(value.toString());
    qDebug()<<"here row is"<<row;
    qDebug()<<"here value is"<<value;
    if(row<0||row==currentIndex()){
        return;
    }
    else{
        setCurrentIndex(row);
    }
}
