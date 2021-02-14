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
    }
    out << context.category << ": "<< msg << endl;  //Запись информации по указанной категории логирования
    out.flush();    //Очистка буфера записи
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    try {
        loggerFile.reset(new QFile(QDir::currentPath()+"\\logFile.txt"));   //Связывание указателя и файла логирования
        loggerFile.data()->open(QFile::Append|QFile::Text); //Открытие файла логированния для записи
        QTextStream out(loggerFile.data());
        out<<"\\\\\\\\\\\\\\\\\\\\\\\\\\\n";    //Вывод метки начала сессии в файл логирования
        qInstallMessageHandler(logHandler); //Определение собственного обработчика сообщений для их записи в файл
        MainWindow w;
        w.show();
        return a.exec();
    }  catch (...) {
        return -1;
    }
}
