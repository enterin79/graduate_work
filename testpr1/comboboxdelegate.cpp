//Это не относится к текущей версии проекта
#include "comboboxdelegate.h"

ComboBoxDelegate::ComboBoxDelegate(QObject *parent)
    : QItemDelegate(parent)
{
}

QWidget *ComboBoxDelegate::createEditor(QWidget *parent,
    const QStyleOptionViewItem &/* option */,
    const QModelIndex &/* index */) const
{
    ComboBoxForDB *editor = new ComboBoxForDB(parent);
    editor->setFrame(false);
    if(model==nullptr||data==nullptr||text==nullptr){
        qDebug()<<"ERROR";
    }
    else{
        qDebug()<<data;
        //qDebug()<<editor->setForeignKey(&data, &text, model);
    }

    return editor;
}


void ComboBoxDelegate::setEditorData(QWidget *editor,
                                    const QModelIndex &index) const
{
    QString value = index.model()->data(index, Qt::EditRole).toString();
    ComboBoxForDB *comboBox = static_cast<ComboBoxForDB*>(editor);
    comboBox->addItem(value);
    qDebug()<<"here";
}

void ComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                   const QModelIndex &index) const
{
    ComboBoxForDB *comboBox = static_cast<ComboBoxForDB*>(editor);
    QString value = comboBox->itemText(comboBox->currentIndex());
    model->setData(index, value, Qt::EditRole);
}

void ComboBoxDelegate::updateEditorGeometry(QWidget *editor,
    const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
    editor->setGeometry(option.rect);
}
