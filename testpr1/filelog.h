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

class filelog : public QDialog
{
    Q_OBJECT

public:
    explicit filelog(QWidget *parent = nullptr);
    void setLog(int idLog, QSqlDatabase *db);
    int getFileID(QByteArray *path);
    ~filelog();

    UpgradedModel *filetable;
    QDataWidgetMapper *tablemapper;
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
