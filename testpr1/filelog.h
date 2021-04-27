#ifndef FILELOG_H
#define FILELOG_H

#include <QWidget>
#include <QFileDialog>
#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QMessageBox>
#include <QtSql>
#include <QDesktopServices>

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
    QSqlTableModel *filetable;
    int idLog;

private slots:
    void on_selectFile_clicked();

    void on_addFile_clicked();



    void on_openFile_clicked();

private:
    Ui::filelog *ui;
};

#endif // FILELOG_H
