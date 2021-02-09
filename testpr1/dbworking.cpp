#include "dbworking.h"

dbWorking::dbWorking()
{
    choosingmodel=new QSqlTableModel;
    choosingmodel->setQuery("select * from synonim");
}

bool dbWorking::connection(QString log, QString pass)
{
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("dbequiptesting");
    db.setUserName(log);
    db.setPassword(pass);
    if(!db.open()) {
        qDebug()<<"Error"<<db.lastError().text();
        return 0;
    }
    choosingmodel=new QSqlTableModel;
    choosingmodel->setQuery("select * from synonim");
    return 1;
}

bool dbWorking::chooseTable(QString idTable, QString nameTable, QString relcol, QString reltable, QString relid, QString reloutcol, int reltype)
{
    try{
        generalmodel->setTable(nameTable);
        if(reltype)
            generalmodel->setRelation(generalmodel->fieldIndex(relcol),
                               QSqlRelation(reltable, relid, reloutcol));
        generalmodel->select();
        qDebug()<<"Error1"<<generalmodel->lastError().text();
        generalmodel->setEditStrategy(QSqlTableModel::OnManualSubmit);
        generalmodel->setJoinMode(QSqlRelationalTableModel::LeftJoin);
        generalmodel->sort(generalmodel->fieldIndex(idTable), Qt::AscendingOrder);
        return 1;
    }
    catch(...){
        qDebug()<<"Error"<<db.lastError().text();
        return 0;
    }
}

