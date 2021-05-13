#ifndef ENUMEXEC_H
#define ENUMEXEC_H

#define LOG "ReceptionData"
#define BLOK "Blok"
#define KA "KA"
#define BI "BI"
#define PARM "ParameterOfBloсk"
#define SOL "Solution"
#define PARMLOG "ConditionOfParm"
#define PARMLOG_L "conditionofparm"
#define FILE "FileOfParameter"

enum class Enumerr:int{
    CONNECTIONOK,
    CONNECTIONERROR,
    READINGOK,
    READINGERROR,
    METALOADERROR,
    SAVINGERROR,
    SAVINGOK
};
#endif // ENUMEXEC_H
