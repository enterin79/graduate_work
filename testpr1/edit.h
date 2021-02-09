#ifndef EDIT_H
#define EDIT_H

#include <QWidget>
#include <QDataWidgetMapper>
#include <QtSql/QSqlRelationalTableModel>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlRecord>

namespace Ui {
class Edit;
}

class Edit : public QWidget
{
    Q_OBJECT
signals:
    void saveYes(bool variant);
public:
    explicit Edit(QWidget *parent = nullptr);
    ~Edit();
    bool setModelTable(QSqlRelationalTableModel *model, QString table);
    QDataWidgetMapper *tablemapper;
private slots:
    void on_Apply_clicked();
    void on_Delete_clicked();

    void on_cbEquipId_currentIndexChanged(const QString &arg1);

    void on_unshowing_textChanged(const QString &arg1);

private:
    Ui::Edit *ui;
};

#endif // EDIT_H
