#ifndef LOGGER_H
#define LOGGER_H
#include <QLoggingCategory>

Q_DECLARE_LOGGING_CATEGORY(loggerInfo)
Q_DECLARE_LOGGING_CATEGORY(loggerWarning)
Q_DECLARE_LOGGING_CATEGORY(loggerCritical)
class logger
{
public:
    logger();
};

#endif // LOGGER_H
