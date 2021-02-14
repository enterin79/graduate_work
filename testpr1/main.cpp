#include "mainwindow.h"

#include <QApplication>
#include <QtWidgets>
#include <QScopedPointer>
#include <QLoggingCategory>

QScopedPointer<QFile> loggerFile;
void logHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    try {
        loggerFile.reset(new QFile(QDir::currentPath()+"\\logFile.txt"));
        loggerFile.data()->open(QFile::Append|QFile::Text);
        QTextStream out(loggerFile.data());
        out<<"\\\\\\\\\\\\\\\\\\\\\\\\\\\n";
        qInstallMessageHandler(logHandler);
        MainWindow w;
        w.show();
        return a.exec();
    }  catch (...) {
        return 1;
    }
}

void logHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg){
    QTextStream out(loggerFile.data());
    out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ");
    switch (type)
    {
        case QtInfoMsg:     out << "INF "; break;
        case QtWarningMsg:  out << "WRN "; break;
        case QtCriticalMsg: out << "CRT "; break;
    }
    out << context.category << ": "<< msg << endl;
    out.flush();
}
