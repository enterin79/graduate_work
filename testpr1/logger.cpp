#include "logger.h"

/*Определение категорий логирования соответсвующими текстовыми сообщениями, которые будут выведены перед сообщением*/
Q_LOGGING_CATEGORY(loggerInfo, "Info")
Q_LOGGING_CATEGORY(loggerWarning, "Warning")
Q_LOGGING_CATEGORY(loggerCritical, "Critical")
logger::logger()
{

}
