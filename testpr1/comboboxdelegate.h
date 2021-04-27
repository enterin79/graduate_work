//Это не относится к текущей версии проекта
#ifndef COMBOBOXDELEGATE_H
#define COMBOBOXDELEGATE_H

#include <QItemDelegate>
#include <QComboBox>
#include <QDebug>
#include <QSqlTableModel>
#include <QtSql/QSqlRecord>
#include "comboboxfordb.h"

class ComboBoxDelegate : public QItemDelegate
{
public:
    Q_OBJECT
public:
       ComboBoxDelegate(QObject *parent = 0);

       QWidget *createEditor(QWidget *parent,
                             const QStyleOptionViewItem &option,
                             const QModelIndex &index) const;

       void setEditorData(QWidget *editor, const QModelIndex &index) const;

       void setModelData(QWidget *editor, QAbstractItemModel *model,
                         const QModelIndex &index) const;
       void updateEditorGeometry(QWidget *editor,
           const QStyleOptionViewItem &option, const QModelIndex &index) const;
       QSqlTableModel *model=nullptr;
       QString data;
       QString text;
};

#endif // COMBOBOXDELEGATE_H
