#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QDataWidgetMapper>
#include "dbworking.h"
#include "edit.h"
#include "logger.h"
#include "Enumexec.h"
#include <QTimer>
#include <QJsonObject>
#include <QJsonParseError>
#include <QFile>
#include <QFileDialog>

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
    void tryconnect();
    void criticalerror(QString message);

public slots:
    void setscroll();
    //void on_tvModel_clicked(const QModelIndex &index);

    void on_cbChooseTable_currentIndexChanged(int index);

    void on_SaveButton_clicked();

    void on_RevertButton_clicked();

    void on_tvModel_doubleClicked(const QModelIndex &index);

    void on_Add_clicked();

    void takesave(bool yes);

    void on_Delete_clicked();

    void on_Search_clicked();

    void on_RevertTable_clicked();

    //void on_Reconnect_clicked();

    void on_tvModel_clicked(const QModelIndex &index);

    //void on_cbEquipment_currentIndexChanged(int index);

    void on_LogEqSave_clicked();

    void on_StartStopScroll_clicked();

    void on_LogSlider_valueChanged(int value);

    void on_dtScroll_dateTimeChanged(const QDateTime &dateTime);

    void on_Retry_clicked();

    void on_RetryConnection_triggered();

    void on_UnloadFrom_triggered();

private:
    Ui::MainWindow *ui;
    dbWorking *dbworking=nullptr;
    Edit *edit;
    QDataWidgetMapper *mapper;
    QTimer *timerScroll;
    QDateTime *selectedDT;
    int scrollingValue;
    QJsonDocument doc;
    QJsonParseError docError;
    QString filePath;
};
#endif // MAINWINDOW_H
