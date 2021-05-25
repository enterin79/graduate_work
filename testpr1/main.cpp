/* Дипломный проект по теме
 * "Разработка программного обеспечения ведения
 * базы данных для оценки работоспособности
 * бортовой аппаратуры"
 *
 * Разраотал: Жиляева Анастасия Андреевна
 * Специальность: 09.02.03
 * Дата и номер версии: 22.05.2021 v2.5
 * Язык программирования: С++
 * Среда разработки: Qt Creator
 *
 * Задание:
 * Разработать базу данных и приложение для взаимодействия с ней.
 * Должен быть разработан набор классов для подключения
 * к базе данных и корректного отображения информации из таблиц,
 * а также редактирования необходимых данных.
 *
 * Основные переменные:
 * a - экземпляр выполняемого приложения;
 * out - поток записи в файл логирования для вывода отметки начала сеанса;
 * w - основная форма приложения.
 *
 * Процедура:
 * logHandler - обработчик сообщений приложения для их вывода в файл.
 *
 * Ожидаемые входные данные:
 * 1) данные о КА, БИ, блоках, параметрах, решениях;
 * 2) пути к файлам, содержащим структурированный набор данных о работе КА;
 * 3) пути к файлам, содержащим подробую информацию о состояниях блоков КА.
*/
#include "mainwindow.h"

#include <QApplication>
#include <QtWidgets>
#include <QScopedPointer>
#include <QLoggingCategory>
#include <QtGui>

QScopedPointer<QFile> loggerFile;

/* Обработчик сообщений приложения для их вывода в файл
 *
 * Формальные параметры:
 * type - тип выводимого сообщения;
 * context - дополнительная информация о сообщении в соответствии с определенными категориями сообщений;
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
    loggerFile.reset(new QFile(QDir::currentPath()+"\\logFile_"+QDateTime::currentDateTime().toString("dd-MM-yyyy")+".txt"));   //Связывание указателя и файла логирования
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
