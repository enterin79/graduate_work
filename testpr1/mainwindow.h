#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "dbworking.h"
#include "edit.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/*Класс основной формы приложения
 *
 * Поля:
 * dbworking - указатель на экземпляр класса для работы с базой данных;
 * edit - указатель на экзмемпляр формы редактирования для текущей записи.
 *
 * Методы:
 * saveChanges - функция для сохранеия внесенных в таблицу изменений;
 * takesave - слот для сохранения изменений таблицы из формы редактирования;
 * criticalerror - процедура для выполнения выхода из программы при возникновении критической ошибки;
 * MainWindow - конструктор класса по умолчанию;
 * ~MainWindow - деструктор класса;
 * on_cbChooseTable_currentIndexChanged - событие для загрузки новой таблицы после ее выбора;
 * on_SaveButton_clicked - событие для сохранения внесенных изменений;
 * on_RevertButton_clicked - событие для отмены внесенных изменений;
 * on_tvModel_doubleClicked - событие для вызова формы редактирования записи;
 * on_Add_clicked - событие для добавления строки в текущую таблицу;
 * on_Delete_clicked - событие для удаления указанной строки;
 * on_Search_clicked - событие для создания выборки в сооствиии с указанными условиями;
 * on_RevertTable_clicked - событие для восстановления полного отображения таблицы после выборки.
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool saveChanges(QString message);
    void criticalerror(QString message);

private slots:
    //void on_tvModel_clicked(const QModelIndex &index);

    void on_cbChooseTable_currentIndexChanged(int index);

    void on_SaveButton_clicked();

    void on_RevertButton_clicked();

    void on_tvModel_doubleClicked(const QModelIndex &index);

    void on_Add_clicked();

    void takesave(bool yes);

    void on_Delete_clicked();

    //void on_select_clicked();

    void on_Search_clicked();

    void on_RevertTable_clicked();


private:
    Ui::MainWindow *ui;
    dbWorking *dbworking;
    Edit *edit;
};
#endif // MAINWINDOW_H
