#include "comboboxfordb.h"

/*Конструктор класса по умолчанию
 *
 * Формальный параметр:
 * parent - указатель на родительский элемент.
*/
ComboBoxForDB::ComboBoxForDB(QWidget *parent):QComboBox(parent)
{
    connect(this, SIGNAL(currentIndexChanged(int)),
            SIGNAL(dataChanged()));
}

/*Функция для загрузки данных в элемент при работе с внешними ключами таблиц
 *
 * Формальные параметры:
 * id - название атрибута первичного ключа таблицы;
 * name - название атрибута с текстом, который определяется первичным ключом;
 * temp - таблица, откуда будут получены данные.
 *
*/
bool ComboBoxForDB::setForeignKey(const QString *id, const QString *name, QSqlTableModel *temp, QString typeofkey)
{
    temp->sort(temp->fieldIndex(*id), Qt::AscendingOrder);
    if(temp->rowCount()>0){    //Проверка наличия записей в предоставленной таблице
        if(typeofkey=="INT"){   //Выбор типа значения
            for(int i=0; i<temp->rowCount();i++){
               addItem(temp->record(i).value(temp->fieldIndex(*name)).toString(),  //Чтение соответствующих данных из таблицы
                       temp->record(i).value(temp->fieldIndex(*id)).toInt());
            }
        }
        else if(typeofkey=="STR"){
            for(int i=0; i<temp->rowCount();i++){
               addItem(temp->record(i).value(temp->fieldIndex(*name)).toString(),  //Чтение соответствующих данных из таблицы
                       temp->record(i).value(temp->fieldIndex(*id)).toString());
            }
        }
        return 1;
    }
    else{
        return 0;
    }
}


/*Пояснение:
 * При соединении столбца внешнего ключа в relation table и комбобокс,
 * отправляется именно текст внешнего ключа, а не идентификатор.
 * Из-за этого возникает проблема при отображении текущего значения внешнего ключа в записи через комбобокс.
 * Данная процедура проблему решает, находя по указанному тексту нужную запись среди данныз комбобокса.
*/
/*Процедура для определения текущего значения, отображаемого элементом
 *
 * Формальный параметр:
 * value - устанавливаемое значение для элемента.
 *
 * Локальная переменная:
 * row - номер строки в наборе данных элемента.
*/
void ComboBoxForDB::setData(QVariant value)
{
    //qDebug()<<"here "<<value.toInt();
    int row=findData(value.toInt()); //Опредение номера строки в наборе данных, сходя из загружаемого текста
    if(row<0){  //Повтор поиска номера строки, исходя из загружаемых данных
        row=findText(value.toString());
    }
    if(row>=0&&row!=currentIndex()){ //Проверка значения необходимой строки
        setCurrentIndex(row);   //Если по указанному тексту была найдена запись, она устанавливается в качестве отображаемой
    }
    /*else if(row<0){ //Попытка установки пользовательского значения по умолчанию при отсутствии найденных записей
        row=findData(-1);
        if(row<0){  //Проверка наличия пользовательского значения по умолчанию
            setCurrentIndex(-1); //Установка пустого значения при отсутствии значения по умолчанию
        }
        else {
            setCurrentIndex(row);
        }
    }*/
}
