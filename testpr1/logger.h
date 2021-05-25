#ifndef LOGGER_H
#define LOGGER_H
#include <QLoggingCategory>

/*Класс для объявления категорий логирования для разных типов сообщений*/
Q_DECLARE_LOGGING_CATEGORY(loggerInfo)  //Информационное сообщение
Q_DECLARE_LOGGING_CATEGORY(loggerWarning)   //Предупреждение
Q_DECLARE_LOGGING_CATEGORY(loggerCritical)  //Сообщение о критической ошибке
class logger
{
public:
    logger();
};

#endif // LOGGER_H
