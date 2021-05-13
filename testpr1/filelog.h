#ifndef FILELOG_H
#define FILELOG_H

#include <QWidget>
#include <QFileDialog>
#include "filetablemodel.h"
#include <QMessageBox>
#include <QtSql>
#include <QDesktopServices>
#include <QClipboard>
#include <upgradedmodel.h>
#include <QDataWidgetMapper>
#include "logger.h"
#include "Enumexec.h"

namespace Ui {
class filelog;
}
/*Класс для работы с таблицей "Состояние параметров"
 *
 * Поля:
 * ui - экемпляр формы графического интерфейса;
 * filetable - таблица;
 * tablemapper - элемент для связывания данных из таблицы с элементами формы редактирования;
 * idLog - идентификатор записи из таблицы "Прием данных";
 * idFile - идентификатор пути к файлу из таблицы "Файл".
 *
 * Методы:
 * filelog - конструктор класса по умолчанию;
 * ~filelog - деструктор класса;
 * setLog - процедура формирования выборки по данным записи из таблицы "Прием данных" и связывания этого представления с элементами интерфейса;
 * getFileID - функция поиска идентификатора для пути файла;
 * on_selectFile_clicked - событие для выбора необходимого файла;
 * on_openFile_clicked - событие для открытия файла из выбранной записи;
 * on_deleteFile_clicked - событие для удаления записи из таблицы "Состояние параметров";
 * on_copy_clicked - событие для копирования пути к файлу;
 * on_saveParm_clicked - событие для сохранения изменений в записи;
 * on_tvFiles_doubleClicked - событие вывода выбранной данных записи в свзанные элементы;
 * on_newRow_clicked - событие очистки свзанных с таблицей элементов.
*/
class filelog : public QDialog
{
    Q_OBJECT

public:
    explicit filelog(QWidget *parent = nullptr);
    void setLog(int idLog, QSqlDatabase *db);
    int getFileID(QByteArray *path);
    ~filelog();

    UpgradedModel *filetable=nullptr;
    QDataWidgetMapper *tablemapper=nullptr;
    int idLog;
    int idFile;

public slots:
    void on_selectFile_clicked();

    void on_openFile_clicked();

    void on_deleteFile_clicked();

    void on_copy_clicked();

    void on_saveParm_clicked();

    void on_tvFiles_doubleClicked(const QModelIndex &index);

    void on_newRow_clicked();

private:
    Ui::filelog *ui;

};

#endif // FILELOG_H
