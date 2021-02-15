/*Создание бд (без особых проверок, чисто для тестирования приложения, но так должны быть все name уникальными, а даты проверяться)
 * create table Equipment(
    id serial primary key,
    NameEquip VARCHAR(40) not null,
    FirstExplDate date not null,
    Note varchar(300)
);
create table Test(
    id serial primary key,
    NameTest VARCHAR(40) not null,
    DateTest date not null,
    Description varchar(300),
    idEqip int not null references Equpment(id)
);
create table Synonim(
    idtable serial primary key,
    nametable varchar(100) not null,
    synonim varchar(100) not null
);
insert into Equpment(NameEquip, FirstExplDate) values
('оборудование 1', '2021-01-01'),
('оборудование 2', '2021-01-02'),
('оборудование 3', '2021-01-03');

insert into test(NameTest, DateTest, idEqip) values
('проверка оборудования 1', '2021-01-02', 1),
('проверка оборудования 2', '2021-01-03', 2),
('проверка оборудования 3', '2021-01-04', 3),
('тестовая загрузка оборудования 1', '2021-01-05', 1),
('тестовая загрузка оборудования 2', '2021-01-06', 2);

insert into Synonim(nametable, synonim) values
('test', 'Тесты'),
('equipment', 'Оборудование');
*/
#include "mainwindow.h"

#include <QApplication>
#include <QtWidgets>
#include <QScopedPointer>
#include <QLoggingCategory>
/*Основная программа
 *
 * Глобальная переменная:
 * loggerFile - указатель на файл журнала операций (логов).
 *
 * Переменные:
 * a - экземпляр выполняемого приложения;
 * out - поток записи в файл логирования для вывода отметки начала сеанса;
 * w - основная форма приложения.
 *
 * Процедура:
 * logHandler - обработчик сообщений логов для их вывода в файл.
*/
QScopedPointer<QFile> loggerFile;

/*Обработчик сообщений логов для их вывода в файл
 *
 * Формальные параметры:
 * type - тип выводимого сообщения;
 * context - дополнительная информация о сообщении в соответствии с определенными категориями логов;
 * msg - текст сообщения.
 *
 * Локальная переменная:
 * out - поток записи в файл логирования.
*/
void logHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg){
    QTextStream out(loggerFile.data());
    out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ");   //Вывод текущей даты в файл
    switch (type)   //Определение аббревиатуры в соответсии с вызванным обработчиком
    {
        case QtInfoMsg:     out << "INF "; break;   //Запись необходимой аббревиатуры
        case QtWarningMsg:  out << "WRN "; break;
        case QtCriticalMsg: out << "CRT "; break;
        case QtFatalMsg:    out << "FTL "; break;
        case QtDebugMsg:    out << "DBG "; break;
    }
    out << context.category << ": "<< msg << endl;  //Запись информации по указанной категории логирования
    out.flush();    //Очистка буфера записи
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    loggerFile.reset(new QFile(QDir::currentPath()+"\\logFile.txt"));   //Связывание указателя и файла логирования
    loggerFile.data()->open(QFile::Append|QFile::Text); //Открытие файла логированния для записи
    QTextStream out(loggerFile.data());
    out<<"\\\\\\\\\\\\\\\\\\\\\\\\\\\n";    //Вывод метки начала сессии в файл логирования
    qInstallMessageHandler(logHandler); //Определение собственного обработчика сообщений для их записи в файл
    try {
        MainWindow w;
        w.show();
        return a.exec();
    }  catch (...) {
        return -1;
    }
}
