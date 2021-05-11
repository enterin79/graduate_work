#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QDataWidgetMapper>
#include <QTimer>
#include <QJsonObject>
#include <QJsonParseError>
#include <QFile>
#include <QFileDialog>
#include "dbworking.h"
#include "edit.h"
#include "logger.h"
#include "Enumexec.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/*Класс основной формы приложения
 *
 * Поля:
 * ui - экемпляр формы графического интерфейса;
 * dbworking - указатель на экземпляр класса для работы с базой данных;
 * edit - указатель на экзмемпляр формы редактирования для текущей записи;
 * timerScroll - таймер для просмотра записей по времени добавления;
 * selectedDT - текущая дата для скроллера;
 * scrollingValue - текущее значение скроллера в единицах;
 * nametable - название отображаемой в данный момент таблицы;
 * doc - .json файл с загружаемыми в базу данными;
 * filePath - путь к .json файлу;
 * docError - отметка о результате обработки .json файла.
 *
 * Методы:
 * saveChanges - функция для сохранеия внесенных в таблицу изменений;
 * takeSave - слот для сохранения изменений таблицы из формы редактирования;
 * criticalError - процедура для выполнения выхода из программы при возникновении критической ошибки;
 * tryConnect - процедура для подключения к базе данных;
 * setScroll - слот для передвижения каретки скроллера в соответствии с таймером;
 * createEdit - процедура для создания окна редактирования выбранной записи;
 * MainWindow - конструктор класса по умолчанию;
 * ~MainWindow - деструктор класса;
 * on_cbChooseTable_currentIndexChanged - событие для загрузки новой таблицы после ее выбора;
 * on_SaveButton_clicked - событие для сохранения внесенных изменений;
 * on_RevertButton_clicked - событие для отмены внесенных изменений;
 * on_tvModel_doubleClicked - событие для вызова формы редактирования записи;
 * on_Add_clicked - событие для добавления строки в текущую таблицу;
 * on_Delete_clicked - событие для удаления указанной строки;
 * on_Search_clicked - событие для создания выборки в сооствиии с указанными условиями;
 * on_RevertTable_clicked - событие для восстановления полного отображения таблицы после выборки;
 * on_StartStopScroll_clicked - событие запуска и остановки движения каретки скроллера;
 * on_LogSlider_valueChanged - событие для выборки данных по текущему времени на скроллере;
 * on_dtScroll_dateTimeChanged - событие изменения времени начала отсчета для скроллера;
 * on_Retry_clicked - событие для перезапуска скроллера;
 * on_RetryConnection_triggered - событие для выполнения переподключения к базе;
 * on_UnloadFrom_triggered - событие для выполнения загрузки данных из .json файла в базу.
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool saveChanges(QString message);
    void tryConnect();
    void criticalError(QString message);
    void createEdit(QModelIndex index);

public slots:
    void setScroll();
    void takeSave(bool yes);
    void on_cbChooseTable_currentIndexChanged(int index);
    void on_SaveButton_clicked();
    void on_RevertButton_clicked();
    void on_tvModel_doubleClicked(const QModelIndex &index);
    void on_Add_clicked();
    void on_Delete_clicked();
    void on_Search_clicked();
    void on_RevertTable_clicked();
    void on_StartStopScroll_clicked();
    void on_LogSlider_valueChanged(int value);
    void on_dtScroll_dateTimeChanged(const QDateTime &dateTime);
    void on_Retry_clicked();
    void on_RetryConnection_triggered();
    void on_UnloadFrom_triggered();

private:
    Ui::MainWindow *ui;
    dbWorking *dbworking=nullptr;
    Edit *edit=nullptr;
    QTimer *timerScroll=nullptr;
    QDateTime *selectedDT=nullptr;
    int scrollingValue;
    QString nametable;
    QJsonDocument doc;
    QJsonParseError docError;
    QString filePath;
};
#endif // MAINWINDOW_H
