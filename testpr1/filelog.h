#ifndef FILELOG_H
#define FILELOG_H

#include <QWidget>
#include <QFileDialog>
#include "filetablemodel.h"
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QMessageBox>
#include <QtSql>
#include <QDesktopServices>
#include <QClipboard>

namespace Ui {
class filelog;
}

class filelog : public QDialog
{
    Q_OBJECT

public:
    explicit filelog(QWidget *parent = nullptr);
    void setLog(int idLog, QSqlDatabase *db);
    ~filelog();
    FileTableModel *filetable;
    int idLog;

private slots:
    void on_selectFile_clicked();

    void on_addFile_clicked();



    void on_openFile_clicked();

    void on_deleteFile_clicked();

    void on_copy_clicked();

private:
    Ui::filelog *ui;
};

#endif // FILELOG_H
