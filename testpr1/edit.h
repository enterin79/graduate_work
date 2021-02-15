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

/*Класс формы редактирования
 * Позволяет редактировать данные данные записи
 *
 * Поле:
 * tablemapper - элемент для связывания данных из таблицы с элементами формы редактирования.
 *
 * Методы:
 * saveYes - событие сохранения изменений через основную форму;
 * Edit - конструктор класса по умолчанию;
 * ~Edit - деструктор класса;
 * setModelTable - метод для соединения данных таблицы с элементами формы редактирования;
 * on_Apply_clicked - событие сохранения текущих изменений и закрытия формы редактирования;
 * on_Delete_clicked - событие закрытия формы редактирования.
 *
*/
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
public slots:
    void on_Apply_clicked();
    void on_Delete_clicked();

private:
    Ui::Edit *ui;
};

#endif // EDIT_H
