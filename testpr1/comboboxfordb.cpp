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
bool ComboBoxForDB::setForeignKey(QString id, QString name, QSqlTableModel *temp)
{
    //QString text;
    if(temp->rowCount()!=0){    //Проверка наличия записей в предоставленной таблице
        for(int i=1; i<=temp->rowCount();i++){
           //text=temp->record(i-1).value(temp->fieldIndex(name)).toString();
           //qDebug()<<"now text"<<text;
           addItem(temp->record(i-1).value(temp->fieldIndex(name)).toString(),  //Чтение соответствующих данных из таблицы
                   temp->record(i-1).value(temp->fieldIndex(id)).toInt());
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
    int row=findText(value.toString()); //Опредение номера строки в наборе данных, сходя из загружаемого текста
    //qDebug()<<"here row is"<<row;
    //qDebug()<<"here value is"<<value;
    if(row<0||row==currentIndex()){ //Проверка значения необходимой строки
        return; //Если необхрдимые данные не найдены либо уже отображены, выполяется выход
    }
    else{
        setCurrentIndex(row);   //Если по указанному тексту была найдена запись, она устанавливается в качестве отображаемой
    }
}
