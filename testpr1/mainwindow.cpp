#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dbworking=new dbWorking();

    if(dbworking->connection("postgres", "admin123")){
        ui->statusbar->showMessage("Соединение установлено");
        dbworking->generalmodel=new QSqlRelationalTableModel(this,dbworking->db);
        ui->cbChooseTable->setModel(dbworking->choosingmodel);
        ui->cbChooseTable->setModelColumn(2);
        ui->cbChooseTable->setCurrentIndex(0);
    }
    else{
        QMessageBox::critical(this, "Ошибка", "Ошибка соединения с базой данных!");
        throw std::runtime_error("connection failed");
        return;
    }

}

MainWindow::~MainWindow()
{
    dbworking->db.close();
    delete ui;
}


/*
bool MainWindow::loadCBTable(QSqlQueryModel *model, QString id, QString data, QString table)
{
    try{
        model=new QSqlQueryModel;
        model->setQuery("select "+id+", "+data+" from "+table);
        return 1;
    }
    catch(...){
        qDebug()<<"Error"<<db.lastError().text();
        return 0;
    }
    return 0;
}*/



void MainWindow::on_tvModel_clicked(const QModelIndex &index)
{
    //dbworking->tablemapper->setCurrentModelIndex(index);
}

void MainWindow::on_cbChooseTable_currentIndexChanged(int index)
{
    //dbworking->tablemapper=new QDataWidgetMapper(this);
    //dbworking->tablemapper->setModel(dbworking->generalmodel);
    dbworking->currtable=dbworking->choosingmodel->record(index).value("nametable").toString();
    if(dbworking->currtable=="equipment"){
        dbworking->chooseTable("id", "equipment");
        //dbworking->tablemapper->addMapping(ui->leNameEq, dbworking->generalmodel->fieldIndex("nameequip"));
        //dbworking->tablemapper->addMapping(ui->leNote, dbworking->generalmodel->fieldIndex("note"), "plainText");
        //dbworking->tablemapper->addMapping(ui->deFirstExpDate, dbworking->generalmodel->fieldIndex("firstexpldate"));
        //ui->gbTest->hide();
        //ui->gbEquip->show();
    }
    else if(dbworking->currtable=="test"){
        //dbworking->tempmodel=new QSqlQueryModel;
        dbworking->chooseTable("id", "test", "ideqip", "equipment", "id", "nameequip", 1);
        ui->tvModel->setItemDelegate(new QSqlRelationalDelegate(ui->tvModel));
        //dbworking->tablemapper->addMapping(ui->leNameTest, dbworking->generalmodel->fieldIndex("nametest"));
        //dbworking->tablemapper->addMapping(ui->deDateTest, dbworking->generalmodel->fieldIndex("datetest"));
        //dbworking->tablemapper->addMapping(ui->leDescript, dbworking->generalmodel->fieldIndex("description"), "plainText");
        //ui->gbTest->show();
        //ui->gbEquip->hide();
    }
    ui->tvModel->setModel(dbworking->generalmodel);
    qDebug()<<dbworking->currtable;
    //edit->setModelTable(dbworking->generalmodel, dbworking->currtable);
}

void MainWindow::on_SaveButton_clicked()
{
    if(dbworking->generalmodel->submitAll()){
        ui->statusbar->showMessage("Операция выполнена успешно "+QTime::currentTime().toString("HH:mm:ss"));
    }
    else{
        QMessageBox::critical(this, "Ошибка", "Ошибка обновления или добавления данных!");
        ui->statusbar->showMessage("Ошибка выполнения операции "+QTime::currentTime().toString("HH:mm:ss"));
    }
}

void MainWindow::on_RevertButton_clicked()
{
    dbworking->generalmodel->revertAll();
}

void MainWindow::on_tvModel_doubleClicked(const QModelIndex &index)
{
    edit=new Edit();
    edit->setParent(this, Qt::Window);
    connect(edit, SIGNAL(saveYes(bool)), this, SLOT(takesave(bool)));
    if(index.column()!=dbworking->generalmodel->fieldIndex("nameequip")||(dbworking->currtable!="test")){
        edit->setModelTable(dbworking->generalmodel, dbworking->currtable);
        edit->tablemapper->setCurrentModelIndex(index);
        edit->show();
    }
}

void MainWindow::on_Add_clicked()
{
    dbworking->generalmodel->insertRow(dbworking->generalmodel->rowCount());
}

void MainWindow::takesave(bool yes)
{
    qDebug()<<"here "<<yes;
    if(yes) on_SaveButton_clicked();
}


